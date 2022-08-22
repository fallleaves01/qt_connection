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
    connect(con, &Connection::receivedData, this, [this](Encoding::Data data) {
        qDebug() << "接收到信息：" << data.getContent().c_str();
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
        Encoding::Data d(0, 0, 1, "17:41", Connection::trans(message));
        con->sendData(d);
        //con->sendMessage(message);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete con;
}
