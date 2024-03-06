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


    class ReadData : public QObject
    {
        Q_OBJECT
    public:
        int getReadFreq();
        double getReadTemp();
    private:
        int readFreq();
        double readTemp();
    };

    #endif