#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    ~settings();
    QString GetPath();

private slots:
    void SetDatabasePath();
private:
    Ui::settings *ui;
    QString pathToDb;
};

#endif // SETTINGS_H
