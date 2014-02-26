#include "mainwindow.h"
#include "ui_mainwindow.h"

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
        double* ptr1 = new double[numSamples * format.channelCount()];
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
        int index = 0, tmp_index = 0;
        double max = 0, tmp_max = 0;
        double buf = (double(format.sampleRate()) / (numSamples * format.channelCount()));
        for (int i = 1; i < 370. / buf; i++ )
        {
            if (spectrogramm[i] > 5e+8  && max < spectrogramm[i] &&
                                        (((i * buf) < 329.8 && (i * buf) > 329.4) ||
                                         ((i * buf) < 247 && (i * buf) > 246) ||
                                         ((i * buf) < 197 && (i * buf) > 195) ||
                                         ((i * buf) < 147 && (i * buf) > 145) ||
                                         ((i * buf) < 111 && (i * buf) > 109) ||
                                         ((i * buf) < 83 && (i * buf) > 82)))
            {

                max = spectrogramm[i];
                index = i;
            }
            if(spectrogramm[i] > tmp_max)
            {
                tmp_max = spectrogramm[i];
                tmp_index = i;
            }
        }
        delete spectrogramm;
        delete ptr1;
        double frequency_ = index * buf;//format.sampleRate() * index / (numSamples * format.channelCount());
        //qWarning() << frequency;
        if (frequency_ < 60) frequency_ = 0;
        m_frequency = frequency_;

        double fre_ = tmp_index * buf;
        frequency_tmp = fre_;

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
    i = new bool[6];
    ui->setupUi(this);
    int r=0,g=255,b=0;
    QString myStyleSheet = QString(" QProgressBar::chunk { background: rgb(%1,%2,%3); }").arg(QString::number(r)).arg(QString::number(g)).arg(QString::number(b));
    s = ui->progressBar->styleSheet().append(myStyleSheet);
    myStyleSheet = QString(" QProgressBar::chunk { background: rgb(255,0,0); }");
    def = ui->progressBar->styleSheet().append(myStyleSheet);
    ui->progressBar->setStyleSheet(def);
    ui->progressBar_2->setStyleSheet(def);
    ui->progressBar_3->setStyleSheet(def);
    ui->progressBar_4->setStyleSheet(def);
    ui->progressBar_5->setStyleSheet(def);
    ui->progressBar_6->setStyleSheet(def);
 }

void MainWindow::dropScreen()
{
    if(i[0])
    {
        ui->progressBar->setStyleSheet(def);
        i[0] = false;
    }
    if(i[1])
    {
        ui->progressBar_2->setStyleSheet(def);
        i[1] = false;
    }
    if(i[2])
    {
        ui->progressBar_3->setStyleSheet(def);
        i[2] = false;
    }
    if(i[3])
    {
        ui->progressBar_4->setStyleSheet(def);
        i[3] = false;
    }
    if(i[4])
    {
        ui->progressBar_5->setStyleSheet(def);
        i[4] = false;
    }
    if(i[5])
    {
        ui->progressBar_6->setStyleSheet(def);
        i[5] = false;
    }
}

 void MainWindow::updateScreen()
 {
     ui->progressBar_8->setValue(audioInfo->level() * 100);
     ui->progressBar_7->setValue(audioInfo->freq());
     ui->lcdNumber->display(audioInfo->frequency());
     ui->lcdNumber_2->display(audioInfo->freq());
     bool fl = false;
     if((audioInfo->frequency() < 329 + 10)&&(audioInfo->frequency() > 329 - 10)){
         ui->progressBar->setStyleSheet(s);
         i[0] = fl = true;
     }
     if((audioInfo->frequency()<246+10)&&(audioInfo->frequency()>246-10)){
         ui->progressBar_2->setStyleSheet(s);
         i[1] = fl = true;
     }
     if((audioInfo->frequency()<196+10)&&(audioInfo->frequency()>196-10)){
         ui->progressBar_3->setStyleSheet(s);
         i[2] = fl = true;
     }
     if((audioInfo->frequency()<146+10)&&(audioInfo->frequency()>146-10)){
         ui->progressBar_4->setStyleSheet(s);
         i[3] = fl = true;
     }
     if((audioInfo->frequency()<110+10)&&(audioInfo->frequency()>110-10)){
         ui->progressBar_5->setStyleSheet(s);
         i[4] = fl = true;
     }
     if((audioInfo->frequency()<82+10)&&(audioInfo->frequency()>82-10)){
         ui->progressBar_6->setStyleSheet(s);
         i[5] = fl = true;
     }
    if(fl)
    {
        QTimer::singleShot(500,this,SLOT(dropScreen()));
    }
 }

 void MainWindow::deviceChanged(int index)
 {
     audioInfo->stop();
     audioInput->stop();
     audioInput->disconnect(this);
     delete audioInput;

     info = ui->comboBox->itemData(index).value<QAudioDeviceInfo>();
     changeDev();
 }


 void MainWindow::startRecording()
 {
     format.setSampleRate(8000);
     format.setChannelCount(2);
     format.setSampleSize(16);
     format.setCodec("audio/pcm");
     format.setByteOrder(QAudioFormat::LittleEndian);
     format.setSampleType(QAudioFormat::SignedInt);

     QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
     for(int i = 0; i < devices.size(); ++i)
         ui->comboBox->addItem(devices.at(i).deviceName(), qVariantFromValue(devices.at(i)));

     connect(ui->comboBox, SIGNAL(activated(int)), SLOT(deviceChanged(int)));

     info = QAudioDeviceInfo::availableDevices(QAudio::AudioInput).first();
     if (!info.isFormatSupported(format)) {
         qWarning()<<"default format not supported try to use nearest";
         format = info.nearestFormat(format);
         qWarning() << format.sampleRate();
     }
     audioInfo = new AudioInfo(format, this);
     connect(audioInfo,SIGNAL(update()),this,SLOT(updateScreen()));
     changeDev();

 }

 void MainWindow::changeDev()
 {
     audioInput = new QAudioInput(info, format, this);
     connect(audioInput, SIGNAL(notify()), SLOT(notifed()));
     audioInput->setBufferSize(1280 * 8 * 16); // 256 * 4 * 16
     audioInfo->start();
     audioInput->start(audioInfo);
 }

 void MainWindow::notifed()
 {
 }

 double* AudioInfo::Calculate(double* x)
 {
     const int channelBytes = format.sampleSize() / 8;
     const int sampleBytes = format.channelCount() * channelBytes;
     const int numSamples = (16384 * 2) / sampleBytes;
     int lenght;
     int bitsInLenght;
     if (IsPowerOfTwo((numSamples * format.channelCount())))
     {
         lenght = (numSamples * format.channelCount());
         bitsInLenght = Log2((numSamples * format.channelCount())) - 1;
     }
     else
     {
         bitsInLenght = Log2((numSamples * format.channelCount()));
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
    delete i;
    delete ui;
}
