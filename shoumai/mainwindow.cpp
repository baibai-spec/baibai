#include "mainwindow.h"
#include "phone.h"
#include "sale.h"
#include "user.h"
#include "account.h"
// Qt 5.3.1 所需头文件
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QInputDialog>
#include <QDateTime>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      phoneInventory(),
      salesRecords(),
      accountModule(),
      currentUser()
{
    // 初始化手机库存
    Phone p1("iPhone 15", "Apple", 6999.0, 50);
    Phone p2("Mate 60", "Huawei", 4999.0, 30);
    phoneInventory.insert(p1.getModel(), p1);
    phoneInventory.insert(p2.getModel(), p2);

    // 创建表格控件
    QTableWidget *table = new QTableWidget(this);
    table->setColumnCount(4);
    QStringList headers;
    headers << "Model" << "Brand" << "Price" << "Stock";
    table->setHorizontalHeaderLabels(headers);

    int row = 0;
    table->setRowCount(phoneInventory.size());
    QMap<QString, Phone>::const_iterator it;
    for (it = phoneInventory.constBegin(); it != phoneInventory.constEnd(); ++it) {
        const Phone &phone = it.value();
        table->setItem(row, 0, new QTableWidgetItem(phone.getModel()));
        table->setItem(row, 1, new QTableWidgetItem(phone.getBrand()));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(phone.getPrice())));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(phone.getStock())));
        row++;
    }
    setCentralWidget(table);

    // 构建菜单栏
    QMenuBar *mainMenuBar = menuBar();

    // 账户菜单
    QMenu *accountMenu = mainMenuBar->addMenu("账户");
    accountMenu->addAction("登录", this, SLOT(on_actionLogin_triggered()));
    accountMenu->addAction("注册", this, SLOT(on_actionRegister_triggered()));
    accountMenu->addAction("修改账户", this, SLOT(on_actionModifyAccount_triggered()));

    // 销售菜单
    QMenu *saleMenu = mainMenuBar->addMenu("销售");
    saleMenu->addAction("卖手机", this, SLOT(on_actionSellPhone_triggered()));
    saleMenu->addAction("查看销售记录", this, SLOT(on_actionShowSales_triggered()));

    // 库存菜单
    QMenu *stockMenu = mainMenuBar->addMenu("库存");
    stockMenu->addAction("查看库存", this, SLOT(on_actionShowPhones_triggered()));
    stockMenu->addAction("添加手机", this, SLOT(on_actionAddPhone_triggered())); // 新增菜单项
}

MainWindow::~MainWindow() {}

// 登录
bool MainWindow::login(const QString &username, const QString &password) {
    if (accountModule.loginUser(username, password)) {
        currentUser = User(username, password);
        QMessageBox::information(this, "登录", "登录成功！");
        return true;
    } else {
        QMessageBox::warning(this, "登录", "用户名或密码错误！");
        return false;
    }
}

// 注册
void MainWindow::registerUser(const QString &username, const QString &password) {
    if (accountModule.registerUser(username, password)) {
        QMessageBox::information(this, "注册", "注册成功！");
    } else {
        QMessageBox::warning(this, "注册", "注册失败，用户名已存在！");
    }
}

// 显示所有手机库存
void MainWindow::displayPhones() {
    QString info;
    QMap<QString, Phone>::const_iterator it = phoneInventory.constBegin();
    while (it != phoneInventory.constEnd()) {
        const Phone &phone = it.value();
        info += QString("Model: %1, Brand: %2, Price: %3, Stock: %4\n")
                .arg(phone.getModel())
                .arg(phone.getBrand())
                .arg(phone.getPrice())
                .arg(phone.getStock());
        ++it;
    }
    QMessageBox::information(this, "手机库存", info);
}

// 显示销售记录
void MainWindow::displaySales() {
    QString info;
    for (int i = 0; i < salesRecords.size(); ++i) {
        const SalesRecord &record = salesRecords.at(i);
        info += QString("Model: %1, Quantity: %2, Total Price: %3, Time: %4\n")
                .arg(record.getPhoneModel())
                .arg(record.getQuantity())
                .arg(record.getTotalPrice())
                .arg(record.getTimestamp().toString("yyyy-MM-dd hh:mm:ss"));
    }
    QMessageBox::information(this, "销售记录", info);
}

