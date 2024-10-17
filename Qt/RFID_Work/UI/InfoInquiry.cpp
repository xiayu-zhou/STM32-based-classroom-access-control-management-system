//
// Created by Kiana on 2024/6/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_InfoInquiry.h" resolved

#include "InfoInquiry.h"
#include "ui_InfoInquiry.h"


InfoInquiry::InfoInquiry(QWidget *parent) :
        QWidget(parent), ui(new Ui::InfoInquiry) {
    ui->setupUi(this);

    ui->textEdit->setReadOnly(true);
    connect(ui->pushButton,&QPushButton::clicked,this,&InfoInquiry::on_clicked);

}

InfoInquiry::~InfoInquiry() {
    delete ui;
}

void InfoInquiry::setMysqlX(MYSQL_X *mysqlX) {
    InfoInquiry::mysqlX = mysqlX;
}

void InfoInquiry::on_clicked() {
    if(mysqlX != nullptr){
        ui->textEdit->setText("");
        info = mysqlX->readInfoTableData();
        int size = info.size();
        for (int i = 0; i < size; ++i) {
            ui->textEdit->append("id:" + info[i].at(0) + "   卡号:" + info[i].at(1) + "  刷卡教室:"+ info[i].at(3) + "  时间:" + info[i].at(2));
        }
    }
}
