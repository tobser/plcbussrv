#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QtSerialPort/QtSerialPort>
#include <QTextStream>
#include <QByteArray>

QT_USE_NAMESPACE


class Serial : public QObject
{
    Q_OBJECT

    public:
        Serial(QString serialPort, QObject *parent = 0);
        ~Serial();

    signals:
        void newData(QByteArray);

    public slots:
        void writeToDevice(QByteArray data);


    private slots:
        void handleReadyRead();
        void handleError(QSerialPort::SerialPortError error);

    private:
        QSerialPort m_serialPort;
        QByteArray  m_readData;
        QTextStream m_stdout;
};

#endif
