#include "scrape.h"

Scrape::Scrape()
{

}

WeatherData* Scrape::LoadHtml(QString url){
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(url)));
    QEventLoop event;
    QObject::connect(response, SIGNAL(finished()), &event, SLOT(quit()));
    event.exec();

    WeatherData* NodeCollection = InitializeStruct();
    NodeCollection = Parse(response->readAll().toStdString(), NodeCollection);
    NodeCollection = SetDateTimes(NodeCollection);
    return NodeCollection;
}

WeatherData* Scrape::InitializeStruct(){
    WeatherData* head = NULL;
    head = (WeatherData*)malloc(sizeof(WeatherData));
    if(head == NULL){
        return NULL;
    }

    head->pNext = NULL;
    return head;
}

WeatherData* Scrape::Parse(std::string source,WeatherData* head){
    const int length = 11;

    static char buffer[length];
    static char bufferTemp[3];
    static char bufferTime[3];
    static char* pBottom = buffer;
    static char* pFill = buffer;
    static char* pTop = pBottom + length - 1;

    const char match1[length] = "class=\"c4\"";
    const char match2[length] = "class=\"c0\"";
    const char match3[length] = "\"><strong>";
    const char match4[length] = "> <strong>";

    WeatherData *current = head;

    short found = 0;

    bool readTemp = false;
    bool Temp = false;
    bool readTime = false;
    bool Time = false;

    int Found = 0;

    for(char &c : source){
        for(int i = 0; i < length-2; i++){
            buffer[i] = buffer[i+1];
        }
        buffer[length-2] = c;

        if(readTemp){
            bufferTemp[0] = bufferTemp[1];
            bufferTemp[1] = bufferTemp[2];
            bufferTemp[2] = c;
            if(bufferTemp[0] != '\0'){
                current->temperature = std::stoi(std::string(bufferTemp));

                Found++;
                Temp = false;
                readTemp = false;
                memset(bufferTemp,'\0',sizeof(bufferTemp));
            }
        }else if(readTime){
            bufferTime[0] = bufferTime[1];
            bufferTime[1] = bufferTime[2];
            bufferTime[2] = c;
            if(bufferTime[0] != '\0'){
                current->time = std::stoi(std::string(bufferTime));

                Found++;
                readTime = false;
                Time = false;
                memset(bufferTime,'\0',sizeof(bufferTime));
            }
        }

        if(Found == 2){
            Found = 0;

            current->pNext = (WeatherData*)malloc(sizeof(WeatherData));
            current->pNext->pNext = NULL;
            current = current->pNext;
        }

        if(!strcmp(buffer,match1)){
            Temp = true;
        }else if(!strcmp(buffer, match2)){
            Time = true;
        }else if(!strcmp(buffer,match3) && Temp ){
            readTemp = Temp;
        }else if(!strcmp(buffer,match4) && Time){
            readTime = Time;
        }
    }

    return head;
}

WeatherData* Scrape::SetDateTimes(WeatherData *head){
    char* date = CurrentDate();

    WeatherData *current = head;
    while(current->pNext != NULL){
        for(int i = 0; i < 8; i++){
            current->date[i] = date[i];
        }
        current = current->pNext;
    }

    free(date);
    return head;
}

char* Scrape::CurrentDate(){
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    std::string date = std::to_string(now->tm_year+1900);
    if(now->tm_mon < 10){date += std::to_string(0);}
    date += std::to_string(now->tm_mon);
    date += std::to_string(now->tm_mday);

    char *date_arr = (char*)malloc(8);
    memset(date_arr,'\0',8);
    for(int i = 0; i < 8; i++){
        date_arr[i] = date[i];
    }

    return date_arr;
}
