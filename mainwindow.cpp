#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAudioInput>
#include <QAudioFormat>
#include <QTimer>
#include <QAudioDeviceInfo>
#include <QtMath>


const double PI = 3.141592653589793238460;



// Cooley–Tukey FFT (in-place)
void MainWindow::fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;
    CArray even = x[std::slice(0, N/2, 2)];
    CArray  odd = x[std::slice(1, N/2, 2)];
    fft(even);
    fft(odd);
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

 void MainWindow::startRecording()
 {
     format.setSampleRate(8000);
     format.setChannelCount(2);
     format.setSampleSize(16);
     format.setCodec("audio/pcm");
     format.setByteOrder(QAudioFormat::LittleEndian);
     format.setSampleType(QAudioFormat::SignedInt);
     outBuf.open(QIODevice::ReadWrite | QIODevice::Truncate);
     psbTmp = new QByteArray[32];
     //outBuf.setBuffer(psbTmp);

     QAudioDeviceInfo info = QAudioDeviceInfo::availableDevices(QAudio::AudioInput).first();
     if (!info.isFormatSupported(format)) {
         qWarning()<<"default format not supported try to use nearest";
         format = info.nearestFormat(format);
     }

     audioInput = new QAudioInput(format, this);
     audioInput->setNotifyInterval(32);
     audioInput->setBufferSize(32);
     audioInput->start(&outBuf);

     connect(audioInput, SIGNAL(notify()),SLOT(notifed()));
     //QTimer::singleShot(100, this, SLOT(stopRecording()));
 }

 void MainWindow::stopRecording()
 {
     psbTmp = new QByteArray();
     *psbTmp = outBuf.buffer();
     qWarning() << *psbTmp->data();
     delete psbTmp;
     audioInput->stop();
     outBuf.close();
     delete audioInput;
 }

 void MainWindow::notifed()
 {
     const int channelBytes = format.sampleSize() / 8;
     const int sampleBytes = format.channelCount() * channelBytes;
     const int numSamples = 32 / sampleBytes;
     qreal m_level = 0;

     quint32 maxValue = 0;
     double *ptr1, *ptr2;
     Complex *tmp = new Complex[16];
     ptr1 = new double[16];
     ptr2 = new double[16];
     //qWarning() << sizeof maxValue;// size();
     const unsigned char *ptr = reinterpret_cast<const unsigned char *>(outBuf.data().data());
     //const unsigned char *ptr = reinterpret_cast<const unsigned char *>(psbTmp);
     for (int i = 0; i < numSamples - 1; ++i) {
         for (int j = 0; j < 2; ++j) {
             quint32 value = 0;
             value = qAbs(qFromLittleEndian<qint16>(ptr));
             maxValue = qMax(value, maxValue);
             ptr1[i * 2 + j + 1] = value;
             tmp[i * 2 + j + 1] = value;
             ptr += channelBytes;
         }
     }
     tmp[0] = tmp[15] = 0;
     //FFTAnalysis(ptr1,ptr2,512,512);
     CArray tst(tmp,16);
     fft(tst);
     double quer = 0, buf = 0;
     Complex arr;
     for(int i = 0; i < 16; i++)
     {
         arr = tst[i];
         buf = arr.real();
        //quer = qMax(quer,ptr2[i]);
         if(buf < quer) continue;
         else quer = buf;
     }
     quer /= 100;
     maxValue = qMin(maxValue, quint32(32767));
     m_level = qreal(maxValue) / 32767;
     m_level *= 100;
     //qWarning() << quer;
     outBuf.reset();
     //outBuf.buffer().clear();
     ui->progressBar->setValue(m_level);
     ui->progressBar_2->setValue(quer);
     ui->lcdNumber->display(quer);
     ui->lcdNumber_2->display(m_level);
     delete ptr1;
     delete ptr2;
 }

 void MainWindow::FFTAnalysis(double *AVal, double *FTvl, int Nvl, int Nft) {
   int i, j, n, m, Mmax, Istp;
   double Tmpr, Tmpi, Wtmp, Theta;
   double Wpr, Wpi, Wr, Wi;
   double *Tmvl;

   n = Nvl * 2; Tmvl = new double[n];

   for (i = 0; i < Nvl; i++) {
     j = i * 2; Tmvl[j] = 0; Tmvl[j+1] = AVal[i];
   }

   i = 1; j = 1;
   while (i < n) {
     if (j > i) {
       Tmpr = Tmvl[i]; Tmvl[i] = Tmvl[j]; Tmvl[j] = Tmpr;
       Tmpr = Tmvl[i+1]; Tmvl[i+1] = Tmvl[j+1]; Tmvl[j+1] = Tmpr;
     }
     i = i + 2; m = Nvl;
     while ((m >= 2) && (j > m)) {
       j = j - m; m = m >> 1;
     }
     j = j + m;
   }

   Mmax = 2;
   while (n > Mmax) {

     Theta = -TwoPi / Mmax; Wpi = qSin(Theta);
     Wtmp = qSin(Theta / 2); Wpr = Wtmp * Wtmp * 2;
     Istp = Mmax * 2; Wr = 1; Wi = 0; m = 1;

     while (m < Mmax) {
       i = m; m = m + 2; Tmpr = Wr; Tmpi = Wi;
       Wr = Wr - Tmpr * Wpr - Tmpi * Wpi;
       Wi = Wi + Tmpr * Wpi - Tmpi * Wpr;

       while (i < n) {
         j = i + Mmax;
         Tmpr = Wr * Tmvl[j] - Wi * Tmvl[j-1];
         Tmpi = Wi * Tmvl[j] + Wr * Tmvl[j-1];

         Tmvl[j] = Tmvl[i] - Tmpr; Tmvl[j-1] = Tmvl[i-1] - Tmpi;
         Tmvl[i] = Tmvl[i] + Tmpr; Tmvl[i-1] = Tmvl[i-1] + Tmpi;
         i = i + Istp;
       }
     }

     Mmax = Istp;
   }

   for (i = 0; i < Nft; i++) {
     j = i * 2; FTvl[Nft - i - 1] = qSqrt((Tmvl[j]) * (Tmvl[j]) + (Tmvl[j+1]) * (Tmvl[j+1]));
   }

   delete []Tmvl;
 }

MainWindow::~MainWindow()
{
    delete ui;
}
