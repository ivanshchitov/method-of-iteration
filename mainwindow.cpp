#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <qwt_plot_grid.h>

#define NMAX 5000
#define MMAX 1000

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initArrays();
    initImage();
    initQwtPlot();
    initPlotCurves();
    setAxes();
    initGrid();
    on_drawButton_toggled(false);
    ui->drawButton->setCheckable(true);
    setWindowTitle("Method of Iterations");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_enableSizeButton_clicked() {
    ui->qwtPlot->setAxisScale(
                    QwtPlot::xBottom,
                    std::min(ui->aDoubleSpinBox->value(), ui->bDoubleSpinBox->value()),
                    std::max(ui->aDoubleSpinBox->value(), ui->bDoubleSpinBox->value()));
        ui->qwtPlot->setAxisScale(
                    QwtPlot::yLeft,
                    std::min(ui->cDoubleSpinBox->value(), ui->dDoubleSpinBox->value()),
                    std::max(ui->cDoubleSpinBox->value(), ui->dDoubleSpinBox->value()));
        ui->qwtPlot->replot();
}

void MainWindow::initArrays() {
    nx = new double [NMAX*MMAX+1];
    px = new double [NMAX*MMAX+1];
    ny = new double [NMAX*MMAX+1];
    py = new double [NMAX*MMAX+1];
}

void MainWindow::initQwtPlot() {
    ui->qwtPlot->setTitle("График");
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,
                              ui->aDoubleSpinBox->value(),
                              ui->bDoubleSpinBox->value());
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,
                              ui->cDoubleSpinBox->value(),
                              ui->dDoubleSpinBox->value());
}

void MainWindow::initPlotCurves() {
    QPen nPen = QPen(Qt::red); // цвет для отрисовки графика
    nCurve = new QwtPlotCurve();
    nCurve->setRenderHint(QwtPlotItem::RenderAntialiased); // сглаживание линий графика
    nCurve->setPen(nPen);
    nCurve->setStyle(QwtPlotCurve::Dots);
    nCurve->attach(ui->qwtPlot); // привязка графика к области рисования
    QPen pPen = QPen(Qt::blue);
    pCurve = new QwtPlotCurve();
    pCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
    pCurve->setPen(pPen);
    pCurve->setStyle(QwtPlotCurve::Dots);
    pCurve->attach(ui->qwtPlot);
    QPen oxyPen = QPen(Qt::darkGray);
    oxAxe = new QwtPlotCurve();
    oxAxe->setRenderHint(QwtPlotItem::RenderAntialiased);
    oxAxe->setPen(oxyPen);
    oxAxe->attach(ui->qwtPlot);
    oyAxe = new QwtPlotCurve();
    oyAxe->setRenderHint(QwtPlotItem::RenderAntialiased);
    oyAxe->setPen(oxyPen);
    oyAxe->attach(ui->qwtPlot);
}

void MainWindow::initImage() {
    QImage *image = new QImage;
    image->load("://formula.png");
    ui->imgLabel->setPixmap(QPixmap::fromImage(*image));
}

void MainWindow::initGrid() {
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->enableXMin(true);
    grid->enableYMin(true);
    grid->setMajorPen(QPen(Qt::lightGray,0,Qt::DashDotDotLine));
    grid->setMinorPen(QPen(Qt::lightGray,0,Qt::DotLine));
    grid->attach(ui->qwtPlot);
}

double MainWindow::func(double x, int num_of_par, double par) {
    switch (num_of_par) {
        case 1:
            return par * sin(tan(ui->betaDoubleSpinBox->value() * x))
                    + ui->epsilonDoubleSpinBox->value() * cos(ui->gammaDoubleSpinBox->value() * x);
        case 2:
            return ui->alphaDoubleSpinBox->value() * sin(tan(par * x))
                    + ui->epsilonDoubleSpinBox->value() * cos(ui->gammaDoubleSpinBox->value() * x);
        case 3:
            return ui->alphaDoubleSpinBox->value() * sin(tan(ui->betaDoubleSpinBox->value() * x))
                        + par * cos(ui->gammaDoubleSpinBox->value() * x);
        case 4:
            return ui->alphaDoubleSpinBox->value() * sin(tan(ui->betaDoubleSpinBox->value() * x))
                    + ui->epsilonDoubleSpinBox->value() * cos(par * x);
        default:
            return 0;
    }
}

void MainWindow::buildIterationResults(int num_of_par) {
    double L = ui->bDoubleSpinBox->value() - ui->aDoubleSpinBox->value();
    double h = L / NMAX;
    double absc = 0, yord = 0;
    for (int i = 0; i <= NMAX; i++) {
        absc = ui->aDoubleSpinBox->value() + i * h;
        yord = ui->x0DoubleSpinBox->value();
        for (int j = 0; j < ui->mSpinBox->value(); j++) // пропуск m предварительных значений итераций
            yord = func(yord, num_of_par, absc);
        for (int j = 0; j < ui->nSpinBox->value(); j++) { // подсчёт n результатов операций-итераций
            nx[len_n] = absc;
            yord = func(yord, num_of_par, absc);
            ny[len_n] = yord;
            if (len_n % ui->pSpinBox->value() == 0) { // отдельное добавление каждой p-ой из n итераций в данные
                px[len_p] = nx[len_n];
                py[len_p] = yord;
                len_p++;
            }
            len_n++;
        }
    }
}

void MainWindow::dumpIterationsResults() {
    len_n = 0;
    len_p = 0;
}

void MainWindow::drawGraphics(bool state) {
    setCurves();
    nCurve->setVisible(state);
    pCurve->setVisible(state);
    ui->qwtPlot->replot(); // перерисовка области рисования
}

void MainWindow::setAxes() {
    double xdata[3];
    double oxdata[3];
    xdata[1] = -100;
    xdata[2] = 100;
    oxdata[1] = oxdata[2] = 0;
    double ydata[3];
    double oydata[3];
    ydata[1] = ydata[2] = 0;
    oydata[1] = -100;
    oydata[2] = 100;
    oxAxe->setSamples(xdata, oxdata, 3);
    oyAxe->setSamples(ydata, oydata, 3);
}

void MainWindow::on_drawButton_toggled(bool checked)
{
    if (checked == false) {
        this->dumpIterationsResults();
        this->drawGraphics(false);
        return;
    }
    if (ui->alphaRadioButton->isChecked())
        buildIterationResults(1);
    if (ui->betaRadioButton->isChecked())
        buildIterationResults(2);
    if (ui->epsilonRadioButton->isChecked())
        buildIterationResults(3);
    if (ui->gammaRadioButton->isChecked())
        buildIterationResults(4);
    this->drawGraphics(true);
}

void MainWindow::on_helpButton_clicked() {
    Dialog *dialog = new Dialog;
    dialog->show();
}

void MainWindow::setCurves() {
    if (!ui->redCheckBox->isChecked() && ui->blueCheckBox->isChecked()) {
        pCurve->setSamples(px, py, len_p);
    }
    if (ui->redCheckBox->isChecked() && !ui->blueCheckBox->isChecked()) {
        nCurve->setSamples(px, py, len_p);
    }
    if (ui->redCheckBox->isChecked() && ui->blueCheckBox->isChecked()) {
        nCurve->setSamples(nx, ny, len_n);
        pCurve->setSamples(px, py, len_p);
    }
}
