#ifndef GPIO_H
#define GPIO_H

#include <QFile>
#include <QString>
#include <QJsonObject>
    
class gpio : public QObject
{
    Q_OBJECT
    public:
        void createGPIO(int n);
        void delGPIO(int n);
        QString allCreate();
        void allDel();
        void changeDirection(QString n, QString mode);
        void changeValue(QString n, QString mode);
        void changeActiveLow(QString n, QString mode);
        QJsonObject GPIOModeChek(QString n);
};
#endif