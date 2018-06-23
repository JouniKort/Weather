#ifndef DATES_H
#define DATES_H

#include <ctime>
#include <string.h>
#include <iostream>
#include <models.h>

tm* CurrentDate();
void DateOffset(struct tm* date, int Offset);
char* DateToString(struct tm* date);
tm* TransformDate(int yyyymmdd);

#endif // DATES_H
