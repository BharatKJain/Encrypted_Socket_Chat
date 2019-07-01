
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
        return;
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
    RSASetup();
}
void MainWindow::RSASetup()
{
    try
    {
        AutoSeededRandomPool rng;
        std::string encoded;
        //InvertibleRSAFunction parameters;
        //parameters.GenerateRandomWithKeySize( rng, 1024 );
        RSA::PrivateKey privateKey;
       // RSA::PublicKey publicKey;
        //DecodePublicKey("rsa-public.key", publicKey);
        DecodePrivateKey("rsa-private.key",privateKey);
        string plain="RSA Encryption", cipher, recovered;
        bzero(temp,sizeof(temp));
        read(new_socket,temp,sizeof(temp));
        cipher=temp;
        // Decryption
        RSAES_OAEP_SHA_Decryptor d( privateKey );
        StringSource( cipher, true,
            new PK_DecryptorFilter( rng, d,
                new StringSink( recovered )
            ) // PK_EncryptorFilter
         ); // StringSource
        cout<<recovered<<endl;
        //assert( plain == recovered );
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
    ::close(server_fd);
}
