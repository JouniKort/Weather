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
    WeatherData* LoadHtml(QString url, char target_date[]);
private:
    WeatherData* InitializeStruct();
    WeatherData* Parse(std::string source, WeatherData *head, char target_date[8]);
};

#endif // SCRAPE_H
