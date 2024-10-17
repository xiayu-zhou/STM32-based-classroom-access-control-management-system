//
// Created by Kiana on 2024/5/16.
//

#include "MySQL_X.h"

MYSQL_X::MYSQL_X(QObject *parent) : QObject(parent) {
    qDebug() << QSqlDatabase::drivers();
    QSqlDatabase::removeDatabase(QSqlDatabase::database().connectionName());
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("rfid_work");
    db.setUserName("root");
    db.setPassword("123456");
    if(db.open()){
        qDebug() << "yes";
    }
}

int MYSQL_X::insert_from_id(QString id, QString name) {
    db.open();
    update_id();
    QSqlQuery query;
    bool result = query.exec("INSERT INTO rfid (rfid_id, class_num) VALUES ('"+id+"', '"+name+"');");

    if(result){
        qDebug()<<"insert ok";
        return 1;
    }else {
        qDebug() << "insert error";
        return 0;
    }
    db.close();
}
int MYSQL_X::insert_from_qq(QString id, QString name) {
    db.open();
    update_qq();
    QSqlQuery query;
    bool result = query.exec("INSERT INTO user (qq, passwd) VALUES ('"+id+"', '"+name+"');");

    if(result){
        qDebug()<<"insert ok";
        return 1;
    }else {
        qDebug() << "insert error";
        return 0;
    }
    db.close();
}


int MYSQL_X::update_id() {
    QSqlQuery query;
    QString sql = "ALTER TABLE rfid AUTO_INCREMENT = 1;";

    if (!query.exec(sql)) {
        // 如果有错误发生
        qDebug() << "Error executing query:";
        return 0;
    } else {
        qDebug() << "AUTO_INCREMENT reset successfully";
        return 1;
    }
}

int MYSQL_X::update_qq() {
    QSqlQuery query;
    QString sql = "ALTER TABLE user AUTO_INCREMENT = 1;";

    if (!query.exec(sql)) {
        // 如果有错误发生
        qDebug() << "Error executing query:";
        return 0;
    } else {
        qDebug() << "AUTO_INCREMENT reset successfully";
        return 1;
    }
}

int MYSQL_X::is_save_id(QString text) {
    db.open();
    QSqlQuery query;
    query.prepare("SELECT EXISTS (SELECT 1 FROM rfid WHERE rfid_id = :rfidId)");
    query.bindValue(":rfidId", text);
    if (query.exec()) {
        if (query.next()) {
            bool exists = query.value(0).toBool();
            qDebug() << "RFID ID exists:" << exists;
            if(exists)
                return 1;
        }
    }
    return 0;
}

QString MYSQL_X::select_from_rfid_id(QString str) {
    QSqlQuery query;
    QString sql = "SELECT class_num FROM rfid_table WHERE rfid_id = :rfidId";
    query.prepare(sql);
    query.bindValue(":rfidId", str);

    // 执行查询
    if (query.exec()) {
        // 检查是否有结果
        if (query.next()) {
            // 读取结果
            QString name = query.value(0).toString();
            qDebug() << "Found name:" << name;
            return name;
        } else {
            qDebug() << "No record found for rfid_id:" << str;
        }
    }
    return "";
}

bool MYSQL_X::login_from_qq(QString qq, QString passwd) {
    db.open();
    // 查询qq是否存在
    QSqlQuery query(db);
    query.prepare("SELECT passwd FROM user WHERE qq = :qq");
    query.bindValue(":qq", qq);

    if (!query.exec()) {
        // 处理查询失败的情况
        qWarning() << "Query failed:" << query.lastError().text();
        return false;
    }

    // 检查查询结果
    if (!query.next()) {
        // 没有找到对应的qq
        return false;
    }

    // 获取查询到的密码（假设是明文存储，如果是加密存储则需要解密）
    QString storedPasswd = query.value(0).toString();

    // 比对密码
    if (passwd != storedPasswd) {
        // 密码不匹配
        return false;
    }

    // 密码匹配
    return true;
}

