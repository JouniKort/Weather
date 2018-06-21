#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: white;");

    ConnectDb();
    WeatherData *NodeCollection = GetUpdate();
    InsertToDb(NodeCollection);
    //SetAxis();

    //QLineSeries* series = new QLineSeries();
    //while(current->pNext != NULL){
    //    series->append(current->time, current->temperature);
    //    current = current->pNext;
    //}

    //ui->graphicsView->chart()->addSeries(series);
    //ui->graphicsView->chart()->legend()->markers(series)[0]->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::ConnectDb(){
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=C:\\Users\\Jouni\\Documents\\Qt\\Weather\\weather.mdb");

    if(db.open()){
        qDebug() << "Database connection established";
    }else{
        qDebug() << db.lastError().text();
    }
    return NULL;
}

WeatherData* MainWindow::GetUpdate(){
    Scrape *scrape = new Scrape();
    WeatherData* head = scrape->LoadHtml("https://www.foreca.fi/Finland/Lappeenranta/details/20180627");

    return head;
}

MainWindow::InsertToDb(WeatherData *head){
    WeatherData* current = head;
    while(current->pNext != NULL){
        QString Sdate = QString::number(std::stoi(current->date));
        QString Stemp = QString::number(current->temperature);
        QString Stime = QString::number(current->time);

        QString cmd = QString("INSERT INTO Weather (AddingDate, ForDate, Temperature, Hour) VALUES (");
        cmd += Sdate + ",";
        cmd += Sdate + ",";
        cmd += Stemp + ",";
        cmd += Stime + ")";

        QSqlQuery query(cmd,db);
        query.exec();
        qDebug() << cmd;

        current = current->pNext;
    }
    return NULL;
}

MainWindow::SetAxis(QLineSeries *series){
    QValueAxis* xAxis = new QValueAxis();
    xAxis->setRange(0,24);
    xAxis->setTickCount(25);
    xAxis->setLabelFormat("%d");
    ui->graphicsView->chart()->setAxisX(xAxis, series);

    QValueAxis* yAxis = new QValueAxis();
    yAxis->setRange(0,25);
    yAxis->setTickCount(5);
    yAxis->setLabelFormat("%.2f");
    ui->graphicsView->chart()->setAxisY(yAxis, series);
}
