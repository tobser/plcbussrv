#include "tcpserv.h"
#include "log.h"
#include <QCoreApplication>
#include <QTcpSocket>

    TcpServ::TcpServ(int tcpPort, QObject *parent)
:QObject(parent)
{
    if(!m_server.listen(QHostAddress::LocalHost, tcpPort))
    {
        WARN(QObject::tr("Unable to start the server: %1.")
                .arg(m_server.errorString()));
        exit(1);
    }
    connect(&m_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

TcpServ::~TcpServ() { }

void TcpServ::onNewConnection(){
    QTcpSocket * client = m_server.nextPendingConnection();
    if (client == 0)
        return;

    INFO(QString("Got new connection ") + client->peerName()) ;
    m_clients.append(client);
    connect (client, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
    connect (client, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
}

void TcpServ::onClientDisconnected(){
    QTcpSocket* client = (QTcpSocket*) sender();
    INFO(QString("connection gone") + client->peerName()) ;
    int idx = m_clients.indexOf(client);
    if (idx < 0 )
    {
        WARN("could not remove connection ");
        return;
    }
    m_clients.removeAt(idx);
    client->deleteLater();
}

QString TcpServ::getClientAddressStr(QTcpSocket* c){
    return c->peerAddress().toString() +":" + QString::number(c->peerPort());
}

void TcpServ::onClientReadyRead()
{
    QTcpSocket* client = (QTcpSocket*) sender();
    QByteArray data = client->read(8);

    INFO("RX CLI " + QString(data.toHex()) + "    " + getClientAddressStr((client)));
    emit(newData(data));
}

void TcpServ::distributeData(QByteArray data){
    QList<QTcpSocket*>::iterator i;
    for (i = m_clients.begin(); i != m_clients.end(); ++i)
    {
        INFO("TX CLI " + QString(data.toHex()) + "  " + getClientAddressStr((*i)));
        (*i)->write(data);
    }
}
