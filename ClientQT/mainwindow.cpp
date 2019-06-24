#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <iostream>
#include <stdio.h>
#include <string.h>
#define PORT 8080
#define MAX 80
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   QString text=ui->textEdit_2->toPlainText();
   QByteArray ba = text.toLocal8Bit();
   char str[10],*c_str2 = ba.data();
   strcpy(Message,c_str2);
   send(sock , Message , strlen(Message) , 0 );
   std::cout<<c_str2;
   char buff[1024];
   bzero(buff, MAX);
   // read the message from client and copy it in buffer
   read(sock, buff, sizeof(buff));
   // print buffer which contains the client contents
   ui->textEdit_3->append(QString("Message Count: "));
   sprintf(str,"%d",mcount);
   ui->textEdit_3->append(QString(str));
   mcount++;
   ui->textEdit_3->append(QString("Message: "));
   ui->textEdit_3->append(QString(buff));
   //ui->textEdit->append(QString("\nEnter Data for Server : "));
   bzero(buff, MAX);
    return;
}
void MainWindow::on_pushButton_2_clicked()
{
    //char *hello = "Hello from client";
    //char buffer[1024] = {0};
    //int valread;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout<<"\n Socket creation error \n";
        ui->textEdit->append(QString("Socket Creation Error!"));
        return;
    }
    else {
        ui->textEdit->append(QString("Socket Created!"));
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        cout<<"\nInvalid address/ Address not supported \n";
        ui->textEdit->append(QString("Invalid address// Address not supported \\"));
        return ;
    }
    else {
        ui->textEdit->append(QString("Valid Address..."));
    }
    if (::connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        cout<<"\nConnection Failed \n";
        ui->textEdit->append(QString("Connection Failed"));
        return;
    }
    else {
        ui->textEdit->append(QString("Connection Successful!"));
    }
    ui->textEdit->append(QString("Enter Data for Server..."));
    mcount=1;
}

void MainWindow::on_pushButton_3_clicked()
{
    ::close(sock);
}
