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
#include <QList>
#include <QSignalMapper>

class Server: public QObject
{
	Q_OBJECT
public:
	Server();
	~Server();
	QByteArray Data2;
	QJsonDocument doc;

public slots:
	void startServer();
	//void incomingConnection(qintptr socketDescriptor);
	void newConnect();
	void sockReady(int n);
	void sockDisk();
private:
	QTcpSocket* socket;
	QTcpServer* tcpServer;
	QList<QTcpSocket*> *list;
	QSignalMapper* mapper;
};

#endif