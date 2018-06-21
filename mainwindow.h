#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <scrape.h>

using namespace QtCharts;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    SetAxis(QLineSeries *series);
    WeatherData *GetUpdate();
    ConnectDb();
    InsertToDb(WeatherData* head);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
};

#endif // MAINWINDOW_H
