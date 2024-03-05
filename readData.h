    #ifndef READDATA_H
    #define READDATA_H

    #include <QTimer>
    #include <QCoreApplication>
    #include <QDebug>
    #include <QFile>
    #include <QTextStream>
    #include <QString>
    #include <iostream>
    #include <QJsonDocument>
    #include <QJsonObject>
    #include <QJsonParseError>


    class readData : public QObject
    {
        Q_OBJECT
    public:
        int readFreq();
        double readTemp();
        QByteArray json(int freq, double temp);
        QByteArray Data;
    };

    #endif