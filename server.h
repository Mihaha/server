#ifndef SERVER_H
#define SERVER_H

//#include "readData.h"
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QFile>
#include <QString>

class server: public QTcpServer
{
	Q_OBJECT
public:
	server();
	~server();
    QByteArray json(int freq, double temp);
	QTimer* timer;
	QTcpSocket* socket;
	QByteArray Data;
	QByteArray Data2;
	QJsonDocument doc;
	void sendFreqTemp();
	bool socOpen();

public slots:
	void startServer();
	void incomingConnection(qintptr socketDescriptor);
	void sockReady();
	void sockDisk();
};



#endif