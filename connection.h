#ifndef CONNECTION_H
#define CONNECTION_H
#include <QTcpSocket>
#include <QByteArray>
#include <QHostAddress>
#include <QWidget>

class Connection : public QWidget {
    Q_OBJECT

    QTcpSocket *tcp;
public:
    explicit Connection(QWidget *parent);
public slots:
    void connectTo(QHostAddress ip, unsigned short port);
    void disconnect();
    void sendMessage(const QByteArray &message);
signals:
    void connected();
    void disconnected();
    void receivedMessage(QByteArray message);
};

#endif // CONNECTION_H
