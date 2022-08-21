#include "connection.h"
#include <QDebug>
Connection::Connection(QWidget *parent = 0) : QWidget(parent) {
    tcp = new QTcpSocket(this);
    connect(tcp, &QTcpSocket::connected, this, [this] {
        qDebug() << "connected to the host";
        connected();
    });
    connect(tcp, &QTcpSocket::disconnected, this, [this]{
        qDebug() << "disconnected to the host";
        disconnected();
    });
    connect(tcp, &QTcpSocket::readyRead, this, [this]{
        QByteArray message = tcp->readAll();
        receivedMessage(message);
    });
}

void Connection::connectTo(QHostAddress ip, unsigned short port) {
    tcp->connectToHost(ip, port);
}

void Connection::disconnect() {
    tcp->close();
}

void Connection::sendMessage(const QByteArray &message) {
    tcp->write(message);
    qDebug() << "send message to host";
}
