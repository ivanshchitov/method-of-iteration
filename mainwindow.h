#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwt_plot_curve.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_enableSizeButton_clicked();
    void on_drawButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    double *nx, *px, *ny, *py;
    int len_n,len_p;
    QwtPlotCurve *nCurve, *pCurve, *oxAxe, *oyAxe;

private:
    void initQwtPlot();
    void initPlotCurves();
    void initImage();
    void initArrays();
    void initGrid();
    double func(double x, int num_of_par, double par);
    void buildIterationResults(int num_of_par);
    void dumpIterationsResults();
    void drawGraphics(bool state);
    void setAxes();
};

#endif // MAINWINDOW_H
