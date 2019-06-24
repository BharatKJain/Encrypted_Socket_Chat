
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include "mainwindow.h"
#include <QLabel>
#include <QTextEdit>
#include "ui_mainwindow.h"
#include <QPushButton>
#define MAX 80
#define PORT 8080

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
    char buff[1024],str[10];
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(new_socket, buff, sizeof(buff));
        // print buffer which contains the client contents
        ui->textEdit_3->append(QString("Message Count: "));
        sprintf(str,"%d",mcount);
        ui->textEdit_3->append(QString(str));
        mcount++;
        ui->textEdit_3->append(QString("Message: "));
        ui->textEdit_3->append(QString(buff));
       // ui->textEdit->append(QString("\nEnter Data for Client : "));
        bzero(buff, MAX);
    QString text=ui->textEdit_2->toPlainText();
      QByteArray ba = text.toLocal8Bit();
       char *c_str2 = ba.data();
       strcpy(Message,c_str2);
       send(new_socket , Message , strlen(Message) , 0 );
      // std::cout<<c_str2;
      return;
 //   cout<<"It was clicked";
 //   ui->textEdit_3->setText(text);
}

void MainWindow::on_pushButton_2_clicked()
{
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server, Send data Client";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        ui->textEdit->append(QString("Socket Failed!"));
        exit(EXIT_FAILURE);
    }
    else {
        ui->textEdit->append(QString("Socket Created!"));
    }
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                &opt, sizeof(opt)))
    {
        perror("setsockopt");
        ui->textEdit->append(QString("setSockopt Failed!"));
        exit(EXIT_FAILURE);
    }
    else {
        ui->textEdit->append(QString("setSockopt Successful!"));
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                sizeof(address))<0)
    {
        perror("bind failed");
        ui->textEdit->append(QString("Bind Failed!"));
        exit(EXIT_FAILURE);
    }
    else {
        ui->textEdit->append(QString("Bind Successful!"));
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        ui->textEdit->append(QString("Listen Failed!"));
        exit(EXIT_FAILURE);
    }
    else {
        ui->textEdit->append(QString("Listening..."));
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                    (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        ui->textEdit->append(QString("Accept Failed!"));
        exit(EXIT_FAILURE);
    }
    else {
        ui->textEdit->append(QString("Connection Accepted!"));
    }
    mcount=1;
}

void MainWindow::on_pushButton_3_clicked()
{
    ::close(server_fd);
}
