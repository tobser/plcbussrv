#ifndef TCPSERV_H
#define TCPSERV_H

#include <QObject>
#include <QTcpServer>
QT_USE_NAMESPACE

class TcpServ : public QObject
{
    Q_OBJECT

    public:
        TcpServ(int tcpPort, QObject *parent = 0);
        ~TcpServ();

   public slots:
        void distributeData(QByteArray data);

   signals:
        void newData(QByteArray);

   private slots:
        void onNewConnection();
        void onClientDisconnected();
        void onClientReadyRead();

    private:
        QString getClientAddressStr(QTcpSocket* client);
        QTcpServer  m_server;
        QList<QTcpSocket*> m_clients;
};

#endif
