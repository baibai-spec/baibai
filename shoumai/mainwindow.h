#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMap>
#include <QList>
#include "account.h"
#include "User.h"
#include "Phone.h"
#include "sale.h"
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLogin_triggered();
    void on_actionRegister_triggered();
    void on_actionModifyAccount_triggered();
    void on_actionSellPhone_triggered();
    void on_actionShowSales_triggered();
    void on_actionShowPhones_triggered();
    void on_actionAddPhone_triggered();
private:
    QMap<QString, Phone> phoneInventory;
    QVector<SalesRecord> salesRecords;
    Account accountModule;
    User currentUser;

    bool login(const QString &username, const QString &password);
    void registerUser(const QString &username, const QString &password);
    void displayPhones();
    void displaySales();
    bool sellPhone(const QString &model, int quantity);
    void modifyAccount(const QString &newUsername, const QString &newPassword);
    void updateTableWithNewPhone(const Phone &newPhone);
};

#endif // MAINWINDOW_H
