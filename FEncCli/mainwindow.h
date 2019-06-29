#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <sys/socket.h>
#include <netdb.h>
#include<iostream>
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
using CryptoPP::BufferedTransformation;
#include "cryptopp/aes.h"
using CryptoPP::AES;
#include "cryptopp/ccm.h"
using CryptoPP::CBC_Mode;
#include "assert.h"
//RSA
#include "stdafx.h"

#include "cryptopp/rsa.h"
using CryptoPP::RSA;
using CryptoPP::InvertibleRSAFunction;
using CryptoPP::RSAES_OAEP_SHA_Encryptor;
using CryptoPP::RSAES_OAEP_SHA_Decryptor;
//
#define PORT 8080
#define MAX 80
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    char Message[1000],buff[1024],str[10],temp[5000];
    int sock = 0, valread,mcount,i;
        struct sockaddr_in serv_addr;
        CryptoPP::byte key[AES::DEFAULT_KEYLENGTH];
        CryptoPP::byte iv[AES::BLOCKSIZE];
        std::string cipher, encoded, recovered,plain;
        void EncStart();
        void Encode(const string&,const BufferedTransformation&);
        void Decode(const string&,BufferedTransformation&);
        void EncodePrivateKey(const string&,const RSA::PrivateKey&);
        void EncodePublicKey(const string&,const RSA::PublicKey&);
        void DecodePrivateKey(const string&,RSA::PrivateKey&);
        void DecodePublicKey(const string&,RSA::PublicKey&);

    ~MainWindow();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
