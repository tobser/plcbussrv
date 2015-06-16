#include "serial.h"
#include "log.h"

#include <QCoreApplication>
#include <QObject>
#include <QtSerialPort/QtSerialPort>

QT_USE_NAMESPACE

Serial::Serial(QString portName, QObject *parent)
    : QObject(parent)
{
    m_serialPort.setPortName(portName);
    m_serialPort.setBaudRate(QSerialPort::Baud9600);

    if (!m_serialPort.open(QIODevice::ReadWrite)) {
        WARN( QObject::tr("Failed to open port %1, error: %2")
                                    .arg(portName)
                                    .arg(m_serialPort.errorString()));
       exit(1);
    }
    connect(&m_serialPort, SIGNAL(readyRead()), SLOT(handleReadyRead()));
    connect(&m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)),
            SLOT(handleError(QSerialPort::SerialPortError)));
}

Serial::~Serial() { }

void Serial::handleReadyRead()
{
    while (m_serialPort.bytesAvailable() >= 9){
        QByteArray d = m_serialPort.read(9);
        INFO("<B " + QString(d.toHex()));
        emit (newData(d));
    }
}

void Serial::writeToDevice(QByteArray data)
{
    m_serialPort.write(data);
    INFO(">B " + QString(data.toHex()));
    // docs for 1141 state to write twice to bus with a delay of
    // 12.5ms in between, but I could not notice any difference
    // in the systems behavior... 
    ////    QThread::usleep(12500);
    ////    m_serialPort.write(data);
    ////    INFO(">B " + QString(data.toHex()));
}

void Serial::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        WARN( QObject::tr("An I/O error occurred while reading the data from port %1, error: %2")
            .arg(m_serialPort.portName())
            .arg(m_serialPort.errorString()));
        QCoreApplication::exit(1);
    }
}