int MYSQL_X::insert_class_num(QString class_num) {
    db.open();
    update_qq();
    QSqlQuery query;
    bool result = query.exec("INSERT INTO class (classnum) VALUES ('" + class_num + "');");

    if(result){
        qDebug()<<"insert ok";
        return 1;
    }else {
        qDebug() << "insert error";
        return 0;
    }
    db.close();
}

bool MYSQL_X::existsRfidWithClassNum(const QString rfidId, const QString classNum) {
    QSqlQuery query;
    QString sql = "SELECT COUNT(*) FROM rfid WHERE rfid_id = :rfid_id AND class_num = :class_num";

    // 准备查询并使用绑定参数，以避免 SQL 注入
    query.prepare(sql);
    query.bindValue(":rfid_id", rfidId);
    query.bindValue(":class_num", classNum);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    // 获取查询结果的第一行第一列（即 COUNT(*) 的结果）
    if (query.next()) {
        int count = query.value(0).toInt();
        // 如果 count 大于 0，则表示存在这样的记录
        return count > 0;
    }

    // 如果查询没有返回结果，则认为不存在这样的记录
    return false;
}

bool MYSQL_X::checkClassNumExists(const QString classNum) {
    QSqlQuery query;
    QString sql = "SELECT COUNT(*) FROM Class WHERE Classnum = :classNum";

    query.prepare(sql);
    query.bindValue(":classNum", classNum);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

QStringList MYSQL_X::getClassNumbers() {
    QStringList classNumbers;

     if (!db.open()) {
         return classNumbers;
     }

    QSqlQuery query;
    if (query.exec("SELECT Classnum FROM Class")) {
        while (query.next()) {
            classNumbers.append(query.value(0).toString());
        }
    } else {
        return classNumbers;
        qDebug() << "QStringList MYSQL_X::getClassNumbers() error";
    }

    return classNumbers;
}

QVector<QStringList> MYSQL_X::getRfidClassInfo() {
    QVector<QStringList> info;
    if (!db.open()) {
        return info;
    }

    QSqlQuery query;

    // 执行查询
    query.prepare("SELECT rfid_id, class_num FROM rfid");
    if (query.exec()) {
        // 遍历查询结果
        while (query.next()) {
            QStringList rowData;
            rowData << query.value(0).toString() << query.value(1).toString();
            info.append(rowData);
        }
    } else {
        return info;
        qDebug() << "QVector<QStringList> MYSQL_X::getRfidClassInfo() error";
    }

    return info;
}

bool MYSQL_X::insertIntoInfoTable(const QString &rfidId, const QDateTime &sdate, const QString &classroom) {
    QSqlQuery query;

    // 构建SQL插入语句
    QString sql = "INSERT INTO info (rfid_id, sdate, classroom) VALUES (:rfidId, :sdate, :classroom)";

    // 准备查询
    if (!query.prepare(sql)) {
        // 准备查询失败
        qDebug() << "Failed to prepare SQL statement:" << query.lastError().text();
        return false;
    }

    // 绑定参数
    query.bindValue(":rfidId", rfidId);
    query.bindValue(":sdate", sdate);
    query.bindValue(":classroom", classroom);

    // 执行查询
    if (!query.exec()) {
        // 插入失败
        qDebug() << "Failed to insert into info table:" << query.lastError().text();
        return false;
    }

    // 插入成功
    return true;
}

QVector<QStringList> MYSQL_X::readInfoTableData() {
    QSqlQuery query;
    QVector<QStringList> resultList;

    // 执行SQL查询
    query.exec("SELECT id, rfid_id, sdate, classroom FROM info");

    // 检查查询是否成功
    if (!query.isActive()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return resultList; // 如果没有数据或查询失败，返回一个空列表
    }

    // 遍历结果集
    while (query.next()) {
        QStringList rowData;
        rowData << query.value(0).toString()
                << query.value(1).toString()
                << query.value(2).toString()
                << query.value(3).toString();

        // 将每行数据添加到结果列表中
        resultList.append(rowData);
    }

    return resultList;
}


