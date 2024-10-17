//
// Created by Kiana on 2024/5/15.
//

#include "MyTCP.h"

MyTCP::MyTCP(QObject *parent) : QObject(parent) {
    server = new QTcpServer(this);

    connect(server, &QTcpServer::newConnection, this, &MyTCP::onNewConnection);
    if (!server->listen(QHostAddress::Any, 7772)) {
        qDebug() << "Server could not start";
    }else {
        qDebug() << "Server could start";
    }
}

void MyTCP::onNewConnection() {
    // 每当有一个新的连接时，这个槽就会被调用
    clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &MyTCP::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);

    qDebug() << "user already connect from IP" << clientSocket->peerAddress();
}

void MyTCP::onReadyRead() {
    if (clientSocket) {
        QByteArray line = clientSocket->readAll();
        qDebug() << "Received: " << line;
        getID(line);
    }
}

void MyTCP::TCP_SEND(QString data) {
    clientSocket->write(data.toStdString().c_str());
}

int MyTCP::getID(QByteArray line) {
    QString str = line;
    QStringList parts = str.split("#");
    if(parts.isEmpty()){
        return 0;
    }else{
        if(parts.at(0) == "o")
        {
            rfid_card_id = parts.at(1);
            if(parts.at(2) == parts.at(3))
                emit sig_get_rfid_card(rfid_card_id,parts.at(2));
            else{
                qDebug() << "parts.at(2) != parts.at(3)";

            }
            emit get_rfid_card(parts.at(1),parts.at(3));
            return 1;
        }else if (parts.at(0) == "i"){
            rfid_init_id = parts.at(1);
            emit sig_get_init_rfid_card(rfid_init_id);
        }else if(parts.at(0) == "f"){
            emit sig_init_false_true(true);
        }else if(parts.at(0) == "e"){
            emit sig_init_false_true(false);
        }
    }
    return 0;
}

const QString &MyTCP::getRfidCardId() const {
    return rfid_card_id;
}

void MyTCP::rfid_card_clean() {
    rfid_init_id = "";
}

const QString &MyTCP::getRfidInitId() const {
    return rfid_init_id;
}







