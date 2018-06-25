#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <database.h>
#include <settings.h>
#include <QSettings>

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
    void SetAxis(QLineSeries* series);
    void SetSeries();
    void StartUp();

private slots:
    void on_cbDates_currentTextChanged(const QString &arg1);
    void on_hsDays_valueChanged(int value);
    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;
    QValueAxis *xAxis;
    QValueAxis *yAxis;
    QLineSeries *series;
};

#endif // MAINWINDOW_H
