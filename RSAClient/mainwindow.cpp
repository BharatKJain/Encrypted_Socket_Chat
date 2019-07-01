#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
//#include <iostream>
#include <stdio.h>
//#include <string.h>
//RSA Headers
#include "stdafx.h"
#include "cryptopp/queue.h"
using CryptoPP::ByteQueue;
#include "cryptopp/asn.h"
using CryptoPP::BufferedTransformation;
#include "cryptopp/rsa.h"
using CryptoPP::RSA;
using CryptoPP::InvertibleRSAFunction;
using CryptoPP::RSAES_OAEP_SHA_Encryptor;
using CryptoPP::RSAES_OAEP_SHA_Decryptor;

#include "cryptopp/sha.h"
using CryptoPP::SHA1;

#include "cryptopp/filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::PK_EncryptorFilter;
using CryptoPP::PK_DecryptorFilter;

#include "cryptopp/files.h"
using CryptoPP::FileSink;
using CryptoPP::FileSource;

#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include "cryptopp/secblock.h"
using CryptoPP::SecByteBlock;

#include "cryptopp/cryptlib.h"
using CryptoPP::Exception;
using CryptoPP::DecodingResult;

#include <string>
using std::string;

#include <exception>
using std::exception;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <assert.h>
//RSA End
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
    cout<<"HELLO";
    RSASetup();
}
void MainWindow :: RSASetup()
{
    int i;
    try
    {
        AutoSeededRandomPool rng;
        //std::string encoded;
        //InvertibleRSAFunction parameters;
        //parameters.GenerateRandomWithKeySize( rng, 1024 );
        RSA::PublicKey publicKey;
        DecodePublicKey("rsa-public.key", publicKey);
        string plain="RSA Encryption", cipher, recovered;
        // Encryption
        RSAES_OAEP_SHA_Encryptor e( publicKey );

        StringSource( plain, true,
            new PK_EncryptorFilter( rng, e,
                new StringSink( cipher )
            ) // PK_EncryptorFilter
         ); // StringSource
        cout<<"\nCipher:"<<cipher<<endl;
        bzero(temp,sizeof(temp));
        //strcpy(temp,cipher.c_str());
        for (i = 0; i < 128; i++) {
                temp[i] = cipher[i];
            }
        cout<<"\nCipher in temp:"<<temp;

        send(sock,temp,sizeof(temp),0);
    }
    catch(CryptoPP::Exception& e )
    {
        cerr << "Caught Exception..." << endl;
        cerr << e.what() << endl;
    }
}
void MainWindow::Encode(const string& filename, const BufferedTransformation& bt)
{
    FileSink file(filename.c_str());

    bt.CopyTo(file);
    file.MessageEnd();
}
void MainWindow::EncodePrivateKey(const string& filename, const RSA::PrivateKey& key)
{
    ByteQueue queue;
    key.DEREncodePrivateKey(queue);

    Encode(filename, queue);
}

void MainWindow::EncodePublicKey(const string& filename, const RSA::PublicKey& key)
{
    ByteQueue queue;
    key.DEREncodePublicKey(queue);

    Encode(filename, queue);
}
void MainWindow::Decode(const string& filename, BufferedTransformation& bt)
{
    FileSource file(filename.c_str(), true /*pumpAll*/);

    file.TransferTo(bt);
    bt.MessageEnd();
}
void MainWindow::DecodePrivateKey(const string& filename, RSA::PrivateKey& key)
{
    ByteQueue queue;

    Decode(filename, queue);
    key.BERDecodePrivateKey(queue, false /*paramsPresent*/, queue.MaxRetrievable());
}

void MainWindow::DecodePublicKey(const string& filename, RSA::PublicKey& key)
{
    ByteQueue queue;

    Decode(filename, queue);
    key.BERDecodePublicKey(queue, false /*paramsPresent*/, queue.MaxRetrievable());
}

void MainWindow::on_pushButton_3_clicked()
{
    ::close(sock);
}
