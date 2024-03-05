#include "readData.h"


int readData::readFreq()
{
    QFile file("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open";
    }
    QString freqs;
    QTextStream in(&file);
    freqs = in.readLine();
    file.close();
    int freq = freqs.toInt();
    return freq;
}

double readData::readTemp()
{
    QFile file("/sys/class/thermal/thermal_zone1/temp");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open";
    }
    QString temps;
    QTextStream in(&file);
    temps = in.readLine();
    file.close();
    double temp = temps.toDouble()/1000;
    return temp;
}


