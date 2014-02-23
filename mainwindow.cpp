#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAudioInput>
#include <QAudioFormat>
#include <QTimer>
#include <QAudioDeviceInfo>

const double PI = 3.14159265359;
AudioInfo::AudioInfo(const QAudioFormat &format, QObject *parent)
    :   QIODevice(parent)
    ,   format(format)
    ,   m_level(0.0)
    ,   m_frequency(0.0)
    ,   m_maxAmplitude (32767)

{
}

AudioInfo::~AudioInfo()
{
}

void AudioInfo::start()
{
    open(QIODevice::WriteOnly);
}

void AudioInfo::stop()
{
    close();
}

qint64 AudioInfo::readData(char *data, qint64 maxlen)
{
    Q_UNUSED(data)
    Q_UNUSED(maxlen)

    return 0;
}

qint64 AudioInfo::writeData(const char *data, qint64 len)
{
    if (m_maxAmplitude) {
        const int channelBytes = format.sampleSize() / 8;
        const int sampleBytes = format.channelCount() * channelBytes;
        const int numSamples = len / sampleBytes;
        quint32 maxValue = 0;
        const unsigned char *ptr = reinterpret_cast<const unsigned char *>(data);
        double* ptr1 = new double[512];
        for (int i = 0; i < numSamples; ++i) {
            for (int j = 0; j < format.channelCount(); ++j) {
                quint32 value = 0;
                value = qAbs(qFromLittleEndian<qint16>(ptr));
                maxValue = qMax(value, maxValue);
                ptr += channelBytes;
                ptr1[i * format.channelCount() + j] = value;
            }
        }

        double* spectrogramm = Calculate(ptr1);
        int index = 0;
        double max = 0;
        for (int i = 1; i < 128; i++ )
        {
            if (max < spectrogramm[i])
            {
                max = spectrogramm[i];
                index = i;
            }
        }
        delete spectrogramm;
        double frequency = format.sampleRate() * index / 512;
        if (frequency < 60) frequency = 0;
        m_frequency = frequency;
        maxValue = qMin(maxValue, m_maxAmplitude);
        m_level = qreal(maxValue) / m_maxAmplitude;
    }

    emit update();
    return len;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

 void MainWindow::updateScreen()
 {
     ui->progressBar->setValue(audioInfo->level() * 100);
     ui->progressBar_2->setValue(audioInfo->frequency());
     ui->lcdNumber->display(audioInfo->frequency());
     ui->lcdNumber_2->display(audioInfo->level() * 100);
 }

 void MainWindow::startRecording()
 {

     format.setSampleRate(8000);
     format.setChannelCount(2);
     format.setSampleSize(16);
     format.setCodec("audio/pcm");
     format.setByteOrder(QAudioFormat::LittleEndian);
     format.setSampleType(QAudioFormat::SignedInt);
     //outBuf.open(QIODevice::ReadWrite | QIODevice::Truncate);
     QAudioDeviceInfo info = QAudioDeviceInfo::availableDevices(QAudio::AudioInput).first();
     if (!info.isFormatSupported(format)) {
         qWarning()<<"default format not supported try to use nearest";
         format = info.nearestFormat(format);
     }
     audioInfo = new AudioInfo(format, this);
     audioInput = new QAudioInput(info, format, this);
     connect(audioInput, SIGNAL(notify()), SLOT(notifed()));
     connect(audioInfo,SIGNAL(update()),this,SLOT(updateScreen()));
     audioInput->setBufferSize(1280 * 4);
     audioInfo->start();
     audioInput->start(audioInfo);
 }

 void MainWindow::notifed()
 {
 }

 double* AudioInfo::Calculate(double* x)
 {
     int lenght;
     int bitsInLenght;
     if (IsPowerOfTwo(512))
     {
         lenght = 512;
         bitsInLenght = Log2(512) - 1;
     }
     else
     {
         bitsInLenght = Log2(512);
         lenght = 1 << bitsInLenght;
     }
     ComplexNumber *data = new ComplexNumber[lenght];
     for (int i = 0; i < lenght; i++ )
     {
         int j = ReverseBits( i, bitsInLenght);
         data[j] = ComplexNumber(x[i]);
     }
     for (int i = 0; i < bitsInLenght; i++ )
     {
         int m = 1 << i;
         int n = m * 2;
         double alpha = -(2 * PI / n);
         for (int k = 0; k < m; k++)
         {
             ComplexNumber oddPartMultiplier = (ComplexNumber(0, alpha * k)).PoweredE();
             for (int j = k; j < lenght; j += n )
             {
                 ComplexNumber evenPart = data[j];
                 ComplexNumber oddPart = oddPartMultiplier * data[j + m];
                 data[j] = evenPart + oddPart;
                 data[j + m] = evenPart - oddPart;
             }
         }
     }
     double* spectrogramma = new double[lenght];
     for (int i = 0; i < lenght; i++)
     {
         spectrogramma[i] = data[i].AbsPower2();
     }
     delete data;
     return spectrogramma;

 }

MainWindow::~MainWindow()
{
    delete ui;
}
