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
#include <QObject>

class Server: public QTcpServer
{
	Q_OBJECT
public:
	Server();
	~Server();
	QByteArray Data2;
	QJsonDocument doc;

public slots:
	void startServer();
	void incomingConnection(qintptr socketDescriptor);
	//void newConnect();
	void sockReady(int n);
	void sockDisc(int n);
	//void sockDisconnect(int n);

private:
	QTcpSocket* socket;
	QList<QTcpSocket*> *list;
	QSignalMapper* mapper;
	QSignalMapper* mapper2;
};

#endif