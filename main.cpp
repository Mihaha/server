
#include "readData.h"
#include "server.h"
#include "gpio.h"
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server serv;
    serv.startServer();
    //while (serv.socOpen()==false){}
    //if(serv.socOpen()==true)
        //{serv.sendFreqTemp(); }
    return a.exec();
}