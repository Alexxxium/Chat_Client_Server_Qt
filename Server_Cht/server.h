#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class Server: public QTcpServer
{
  Q_OBJECT                      // для использования сигнальных слотовых связей

public:
  Server();
  QTcpSocket *socket;          // сокет для каждого нового подключения

private:
  QVector <QTcpSocket*> Sockets;    // все новые подключения
  QByteArray Data;                  // информация для клиент-сервера
  void SendToClient(QString str);   // функция для передачи данных клиенту (строки)

public slots:
  void incomingConnection(qintptr socketescriptor);    // обработчик новых подключений
  void slotReadyRead();                               // обработчик полученных от клиента сообщений

};

#endif // SERVER_H
