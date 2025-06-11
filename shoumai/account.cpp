// account.cpp
#include "account.h"

Account::Account(QObject *parent) : QObject(parent) {}

bool Account::registerUser(const QString &username, const QString &password) {
    if (userDB.contains(username))
        return false; // 用户名已存在
    userDB.insert(username, password);
    return true;
}

bool Account::loginUser(const QString &username, const QString &password) {
    return userDB.value(username) == password;
}

bool Account::modifyPassword(const QString &username, const QString &oldPwd, const QString &newPwd) {
    if (userDB.value(username) != oldPwd)
        return false; // 旧密码错误
    userDB[username] = newPwd;
    return true;
}
