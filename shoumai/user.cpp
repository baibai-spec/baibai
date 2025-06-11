#include "User.h"

User::User() {}

User::User(const QString &username, const QString &password)
    : username(username), password(password) {}

QString User::getUsername() const {
    return username;
}

void User::setUsername(const QString &username) {
    this->username = username;
}

QString User::getPassword() const {
    return password;
}

void User::setPassword(const QString &password) {
    this->password = password;
}
