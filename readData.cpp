#include "readData.h"


int ReadData::readFreq()
{
    QFile file("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open";
        return 0;
    }
    QString freqs;
    QTextStream in(&file);
    freqs = in.readLine();
    if(file.isOpen())
        file.close();
    int freq = freqs.toInt();
    return freq;
}

double ReadData::readTemp()
{
    QFile file("/sys/class/thermal/thermal_zone1/temp");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open";
        return 0;
    }
    QString temps;
    QTextStream in(&file);
    temps = in.readLine();
    if(file.isOpen())
        file.close();
    double temp = temps.toDouble()/1000;
    return temp;
}

int ReadData::getReadFreq()
{return readFreq();}
double ReadData::getReadTemp()
{return readTemp();}