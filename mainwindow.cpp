#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QByteArray>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->disconnectButton->setEnabled(false);
    setWindowTitle("测试器");
    con = new Connection(this);
    connect(con, &Connection::connected, this, [this]() {
        qDebug() << "服务端连接成功";
        ui->connectButton->setEnabled(false);
        ui->disconnectButton->setEnabled(true);
    });
    connect(con, &Connection::disconnected, this, [this]() {
        qDebug() << "服务器断开连接";
        ui->connectButton->setEnabled(true);
        ui->disconnectButton->setEnabled(false);
    });
    connect(con, &Connection::receivedMessage, this, [this](QByteArray message) {
        qDebug() << "接收到信息：" << message;
    });
    connect(ui->connectButton, &QPushButton::clicked, this, [this]() {
        QString ip = ui->ipText->text();
        unsigned short port = ui->portText->text().toInt();
        con->connectTo(QHostAddress(ip), port);
    });
    connect(ui->disconnectButton, &QPushButton::clicked, this, [this]() {
        con->disconnect();
    });

    connect(ui->sendButton, &QPushButton::clicked, this, [this]() {
        QByteArray message = ui->messageText->toPlainText().toUtf8();
        con->sendMessage(message);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
