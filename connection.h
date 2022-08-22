#ifndef CONNECTION_H
#define CONNECTION_H
#include <QTcpSocket>
#include <QByteArray>
#include <QHostAddress>
#include <QWidget>
#include "encoding.h"

class Connection : public QWidget {
    Q_OBJECT

    QTcpSocket *tcp;
public:
    static std::string trans(const QByteArray&);
    static QByteArray trans(const std::string&);
    explicit Connection(QWidget *parent);
    ~Connection();
private slots:
    void readData();
public slots:
    void connectTo(QHostAddress ip, unsigned short port);
    void disconnect();
    void sendMessage(const QByteArray &message);
    void sendData(const Encoding::Data &data);
signals:
    void connected();
    void disconnected();
    void receivedMessage(QByteArray message);
    void receivedData(Encoding::Data data);
};

#endif // CONNECTION_H
