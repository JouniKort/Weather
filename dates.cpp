#include <dates.h>

tm* CurrentDate(){
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    return now;
}

void DateOffset(struct tm* date, int offset){
    const time_t ONE_DAY = 24*60*60;
    time_t date_seconds = mktime(date) + (offset*ONE_DAY);
    *date = *localtime(&date_seconds);
}

char* DateToString(struct tm* date){
    char* buffer = (char*)malloc(sizeof(char)*9);
    strftime(buffer,sizeof(char)*9,"%Y%m%d",date);
    return buffer;
}

tm* TransformDate(int yyyymmdd){
    tm* date = CurrentDate();
    date->tm_mday = yyyymmdd % 100;
    yyyymmdd /= 100;
    date->tm_mon = yyyymmdd % 100 - 1;  //Zero-based
    yyyymmdd /= 100;
    date->tm_year = yyyymmdd - 1900;

    return date;
}
