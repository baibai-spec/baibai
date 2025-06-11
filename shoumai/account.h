// account.h
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QString>
#include <QMap>

class Account : public QObject {
    Q_OBJECT
public:
    explicit Account(QObject *parent = 0);
    bool registerUser(const QString &username, const QString &password);
    bool loginUser(const QString &username, const QString &password);
    bool modifyPassword(const QString &username, const QString &oldPwd, const QString &newPwd);

private:
    QMap<QString, QString> userDB; // 存储用户名和密码
};

#endif // ACCOUNT_H
