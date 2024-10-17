//
// Created by Kiana on 2024/5/15.
//

#ifndef RFID_WORK_MYTCP_H
#define RFID_WORK_MYTCP_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDebug>
#include <QStringList>

class MyTCP : public QObject
{
Q_OBJECT
public:
    MyTCP(QObject *parent = nullptr);

    void TCP_SEND(QString data);

    const QString &getRfidCardId() const;

    const QString &getRfidInitId() const;

    void rfid_card_clean();

    signals:
    void sig_get_rfid_card(QString id,QString class_num);

    void sig_get_init_rfid_card(QString str);

    void sig_init_false_true(bool flag);

    void get_rfid_card(QString id,QString classroom);

public slots:
    void onNewConnection();

    void onReadyRead();

private:

    int getID(QByteArray line);

    QTcpServer *server;

    QTcpSocket *clientSocket;

    QString rfid_card_id;

    QString rfid_init_id;


};

#endif //RFID_WORK_MYTCP_H
