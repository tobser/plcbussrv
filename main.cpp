/* 
 * creates a class to read/write the serial device.
 * creates a tcp server.
 *
 * read events of both are connected to the write method
 * of the other.
 * */

#include "serial.h"
#include "tcpserv.h"
#include "log.h"


#include <QTextStream>
#include <QCoreApplication>
#include <QFile>
#include <QObject>
#include <QStringList>

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QCoreApplication coreApplication(argc, argv);
    int argumentCount = QCoreApplication::arguments().size();
    QStringList argumentList = QCoreApplication::arguments();

    QTextStream standardOutput(stdout);

    if (argumentCount == 1) {
        WARN(QObject::tr("Usage: %1 <serialportname> <tcpport>").arg(argumentList.first()) );
        return 1;
    }

    QString serialPortName = argumentList.at(1);
    int tcpPort = argumentList.at(2).toInt();


    TcpServ* tcpServ = new TcpServ(tcpPort);
    Serial* serial = new Serial(serialPortName);

    QObject::connect(serial, SIGNAL(newData(QByteArray)),
                     tcpServ, SLOT(distributeData(QByteArray)));

    QObject::connect(tcpServ, SIGNAL(newData(QByteArray)),
                     serial, SLOT(writeToDevice(QByteArray)));

    INFO("started.");
    return coreApplication.exec();
}
