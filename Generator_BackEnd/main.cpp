#include "Generator.h"

#include "mainwindow.h"
#include <QApplication>

using namespace std;

void TestConnection(){
   Generator G1;
   cout<< G1.SETconnect("COM", "9600", "8", "1" , "NO", "NO", "DS345") <<endl;  // Generator(const std::string &portName, const std::string &baudrate, const std::string &dataBit, const std::string &stopBit, const std::string &parity, const std::string &flowcontrol, const std::string &new_generatorModel = "");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    TestConnection();

    return a.exec();
}
