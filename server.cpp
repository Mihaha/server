#include "server.h"
#include "gpio.h"
#include "readData.h"
Server::Server(){}

Server::~Server(){}

void Server::startServer()
{
	tcpServer = new QTcpServer;
	list = new QList<QTcpSocket*>;
	mapper = new QSignalMapper(this);
	connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnect()));
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(sockReady(int)));
	if (tcpServer->listen(QHostAddress::Any,5555))
	{
		qDebug() << "listening";
	}
	else
	{
		qDebug()<<"not listening";
	}
}

void Server::newConnect()
{
	list->append(tcpServer->nextPendingConnection());
	mapper->setMapping(list->last(),list->length()-1);
	connect(list->last(),SIGNAL(readyRead()),mapper,SLOT(map()));
}


void Server::sockReady(int n)
{
	Data2 = list->at(n)->readAll();
	Gpio GP;
	QJsonDocument fromClient = QJsonDocument::fromBinaryData(Data2);
	if((fromClient.object().value("type").toString()=="request")&&(fromClient.object().value("value").toString()=="freqTemp"))
	{
		QJsonObject freqTemp;
		QJsonDocument freqTempDoc;
		ReadData ft;
		freqTemp.insert("freq",ft.getReadFreq());
		freqTemp.insert("temp",ft.getReadTemp());
		freqTempDoc.setObject(freqTemp);
		
		if (list->at(n)->isWritable())
			list->at(n)->write(freqTempDoc.toBinaryData());
	}
	else if((fromClient.object().value("type").toString()=="request")&&(fromClient.object().value("value").toString()=="GPIO"))
	{
		QJsonObject obj;
		
		QString jsonGPIO = GP.getAllCreate();
		GP.getAllDel();
		obj.insert("availableGPIO",jsonGPIO);
		obj.insert("GPIOReady","yes");
		QJsonDocument dc;
		dc.setObject(obj);
		if (list->at(n)->isWritable())
			list->at(n)->write(dc.toBinaryData());
	}
	else if(fromClient.object().value("type").toString()=="create")
	{
		QString numberGPIO = fromClient.object().value("value").toString();
		GP.getCreateGPIO(numberGPIO.toInt());
	}
	else if(fromClient.object().value("type").toString()=="changeMode")
	{
		QString numberGPIO = fromClient.object().value("numberGPIO").toString();
		QString direction = fromClient.object().value("direction").toString();
		QString value = fromClient.object().value("value").toString();
		QString activeLow = fromClient.object().value("activeLow").toString();
		GP.getChangeDirection(numberGPIO, direction);
		GP.getChangeValue(numberGPIO, value);
		GP.getChangeActiveLow(numberGPIO, activeLow);
	}
	else if(fromClient.object().value("type").toString()=="chekMode")
	{
		QString numberGPIO = fromClient.object().value("numberGPIO").toString();
		QJsonObject chekGPIO;
		chekGPIO = GP.getGPIOModeChek(numberGPIO);
		QJsonDocument chekGPIODoc;
		chekGPIODoc.setObject(chekGPIO);
		
		if (list->at(n)->isWritable())
			list->at(n)->write(chekGPIODoc.toBinaryData());
	}
}

void Server::sockDisk()
{
	qDebug()<<"disconnected";
	socket->deleteLater();

}