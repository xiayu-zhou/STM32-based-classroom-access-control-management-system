//
// Created by Kiana on 2024/5/15.
//

#ifndef RFID_WORK_MAIN_H
#define RFID_WORK_MAIN_H

#include <QWidget>
#include <QTimer>
#include <QMessageBox>
#include <QVector>
#include <QDateTime>
#include "MyTCP.h"
#include "MySQL_X.h"
#include "../UI/InfoInquiry.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Main; }
QT_END_NAMESPACE

class Main : public QWidget {
Q_OBJECT

public:
    explicit Main(QWidget *parent = nullptr);

    ~Main() override;
    void from_rfid_open(bool flag,QString class_num);

    QString getNowTime();


public slots:
    void on_init_RFID();

    void on_open_lock();

    void set_now_rfid_card_txt(QString id,QString class_num);

    void set_now_init_rfid_card_txt(QString txt);

    void onTimeout();

    void on_class_num_clicked();

    void on_class_start_init_clicked();

    void init_false_true(bool flag);

    void info_class_num_rfid_card(int index);

    void on_InfoInquiry();

    void have_rfid_card(QString id,QString classroom);

private:
    Ui::Main *ui;

    MYSQL_X *mysql;

    MyTCP *tcp;

    int Error_count;

    bool start_init_flag = false;

    InfoInquiry info;
};


#endif //RFID_WORK_MAIN_H
