#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(SetDatabasePath()));
    QObject::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

}

settings::~settings()
{
    delete ui;
}

void settings::SetDatabasePath(){
    pathToDb = ui->lineEdit->text();
    accept();
}

QString settings::GetPath(){
    return pathToDb;
}
