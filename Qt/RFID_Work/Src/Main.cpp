//
// Created by Kiana on 2024/5/15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Main.h" resolved

#include "Main.h"
#include "ui_Main.h"

Main::Main(QWidget *parent) :
        QWidget(parent), ui(new Ui::Main) {
    ui->setupUi(this);

    this->setWindowTitle("智慧教室门锁管理系统");

    tcp = new MyTCP();
    mysql = new MYSQL_X();

    Error_count = 0;

    connect(ui->init_rfid,&QPushButton::clicked,this,&Main::on_init_RFID);
    connect(ui->open_lock,&QPushButton::clicked,this,&Main::on_open_lock);
    connect(tcp, SIGNAL(sig_get_rfid_card(QString, QString)),this, SLOT(set_now_rfid_card_txt(QString, QString)));
    connect(tcp, SIGNAL(sig_get_init_rfid_card(QString)),this, SLOT(set_now_init_rfid_card_txt(QString)));
    connect(ui->class_re,&QPushButton::clicked,this,&Main::on_class_num_clicked);
    connect(ui->start_init,&QPushButton::clicked,this,&Main::on_class_start_init_clicked);
    connect(tcp, SIGNAL(sig_init_false_true(bool)),this, SLOT(init_false_true(bool)));

    connect(ui->tabWidget, SIGNAL(currentChanged(int)),this, SLOT(info_class_num_rfid_card(int)));

    connect(ui->pb_info, &QPushButton::clicked,this, &Main::on_InfoInquiry);

    connect(tcp, SIGNAL(get_rfid_card(QString, QString)),this, SLOT(have_rfid_card(QString, QString)));

    ui->init_rfid->setEnabled(false);

    this->setStyleSheet("QWidget { background-color: rgb(180,180,180); }");
    ui->widget->setStyleSheet("QWidget { background-color: rgb(235,235,235); }");
    ui->widget_2->setStyleSheet("QWidget { background-color: rgb(235,235,235); }");
    ui->widget_3->setStyleSheet("QWidget { background-color: rgb(180,180,180); }");
    ui->widget_4->setStyleSheet("QWidget { background-color: rgb(180,180,180); }");
    ui->label_12->setStyleSheet("QLabel {color: rgb(0,0,255);}");
    ui->card_info->setStyleSheet("QTextEdit { background-color: rgb(255,255,255);}");
    ui->card_info->setReadOnly(true);
    ui->class_info->setStyleSheet("QTextEdit { background-color: rgb(255,255,255);}");
    ui->class_info->setReadOnly(true);

    ui->passwd->setStyleSheet("QWidget { background-color: rgb(255,255,255); }");
    ui->start_init->setStyleSheet("QWidget { background-color: rgb(255,255,255); }");
    ui->open_lock->setStyleSheet("QWidget { background-color: rgb(255,255,255); }");
    ui->init_rfid->setStyleSheet("QWidget { background-color: rgb(255,255,255); }");
    ui->class_num->setStyleSheet("QWidget { background-color: rgb(255,255,255); }");
    ui->class_re->setStyleSheet("QWidget { background-color: rgb(255,255,255); }");
    ui->class_num_2->setStyleSheet("QWidget { background-color: rgb(255,255,255); }");
    ui->class_num_3->setStyleSheet("QWidget { background-color: rgb(255,255,255); }");
    ui->f_e->setStyleSheet("QLabel { background-color: rgb(255,0,0);}");

}

Main::~Main() {
    delete ui;
}

void Main::on_init_RFID() {
    QString class_num = ui->class_num_3->text();
    if(class_num != ""){
        if(mysql->checkClassNumExists(class_num)){
            tcp->TCP_SEND("@i" + ui->class_num_2->text() + class_num+"*");
        }else{
            QMessageBox::information(this,"error","The classroom number does not exist");
        }
    }
}

void Main::on_open_lock() {
    QString passwd = ui->passwd->text();
    if(passwd != ""){
        if(mysql->checkClassNumExists(passwd))
        {
            tcp->TCP_SEND("@o" + passwd + "*");
            qDebug() << "open lock";
            QTimer::singleShot(5000, this, [=](){
                qDebug() << "Auto close lock";
                tcp->TCP_SEND("@c" + passwd + "*");
            });
        }
        if(Error_count < 4){
            Error_count++;
        }else{
            tcp->TCP_SEND("@e" + passwd + "*");
            Error_count = 0;
        }
        return;
    }
}


void Main::onTimeout() {
    qDebug() << "Auto close lock";
    tcp->TCP_SEND("@c*");
}

