#ifndef GPIO_H
#define GPIO_H

#include <QFile>
#include <QString>
#include <QJsonObject>
    
class Gpio : public QObject
{
    Q_OBJECT
    public:
        
        QString getAllCreate();
        QJsonObject getGPIOModeChek(QString n);
        void getCreateGPIO(int n);
        void getDelGPIO(int n);
        void getAllDel();
        void getChangeDirection(QString n, QString mode);
        void getChangeValue(QString n, QString mode);
        void getChangeActiveLow(QString n, QString mode);

    private:
        QString allCreate();
        QJsonObject GPIOModeChek(QString n);
        void createGPIO(int n);
        void delGPIO(int n);
        void allDel();
        void changeDirection(QString n, QString mode);
        void changeValue(QString n, QString mode);
        void changeActiveLow(QString n, QString mode);
};
#endif