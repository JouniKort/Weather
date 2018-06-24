#include <database.h>

QSqlDatabase db;

void ConnectDb(){
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=C:\\Users\\Jouni\\Documents\\Qt\\Weather\\weather.mdb");

    if(db.open()){
        qDebug() << "Database connection established";
    }else{
        qDebug() << db.lastError().text();
    }
}

void CloseDb(){
    db.close();
}

void GetUpdate(){
    tm *pdate = CurrentDate();
    DateOffset(pdate,0);
    char* date_current = DateToString(pdate);

    QString cmd = "SELECT * FROM Weather WHERE AddingDate=" + QString::number(std::stoi(date_current));
    QSqlQuery query(db);
    query.prepare(cmd);
    query.exec();
    if(query.next()){qDebug() << "No updates"; return;}

    Scrape *scrape = new Scrape();
    for(int i = 1; i < 10; i++){
        tm *pdate = CurrentDate();
        DateOffset(pdate,i);
        char* date_target = DateToString(pdate);

        QString url = "https://www.foreca.fi/Finland/Lappeenranta/details/";
        url += QString(date_target);

        InsertToDb(scrape->LoadHtml(url, date_target),date_current);
    }
    query.finish();

    qDebug() << "Updated";
}

void SetDates(QComboBox* cbDates){
    QSqlQuery query;
    query.prepare("SELECT DISTINCT ForDate FROM Weather");
    query.exec();

    while(query.next()){
        cbDates->addItem(query.value(0).toString());
    }
}

QLineSeries* GetSeries(QString forDate, QString addingDate){
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Weather WHERE AddingDate=? AND ForDate=?");
    query.addBindValue(addingDate);
    query.addBindValue(forDate);
    query.exec();

    QLineSeries* series = new QLineSeries();
    bool midnight = 0;
    while(query.next()){
        if(std::stoi(query.value("Hour").toString().toStdString()) == 0){
            if(midnight){
                series->append(24, std::stoi(query.value("Temperature").toString().toStdString()));
            }else{
                series->append(0, std::stoi(query.value("Temperature").toString().toStdString()));
                midnight = 1;
            }
        }else{
            series->append(std::stoi(query.value("Hour").toString().toStdString()), std::stoi(query.value("Temperature").toString().toStdString()));
        }
    }
    query.finish();

    return series;
}

int ResultSize(QSqlQuery query){
    int initialPos = query.at();
    int pos = 0;
    if(query.last()){pos = query.at() + 1;}
    else pos = 0;
    query.seek(initialPos);
    return pos;
}

void InsertToDb(WeatherData *head, char date_current[8]){
    WeatherData* current = head;
    WeatherData* tmp;
    while(current->pNext != NULL){
        QString SdateCurrent = QString::number(std::stoi(date_current));
        QString SdateTarget = QString::number(std::stoi(current->date));
        QString Stemp = QString::number(current->temperature);
        QString Stime = QString::number(current->time);

        QSqlQuery query(db);
        query.prepare("INSERT INTO Weather (AddingDate, ForDate, Temperature, Hour) VALUES (?,?,?,?)");
        query.addBindValue(SdateCurrent);
        query.addBindValue(SdateTarget);
        query.addBindValue(Stemp);
        query.addBindValue(Stime);
        query.exec();

        tmp = current->pNext;
        free(current);
        current = tmp;
    }

    head = NULL;
}
