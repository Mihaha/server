#include "server.h"
#include "gpio.h"
#include "readData.h"
Server::Server(){}

Server::~Server(){}

void Server::startServer()
{
	list = new QList<QTcpSocket*>;
	if (this->listen(QHostAddress::Any,5555))
	{
		qDebug() << "listening";
	}
	else
	{
		qDebug()<<"not listening";
	}
	mapper = new QSignalMapper(this);
	mapper2 = new QSignalMapper(this);
	connect(mapper, SIGNAL(mapped(int)), this, SLOT(sockReady(int)));
	connect(mapper2, SIGNAL(mapped(int)), this, SLOT(sockDisc(int)));
}
void Server::incomingConnection(qintptr socketDescriptor)
{
	list->append(new QTcpSocket(this));
	list->last()->setSocketDescriptor(socketDescriptor);
	//connect(list->last(),SIGNAL(readyRead()),this,SLOT(sockReady(n)));
	//connect(list->last(),SIGNAL(disconnected()),this,SLOT(sockDisc(n)));
	mapper->setMapping(list->last(),list->length()-1);
	mapper2->setMapping(list->last(),list->length()-1);
	connect(list->last(),SIGNAL(readyRead()),mapper,SLOT(map()));
	connect(list->last(),SIGNAL(disconnected()),mapper2,SLOT(map()));
	qDebug() << socketDescriptor << "client connected";
	
}
/*
void Server::newConnect()
{
	list->append(tcpServer->nextPendingConnection());
	mapper->setMapping(list->last(),list->length()-1);
	connect(list->last(),SIGNAL(readyRead()),mapper,SLOT(map()));
	connect(list->last(),SIGNAL(dissconnected()),tcpServer,SLOT(sockDisk()));
}
*/
void Server::sockDisc(int n)
{
	list->at(n)->deleteLater();
	qDebug()<<"disconnected";
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

