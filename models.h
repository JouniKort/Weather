#ifndef MODELS_H
#define MODELS_H

struct WeatherData{
    char date[8];
    int time;
    short temperature;
    WeatherData* pNext;
};

#endif // MODELS_H
