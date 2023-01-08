#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
  connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_lineEdit_returnPressed()
{
    qDebug() << "send...";
    SendToServer(ui->lineEdit->text());
    qDebug() << "end send!";
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "send...";
    SendToServer(ui->lineEdit->text());
    qDebug() << "end send!";
}


void MainWindow::on_pushButton_clicked()
{
    qDebug() << "connecting.......";
    socket->connectToHost("127.0.0.1", 2323);   //   127.0.0.1 (???)
    qDebug() << "end connecting";

}

void MainWindow::SendToServer(QString str)
{
  Data.clear();                                   // зарание чистим массив байтов

  QDataStream out(&Data, QIODevice::WriteOnly);   // массив байтов и режим работы (::WriteOnly) <- для работоспособности
  out.setVersion(QDataStream::Qt_5_2);            // версия
  out << str;
  socket->write(Data);
  ui->lineEdit->clear();
}

void MainWindow::slotReadyRead()
{
  ui->textBrowser->append("sas:\t");
  qDebug() << "OK";
  QDataStream in(socket);
  in.setVersion(QDataStream::Qt_5_2);
  if(in.status() == QDataStream::Ok)
    {
      qDebug() << "OK";
      QString str;
      in >> str;
      ui->textBrowser->append(str);
    }
  else
    ui->textBrowser->append("read error");
}