// 卖手机
bool MainWindow::sellPhone(const QString &model, int quantity) {
    if (phoneInventory.contains(model)) {
        Phone &phone = phoneInventory[model];
        if (phone.getStock() >= quantity) {
            phone.setStock(phone.getStock() - quantity);
            double totalPrice = phone.getPrice() * quantity;
            salesRecords.append(SalesRecord(model, quantity, totalPrice, QDateTime::currentDateTime()));
            return true;
        }
    }
    QMessageBox::warning(this, "销售失败", "库存不足或型号不存在！");
    return false;
}

// 修改账户
void MainWindow::modifyAccount(const QString &newUsername, const QString &newPassword) {
    if (accountModule.modifyPassword(currentUser.getUsername(),
                                     currentUser.getPassword(),
                                     newPassword)) {
        currentUser.setUsername(newUsername);
        currentUser.setPassword(newPassword);
        QMessageBox::information(this, "修改账户", "账户修改成功！");
    } else {
        QMessageBox::warning(this, "修改账户", "账户修改失败！");
    }
}

// 登录槽
void MainWindow::on_actionLogin_triggered() {
    QString username = QInputDialog::getText(this, "登录", "用户名:");
    QString password = QInputDialog::getText(this, "登录", "密码:", QLineEdit::Password);
    login(username, password);
}

// 注册槽
void MainWindow::on_actionRegister_triggered() {
    QString username = QInputDialog::getText(this, "注册", "用户名:");
    QString password = QInputDialog::getText(this, "注册", "密码:", QLineEdit::Password);
    registerUser(username, password);
}

// 修改账户槽
void MainWindow::on_actionModifyAccount_triggered() {
    QString newUsername = QInputDialog::getText(this, "修改账户", "新用户名:");
    QString newPassword = QInputDialog::getText(this, "修改账户", "新密码:", QLineEdit::Password);
    modifyAccount(newUsername, newPassword);
}

// 卖手机槽
void MainWindow::on_actionSellPhone_triggered() {
    QString model = QInputDialog::getText(this, "卖手机", "手机型号:");
    bool ok;
    int quantity = QInputDialog::getInt(this, "卖手机", "数量:", 1, 1, 1000, 1, &ok);
    if (ok) sellPhone(model, quantity);
}

// 查看销售记录槽
void MainWindow::on_actionShowSales_triggered() {
    displaySales();
}

// 查看库存槽
void MainWindow::on_actionShowPhones_triggered() {
    displayPhones();
}

// 添加手机槽
void MainWindow::on_actionAddPhone_triggered() {
    QString model = QInputDialog::getText(this, "添加手机", "手机型号:");
    QString brand = QInputDialog::getText(this, "添加手机", "手机品牌:");
    bool priceOk;
    double price = QInputDialog::getDouble(this, "添加手机", "手机价格:", 0, 0, 100000, 2, &priceOk);
    bool stockOk;
    int stock = QInputDialog::getInt(this, "添加手机", "库存数量:", 0, 0, 10000, 1, &stockOk);

    if (model.isEmpty() || brand.isEmpty() || !priceOk || !stockOk) {
        QMessageBox::warning(this, "输入错误", "请完整填写手机信息并确保价格、库存为有效数字！");
        return;
    }

    Phone newPhone(model, brand, price, stock);
    phoneInventory.insert(model, newPhone);

    updateTableWithNewPhone(newPhone);

    QMessageBox::information(this, "添加成功", "手机信息已成功添加到库存！");
}

// 更新表格显示
void MainWindow::updateTableWithNewPhone(const Phone &newPhone) {
    QTableWidget *table = qobject_cast<QTableWidget*>(centralWidget());
    if (table) {
        int newRow = table->rowCount();
        table->insertRow(newRow);

        table->setItem(newRow, 0, new QTableWidgetItem(newPhone.getModel()));
        table->setItem(newRow, 1, new QTableWidgetItem(newPhone.getBrand()));
        table->setItem(newRow, 2, new QTableWidgetItem(QString::number(newPhone.getPrice())));
        table->setItem(newRow, 3, new QTableWidgetItem(QString::number(newPhone.getStock())));
    }
}
