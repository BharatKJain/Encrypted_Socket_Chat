
#include <unistd.h>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
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
#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;
#include <string>
using std::string;
#include <cstdlib>
using std::exit;
#include <cryptopp/cryptlib.h>
using CryptoPP::Exception;
#include "cryptopp/hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;
#include "cryptopp/filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
#include "cryptopp/aes.h"
using CryptoPP::AES;
#include "cryptopp/ccm.h"
using CryptoPP::CBC_Mode;
#include "assert.h"
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
void MainWindow::EncStart()
{
    read(new_socket,key,sizeof(key));
    encoded.clear();
    StringSource(key, sizeof(key), true,
        new HexEncoder(
            new StringSink(encoded)
        ) // HexEncoder
    ); // StringSource
    ui->textEdit->append(QString("Key:"));
    ui->textEdit->append(QString(encoded.c_str()));
    send(new_socket,"ok",sizeof("ok"),0);
    read(new_socket,iv,sizeof(iv));
    encoded.clear();
    StringSource(iv, sizeof(iv), true,
        new HexEncoder(
            new StringSink(encoded)
        ) // HexEncoder
    ); // StringSource
    ui->textEdit->append(QString("IV:"));
    ui->textEdit->append(QString(encoded.c_str()));
    ui->textEdit->append(QString("End of start---------"));
    //d.SetKeyWithIV(key, sizeof(key), iv);
    return;
/*
    read(new_socket,temp,sizeof(temp));
    ui->textEdit->append(QString("Recovered Text:"));
    ui->textEdit->append(QString(temp));
    cipher=temp;
    try
    {
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, sizeof(key), iv);
        StringSource s(cipher, true,
            new StreamTransformationFilter(d,
                new StringSink(recovered)
            ) // StreamTransformationFilter
        ); // StringSource

        //cout << "recovered text: " << recovered << endl;
    }
    catch(const CryptoPP::Exception& e)
    {
        cerr << e.what() << endl;
        exit(1);
    }
    ui->textEdit->append(QString("Recovered Text:"));
    ui->textEdit->append(QString(recovered.c_str()));*/


}
void MainWindow::on_pushButton_clicked()
{
    bzero(buff, MAX);
    // read the message from client and copy it in buffer
    read(new_socket, buff, sizeof(buff));

    //Start of decryption
    cipher=buff;
    try
    {
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, sizeof(key), iv);
        StringSource s(cipher, true,
            new StreamTransformationFilter(d,
                new StringSink(recovered)
            ) // StreamTransformationFilter
        ); // StringSource

        //cout << "recovered text: " << recovered << endl;
    }
    catch(const CryptoPP::Exception& e)
    {
        cerr << e.what() << endl;
       // exit(1);
    }
    strcpy(buff,recovered.c_str());
    //end of decryption


    // print buffer which contains the client contents
    ui->textEdit_3->append(QString("Message Count: "));
    sprintf(str,"%d",mcount);
    ui->textEdit_3->append(QString(str));
    mcount++;
    ui->textEdit_3->append(QString("CIPHER: "));
    ui->textEdit_3->append(QString(cipher.c_str()));
    ui->textEdit_3->append(QString("Message: "));
    ui->textEdit_3->append(QString(buff));
    bzero(buff, MAX);
    cipher.clear();
    //SEND DATA CODE:-
    QString text=ui->textEdit_2->toPlainText();
    QByteArray ba = text.toLocal8Bit();
    char *c_str2 = ba.data();
    strcpy(Message,c_str2);
    plain=Message;
    try
    {
        CBC_Mode< AES >::Encryption e;
        e.SetKeyWithIV(key, sizeof(key), iv);
        StringSource s(plain, true,
            new StreamTransformationFilter(e,
                new StringSink(cipher)
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch(const CryptoPP::Exception& e)
    {
        cerr << e.what() << endl;
        exit(1);
    }
    strcpy(Message,cipher.c_str());
    send(new_socket , Message , strlen(Message) , 0 );
    recovered.clear();
    plain.clear();
    cipher.clear();
    bzero(Message,sizeof(Message));
    bzero(buff,sizeof(buff));
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
    EncStart();
}

void MainWindow::on_pushButton_3_clicked()
{
    ::close(server_fd);
}
