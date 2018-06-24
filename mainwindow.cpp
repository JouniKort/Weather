#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: white;");

    ui->graphicsView->chart()->layout()->setContentsMargins(1,1,1,1);
    ui->graphicsView->chart()->setBackgroundRoundness(0);

    xAxis = new QValueAxis();
    yAxis = new QValueAxis();
    series = new QLineSeries();

    ConnectDb();
    GetUpdate();
    SetDates(ui->cbDates);
}

MainWindow::~MainWindow()
{
    CloseDb();
    delete ui;
}

void MainWindow::SetAxis(QLineSeries* series){
    ui->graphicsView->chart()->axes().removeAll(yAxis);
    ui->graphicsView->chart()->axes().removeAll(xAxis);

    xAxis->setRange(0,24);
    xAxis->setTickCount(25);
    xAxis->setLabelFormat("%d");
    ui->graphicsView->chart()->setAxisX(xAxis, series);

    yAxis->setRange(0,30);
    yAxis->setTickCount(5);
    yAxis->setLabelFormat("%d");
    ui->graphicsView->chart()->setAxisY(yAxis, series);
}

void MainWindow::on_cbDates_currentTextChanged(const QString &arg1)
{
    SetSeries();
}

void MainWindow::on_hsDays_valueChanged(int value)
{
    SetSeries();
}

void MainWindow::SetSeries(){
    ui->graphicsView->chart()->removeAllSeries();

    tm* date = TransformDate(ui->cbDates->currentText().toInt());
    DateOffset(date,ui->hsDays->value()*-1);

    QString AddingDate = DateToString(date);
    QString ForDate = ui->cbDates->currentText();
    series = GetSeries(ForDate, AddingDate);

    ui->graphicsView->chart()->addSeries(series);
    ui->graphicsView->chart()->legend()->markers(series)[0]->setVisible(false);

    SetAxis(series);

    qDebug() << ForDate << "-" << AddingDate;
}
