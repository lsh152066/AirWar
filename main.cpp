#include "wight.h"
#include "mainwight.h"
#include <QApplication>
#include"NetDef.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<flightPackage>("flightPackage");

    MainWight Mw;
    Mw.show();

    return a.exec();
}
