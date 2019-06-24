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
using std::cout;
using std::cin;
using std::endl;
#include <stdio.h>
#include <string.h>
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

void MainWindow::EncStart()
{
    AutoSeededRandomPool prng;
    prng.GenerateBlock(key, sizeof(key));
    prng.GenerateBlock(iv, sizeof(iv));
    encoded.clear();
    StringSource(key, sizeof(key), true,
                 new HexEncoder(
                     new StringSink(encoded)
                     ) /* HexEncoder*/
    ); // StringSource
    ui->textEdit->append(QString("key: "));
    ui->textEdit->append(QString(encoded.c_str()));
    send(sock,key,sizeof(key),0);
    read(sock,temp,sizeof(temp));
    if(strcmp(temp,"key"))
    {
        send(sock,iv,sizeof(iv),0);
    }
    // Pretty print iv
    encoded.clear();
    StringSource(iv, sizeof(iv), true,
        new HexEncoder(
            new StringSink(encoded)
        ) // HexEncoder
    ); // StringSource
    ui->textEdit->append(QString("iv: "));
    ui->textEdit->append(QString(encoded.c_str()));
    ui->textEdit->append(QString("END Of Start--------"));

/*    try
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

    ui->textEdit->append(QString(cipher.c_str()));
    ui->textEdit->append(QString("Sending!"));
    strcpy(temp,cipher.c_str());
    send(sock,temp,sizeof(temp),0);*/
}
void MainWindow::on_pushButton_clicked()
{
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
   send(sock , Message , strlen(Message) , 0 );
   ui->textEdit->append(QString(cipher.c_str()));
   ui->textEdit->append(QString("Sending!"));
   char buff[1024];
   bzero(buff, MAX);
   cipher.clear();
   // read the message from client and copy it in buffer
   read(sock, buff, sizeof(buff));
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
   // print buffer which contains the client contents
   ui->textEdit_3->append(QString("Message Count: "));
   sprintf(str,"%d",mcount);
   ui->textEdit_3->append(QString(str));
   mcount++;
   ui->textEdit_3->append(QString("CIPHER: "));
   ui->textEdit_3->append(QString(cipher.c_str()));
   ui->textEdit_3->append(QString("Message: "));
   ui->textEdit_3->append(QString(buff));
   //ui->textEdit->append(QString("\nEnter Data for Server : "));
   bzero(buff, MAX);
   recovered.clear();
   plain.clear();
   cipher.clear();
   bzero(Message,sizeof(Message));
   bzero(buff,sizeof(buff));
    return;
}
void MainWindow::on_pushButton_2_clicked()
{
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
    EncStart();
}

void MainWindow::on_pushButton_3_clicked()
{
    ::close(sock);
}
