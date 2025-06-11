#ifndef USER_H
#define USER_H

#include <QString>

class User {
public:
    User();
    User(const QString &username, const QString &password);

    QString getUsername() const;
    void setUsername(const QString &username);

    QString getPassword() const;
    void setPassword(const QString &password);

private:
    QString username;
    QString password;
};

#endif // USER_H
