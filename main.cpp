#include "serialport.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Serialport w;
    w.show();

    return a.exec();
}
