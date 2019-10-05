#include "mainwindow.h"
#include <QApplication>
#include <QFile>

using namespace std;

extern QString filename;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
