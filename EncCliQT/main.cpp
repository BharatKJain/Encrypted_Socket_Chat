#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080
using namespace std;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    //w.setObjectName("Client");
    w.show();

    return a.exec();
}
