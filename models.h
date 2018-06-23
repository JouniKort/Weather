#ifndef MODELS_H
#define MODELS_H

struct WeatherData{
    char date[8];
    short time;
    short temperature;
    WeatherData* pNext;
};

struct DateData{
    int y;
    int m;
    int d;
};

#endif // MODELS_H
