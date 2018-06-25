#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->chart()->layout()->setContentsMargins(1,1,1,1);
    ui->graphicsView->chart()->setBackgroundRoundness(1);
    ui->graphicsView->chart()->setBackgroundBrush(QBrush(QColor("#232629")));

    xAxis = new QValueAxis();
    yAxis = new QValueAxis();
    series = new QLineSeries();

    StartUp();
}

MainWindow::~MainWindow()
{
    CloseDb();
    delete ui;
}

void MainWindow::StartUp(){
    QSettings sett("Jouni Kortelainen", "Weather");
    if(sett.contains("Database")){
        qDebug() << "Database path: " << sett.value("Database").toString();
        if(QFile(sett.value("Database").toString()).exists()){
            ConnectDb();
            GetUpdate();
            SetDates(ui->cbDates);
        }
    }else{
        qDebug() << "Database path missing";
    }
}

void MainWindow::SetAxis(QLineSeries* series){
    ui->graphicsView->chart()->axes().removeAll(yAxis);
    ui->graphicsView->chart()->axes().removeAll(xAxis);

    xAxis->setRange(0,24);
    xAxis->setTickCount(25);
    xAxis->setLabelFormat("%d");
    xAxis->setLabelsBrush(QBrush(QColor(255,255,255)));
    ui->graphicsView->chart()->setAxisX(xAxis, series);

    yAxis->setRange(0,30);
    yAxis->setTickCount(5);
    yAxis->setLabelFormat("%d");
    yAxis->setLabelsBrush(QBrush(QColor(255,255,255)));
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

void MainWindow::on_actionSettings_triggered()
{
    settings* set = new settings();
    QObject::connect(set,SIGNAL(accepted()),this,SLOT(accept()));
    QObject::connect(set,SIGNAL(rejected()),this,SLOT(reject()));

    int diagCode = set->exec();

    if(diagCode == QDialog::Accepted){
        QSettings sett("Jouni Kortelainen", "Weather");
        qDebug() << "Setting database path";
        sett.setValue("Database",set->GetPath());
        StartUp();
    }

    set->deleteLater();
}