void Main::from_rfid_open(bool flag,QString class_num) {
    if(flag){
        QTimer::singleShot(5000, this, [=](){
            qDebug() << "Auto close lock";
            tcp->TCP_SEND("@c" + class_num + "*");
        });
        tcp->TCP_SEND("@o" + class_num + "*");
    }else{
        if(Error_count < 4){
            Error_count++;

        }else{
            tcp->TCP_SEND("@e" + class_num + "*");
            Error_count = 0;
        }
    }
}

void Main::on_class_num_clicked() {
    QString class_num = ui->class_num->text();
    if(class_num != ""){
        int ret = mysql->insert_class_num(class_num);
        if(ret){
            QMessageBox::information(this,"insert","insert ok!!!");
        }else{
            QMessageBox::information(this,"insert","insert error!!!");
        }
    }
}

void Main::on_class_start_init_clicked() {
    if(start_init_flag){
        start_init_flag = false;
        ui->init_rfid->setEnabled(false);
        ui->start_init->setText("启动录卡");
        ui->start_init->setStyleSheet("QWidget { color: rgb(0,0,0); background-color: rgb(255,255,255); }");
        QString class_num = ui->class_num_2->text();
        tcp->TCP_SEND("@g" + class_num + "*");
        ui->f_e->setStyleSheet("QLabel { background-color: rgb(255,0,0);}");
        ui->id_card_2->setText("");
        ui->class_num_2->setText("");
        ui->class_num_3->setText("");
        ui->class_num_2->setEnabled(true);
        qDebug() << "start_init_flag = false";
    }else{
        QString class_num = ui->class_num_2->text();
        if(class_num != ""){
            if(mysql->checkClassNumExists(class_num)){
                ui->class_num_2->setEnabled(false);
                start_init_flag = true;
                ui->start_init->setText("正在录卡");
                ui->start_init->setStyleSheet("QWidget { color: rgb(255,255,255); background-color: rgb(255,0,0); }");
                tcp->rfid_card_clean();
                tcp->TCP_SEND("@l" + class_num + "*");
                ui->init_rfid->setEnabled(true);
                qDebug() << "start_init_flag = true";
            }else{
                QMessageBox::information(this,"error","The classroom number does not exist");
            }
        }
    }
}

void Main::set_now_init_rfid_card_txt(QString txt) {
    ui->id_card_2->setText(txt);
}

void Main::init_false_true(bool flag) {
    if(flag){
        qDebug() << "init RFID finish";
        mysql->insert_from_id(tcp->getRfidInitId(),ui->class_num_3->text());
        ui->f_e->setStyleSheet("QLabel { background-color: rgb(0,255,0);}");
    }else{
        ui->f_e->setStyleSheet("QLabel { background-color: rgb(255,0,0);}");
    }
}

void Main::set_now_rfid_card_txt(QString id, QString class_num) {
    bool flag = mysql->existsRfidWithClassNum(id,class_num);
    if(flag){
        ui->id_card->setText(id);
        ui->id_card_ident->setText(class_num);
        from_rfid_open(true,class_num);
    }else{
        from_rfid_open(false,class_num);
        qDebug() << "from_rfid_open(false);";
    }
}

void Main::info_class_num_rfid_card(int index) {
    qDebug() << "index = " << index;
    if(index == 0){
        QStringList info;
        info = mysql->getClassNumbers();
        ui->class_info->setText("");
        for (int i = 0; i < info.size(); ++i) {
            ui->class_info->append("classroom number: " + info[i]);
        }
    }else if(index == 1){
        QVector<QStringList> info;
        info = mysql->getRfidClassInfo();
        ui->card_info->setText("");
        for (int i = 0; i < info.size(); ++i) {
            ui->card_info->append("ID:" + info[i][0] + "   classroom:" + info[i][1]);
        }
    }
}

void Main::on_InfoInquiry() {
    qDebug() << "on_InfoInquiry";
    info.setMysqlX(mysql);
    info.show();
}

void Main::have_rfid_card(QString id, QString classroom) {
    QDateTime currentTime = QDateTime::currentDateTime();
    mysql->insertIntoInfoTable(id,currentTime,classroom);
}

QString Main::getNowTime() {
    // 获取当前时间
    QDateTime currentTime = QDateTime::currentDateTime();
    // 设置时间格式，例如 "yyyy-MM-dd HH:mm:ss"
    QString format = "yyyy-MM-dd HH:mm:ss";
    // 将时间转换为指定格式的字符串
    QString formattedTime = currentTime.toString(format);
    // 返回格式化后的时间字符串
    return formattedTime;
}

