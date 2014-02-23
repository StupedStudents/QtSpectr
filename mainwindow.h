#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QFile>
#include <QBuffer>
#include <complex>
#include <iostream>
#include <valarray>
#include <vector>

namespace Ui {
class MainWindow;
}

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void startRecording();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void fft(CArray &x);
private slots:
    void stopRecording();
    void notifed();

private:

    static const double TwoPi = 6.283185307179586;
    void FFTAnalysis(double *AVal, double *FTvl, int Nvl, int Nft);
    std::vector<double> buffer;
    QFile outputFile;
    QByteArray *psbTmp;
    QAudioFormat format;
    QBuffer outBuf;
    QAudioInput *audioInput;  // class member.
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
