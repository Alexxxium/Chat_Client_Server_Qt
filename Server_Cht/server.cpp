#include "server.h"
#include <QDataStream>

Server::Server()
{                                                 // QHostAddress::Any
  if(this->listen(QHostAddress::Any, 2323))       // прослушивание... пришедшие сигналы с любого адреса (::Any), порт №2323
    qDebug() << "start server!";
  else
    qDebug() << "error start server!";
}


void Server::incomingConnection(qintptr socketDescriptor)      // ??????????!!!!!!!!!!
{
  qDebug() << "connecting...";
  socket = new QTcpSocket;
  socket->setSocketDescriptor(socketDescriptor);

  connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
  connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

  Sockets.push_back(socket);
  qDebug() << "client connected!\tdescriptor:\t" << socketDescriptor;
}


void Server::slotReadyRead()
{
  qDebug() << "read...";
  socket = (QTcpSocket*)sender();       // сокет, с которого пришел запрос

  QDataStream in(socket);               // потоковый ввод/вывод информации
  in.setVersion(QDataStream::Qt_5_2);   // версия

  if(in.status() == QDataStream::Ok)    // проверяем состояние объекта in
    {
    qDebug() << "read...";
    QString str;
    in >> str;
    qDebug() << str;
    SendToClient(str);
    }
  else
    qDebug() << "error DataStream!";
}


void Server::SendToClient(QString str)
{
  Data.clear();                                   // зарание чистим массив байтов

  QDataStream out(&Data, QIODevice::WriteOnly);   // массив байтов и режим работы (::WriteOnly) <- для работоспособности
  out.setVersion(QDataStream::Qt_5_2);            // версия
  out << str;
  //socket->write(Data);
  for(int i = 0; i < Sockets.size(); ++i)         // записываем сообщения в каждый сокет
    Sockets[i]->write(Data);
}
