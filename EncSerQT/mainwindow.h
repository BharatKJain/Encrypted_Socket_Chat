#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
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
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    char Message[1000], buff[1024],str[10],temp[200];
    int server_fd, new_socket, valread,mcount;
    struct sockaddr_in address;
    CryptoPP::byte key[AES::DEFAULT_KEYLENGTH];
    CryptoPP::byte iv[AES::BLOCKSIZE];
    std::string cipher, encoded, recovered,plain;
    //CBC_Mode< AES >::Decryption d;
    void EncStart();
    ~MainWindow();
    //void connection();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
