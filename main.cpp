#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleFile("C:\\Users\\Jouni\\Documents\\Qt\\Weather\\style\\style_.qss");
    styleFile.open(QFile::ReadOnly);

    QString style(styleFile.readAll());
    a.setStyleSheet(style);

    MainWindow w;
    w.show();

    return a.exec();
}
