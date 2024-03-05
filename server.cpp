#include "server.h"
#include "gpio.h"
#include "readData.h"
server::server(){}

server::~server(){}

void server::startServer()
{
	if (this->listen(QHostAddress::Any,5555))
	{
		qDebug() << "listening";
	}
	else
	{
		qDebug()<<"not listening";
	}
}

void server::incomingConnection(qintptr socketDescriptor)
{
	socket = new QTcpSocket(this);
	socket->setSocketDescriptor(socketDescriptor);

	connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
	connect(socket,SIGNAL(dissconnected()),this,SLOT(sockDisk()));

	qDebug() << socketDescriptor << "client connectad";
	
}

void server::sockReady()
{
	Data2 = socket->readAll();
	gpio GP;
	QJsonDocument fromClient = QJsonDocument::fromBinaryData(Data2);
	if((fromClient.object().value("type").toString()=="request")&&(fromClient.object().value("value").toString()=="freqTemp"))
	{
		QJsonObject freqTemp;
		QJsonDocument freqTempDoc;
		readData ft;
		freqTemp.insert("freq",ft.readFreq());
		freqTemp.insert("temp",ft.readTemp());
		freqTempDoc.setObject(freqTemp);
		
		socket->write(freqTempDoc.toBinaryData());
	}
	else if((fromClient.object().value("type").toString()=="request")&&(fromClient.object().value("value").toString()=="GPIO"))
	{
		QJsonObject obj;
		
		QString jsonGPIO = GP.allCreate();
		GP.allDel();
		obj.insert("availableGPIO",jsonGPIO);
		obj.insert("GPIOReady","yes");
		QJsonDocument dc;
		dc.setObject(obj);
		
		socket->write(dc.toBinaryData());
	}
	else if(fromClient.object().value("type").toString()=="create")
	{
		QString numberGPIO = fromClient.object().value("value").toString();
		GP.createGPIO(numberGPIO.toInt());
	}
	else if(fromClient.object().value("type").toString()=="changeMode")
	{
		QString numberGPIO = fromClient.object().value("numberGPIO").toString();
		QString direction = fromClient.object().value("direction").toString();
		QString value = fromClient.object().value("value").toString();
		QString activeLow = fromClient.object().value("activeLow").toString();
		GP.changeDirection(numberGPIO, direction);
		GP.changeValue(numberGPIO, value);
		GP.changeActiveLow(numberGPIO, activeLow);
	}
	else if(fromClient.object().value("type").toString()=="chekMode")
	{
		QString numberGPIO = fromClient.object().value("numberGPIO").toString();
		QJsonObject chekGPIO;
		chekGPIO = GP.GPIOModeChek(numberGPIO);
		QJsonDocument chekGPIODoc;
		chekGPIODoc.setObject(chekGPIO);
		socket->write(chekGPIODoc.toBinaryData());
	}
}

void server::sockDisk()
{
	qDebug()<<"disconnected";
	socket->deleteLater();

}



