#ifndef SCRAPE_H
#define SCRAPE_H

#include <QtNetwork>
#include <iostream>
#include <models.h>
#include <ctime>

class Scrape
{
public:
    Scrape();
    WeatherData* LoadHtml(QString url);
private:
    WeatherData* InitializeStruct();
    WeatherData* Parse(std::string source, WeatherData *head);
    WeatherData* SetDateTimes(WeatherData* head);
    char *CurrentDate();
};

#endif // SCRAPE_H
