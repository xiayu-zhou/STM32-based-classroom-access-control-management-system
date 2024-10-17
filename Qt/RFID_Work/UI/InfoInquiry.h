//
// Created by Kiana on 2024/6/23.
//

#ifndef RFID_WORK_INFOINQUIRY_H
#define RFID_WORK_INFOINQUIRY_H

#include <QWidget>
#include "../Src/MySQL_X.h"

QT_BEGIN_NAMESPACE
namespace Ui { class InfoInquiry; }
QT_END_NAMESPACE

class InfoInquiry : public QWidget {
Q_OBJECT

public:
    explicit InfoInquiry(QWidget *parent = nullptr);

    ~InfoInquiry() override;

    void setMysqlX(MYSQL_X *mysqlX);

public slots:
    void on_clicked();

private:
    Ui::InfoInquiry *ui;
    MYSQL_X *mysqlX = nullptr;
    QVector<QStringList> info;
};


#endif //RFID_WORK_INFOINQUIRY_H
