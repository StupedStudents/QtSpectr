#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>

namespace Ui {
class MainWindow;
}

class AudioInfo : public QIODevice
{
    Q_OBJECT

public:
    AudioInfo();
    AudioInfo(const QAudioFormat &format, QObject *parent);
    ~AudioInfo();
    void start();
    void stop();
    qreal level() const { return m_level; }
    qreal frequency() const { return m_frequency; }
    qreal freq() const { return frequency_tmp; }
    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

private:
    int Log2(int n)
    {
        int i = 0;
        while (n > 0)
        {
            ++i;
            n >>= 1;
        }
        return i;
    }
    int ReverseBits(int n, int bitsCount)
    {
        int reversed = 0;
        for (int i = 0; i < bitsCount; i++)
        {
            int nextBit = n & 1;
            n >>= 1;
            reversed <<= 1;
            reversed |= nextBit;
        }
        return reversed;
    }
    bool IsPowerOfTwo(int n)
    {
        return n > 1 && (n & (n - 1)) == 0;
    }

    double* Calculate(double* x);
    double *FilterLF(double nF, int N, double *x, double BW);
    double* Convolution(double *x, int N, double *h, int M, double *st);
    const QAudioFormat format;
    qreal m_level;
    qreal m_frequency;
    quint32 m_maxAmplitude;
    qreal frequency_tmp;
signals:
    void update();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void startRecording();
    void changeDev();
private slots:
    void deviceChanged(int index);
    void notifed();
    void updateScreen();
    void dropScreen();
signals:
    void drop();


private:
    QString s, def;
    QAudioInput *audioInput;
    Ui::MainWindow *ui;
    AudioInfo* audioInfo;
    QAudioFormat format;
    bool *i;
    QAudioDeviceInfo info;
};

class ComplexNumber
{
public:
    double Re;
    double Im;
    ComplexNumber()
    {
        Re = Im = 0;
    }

    ComplexNumber(double re)
    {
        Re = re;
        Im = 0;
    }
    ComplexNumber(double re, double im)
    {
        Re = re;
        Im = im;
    }
    ComplexNumber operator *(ComplexNumber n2)
    {
        return ComplexNumber(Re * n2.Re - Im * n2.Im, Re * n2.Im + Im * n2.Re);
    }
    ComplexNumber operator +(ComplexNumber n2)
    {
        return ComplexNumber(Re + n2.Re, Im + n2.Im);
    }
    ComplexNumber operator -(ComplexNumber n2)
    {
        return ComplexNumber(Re - n2.Re, Im - n2.Im);
    }
    ComplexNumber operator -()
    {
        return ComplexNumber(-Re, -Im);
    }

    double Power2()
    {
        return Re * Re - Im * Im;
    }
    double AbsPower2()
    {
        return Re * Re + Im * Im;
    }
    ComplexNumber PoweredE()
    {
        double e = qExp(Re);
        return ComplexNumber(e * qCos(Im), e * qSin(Im));
    }
};

#endif // MAINWINDOW_H
