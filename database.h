#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QComboBox>
#include <QtCharts>
#include <models.h>
#include <dates.h>
#include <scrape.h>

void GetUpdate();
void SetDates(QComboBox* cbDates);
QLineSeries* GetSeries(QString forDate, QString addingDate);
void ConnectDb();
void CloseDb();
void InsertToDb(WeatherData* head, char date_current[]);
AxisMinMax* GetMinMax(QString forDate);
int ResultSize(QSqlQuery query);

#endif // DATABASE_H
