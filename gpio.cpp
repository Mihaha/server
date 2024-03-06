#include "gpio.h"
#include <QDebug>
#include <QCoreApplication>
void Gpio::createGPIO(int n)
{
    QString gpio_file, gpio_num;
    QFile exportFile;
    QByteArray  ba;
    gpio_num = QString::number(n);
    gpio_file = "/sys/class/gpio/export";
    exportFile.setFileName(gpio_file);
    exportFile.open(QIODevice::WriteOnly);
    ba = gpio_num.toLatin1();
    exportFile.write(ba); 
    if(exportFile.isOpen())
        exportFile.close();
}

void Gpio::getCreateGPIO(int n)
{createGPIO(n);}

void Gpio::changeDirection(QString n, QString mode)
{
    QString direction_file = "/sys/class/gpio/gpio"+n+"/direction";
    QFile exportFile;
    QByteArray  ba;
    exportFile.setFileName(direction_file);
    exportFile.open(QIODevice::WriteOnly);
    ba = mode.toLatin1();
    exportFile.write(ba); 
    if(exportFile.isOpen())
        exportFile.close();
}

void Gpio::getChangeDirection(QString n, QString mode)
{changeDirection(n, mode);}

void Gpio::changeValue(QString n, QString mode)
{
    QString value_file = "/sys/class/gpio/gpio"+n+"/value";
    QFile exportFile;
    QByteArray  ba;
    exportFile.setFileName(value_file);
    exportFile.open(QIODevice::WriteOnly);
    ba = mode.toLatin1();
    exportFile.write(ba); 
    if(exportFile.isOpen())
        exportFile.close();
}

void Gpio::getChangeValue(QString n, QString mode)
{changeValue(n,mode);}

void Gpio::changeActiveLow(QString n, QString mode)
{
    QString activeLow_file = "/sys/class/gpio/gpio"+n+"/active_low";
    QFile exportFile;
    QByteArray  ba;
    exportFile.setFileName(activeLow_file);
    exportFile.open(QIODevice::WriteOnly);
    ba = mode.toLatin1();
    exportFile.write(ba); 
    if(exportFile.isOpen())
        exportFile.close();
}

void Gpio::getChangeActiveLow(QString n, QString mode)
{changeActiveLow(n, mode);}

void Gpio::delGPIO(int n)
{
    QString gpio_file, gpio_num;
    QFile exportFile;
    QByteArray  ba;
    gpio_num = QString::number(n);
    gpio_file = "/sys/class/gpio/unexport";
    exportFile.setFileName(gpio_file);
    exportFile.open(QIODevice::WriteOnly);
    ba = gpio_num.toLatin1();
    exportFile.write(ba); 
    if(exportFile.isOpen())
        exportFile.close();
}

void Gpio::getDelGPIO(int n)
{delGPIO(n);}

QString Gpio::allCreate()
{   QString jsonArr;
    for (int i = 0; i<288; i++)
    {
        createGPIO(i);
        QString filename="/sys/class/gpio/gpio"+QString::number(i)+"/value";
        QFile file;
        file.setFileName(filename);
        file.open(QIODevice::WriteOnly);
        if(file.isOpen())
        {
            jsonArr += QString::number(i)+",";
        }
        if(file.isOpen())
            file.close();
    }
    allDel();
    return jsonArr;
}

QString Gpio::getAllCreate()
{return allCreate();}

void Gpio::allDel()
{
    for (int i=0; i<288; i++)
    {
        delGPIO(i);
        QString filename1="/sys/class/gpio/gpio"+QString::number(i)+"/value";
        QFile file1;
        file1.setFileName(filename1);
        file1.open(QIODevice::WriteOnly);
        if(file1.isOpen())
        {
            qDebug() << "GPIO" << QString::number(i) << " not deleted";
        }
        if(file1.isOpen())
            file1.close();
    }
}

void Gpio::getAllDel()
{allDel();}

QJsonObject Gpio::GPIOModeChek(QString n)
{
    
    QString filename="/sys/class/gpio/gpio"+n+"/value";
    QFile file;
    QJsonObject chek;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen())
    {
        chek.insert("statusGPIO","closed");
    }
    else
    {
        QString value, activeLow, direction;
        QTextStream in(&file);
        value = in.readLine();
        if(file.isOpen())
            file.close();
        filename="/sys/class/gpio/gpio"+n+"/direction";
        file.setFileName(filename);
        file.open(QIODevice::ReadOnly);
        QTextStream in1(&file);
        direction = in1.readLine();
        if(file.isOpen())
            file.close();
        filename="/sys/class/gpio/gpio"+n+"/active_low";
        file.setFileName(filename);
        file.open(QIODevice::ReadOnly);
        QTextStream in2(&file);
        activeLow = in2.readLine();
        if(file.isOpen())
            file.close();
        chek.insert("chekMode","GPIO");
        chek.insert("value", value);
        chek.insert("direction", direction);
        chek.insert("activeLow", activeLow);
    }
    return chek;
}

QJsonObject Gpio::getGPIOModeChek(QString n)
{return GPIOModeChek(n);}