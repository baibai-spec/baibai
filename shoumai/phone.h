#ifndef PHONE_H
#define PHONE_H

#include <QString>

class Phone {
public:
    Phone();
    Phone(const QString &model, const QString &brand, double price, int stock);

    QString getModel() const;
    void setModel(const QString &model);

    QString getBrand() const;
    void setBrand(const QString &brand);

    double getPrice() const;
    void setPrice(double price);

    int getStock() const;
    void setStock(int stock);

private:
    QString model;
    QString brand;
    double price;
    int stock;
};

struct PhoneInfo {
    QString model;
    QString brand;
    double price;
    int stock;

    // 如果使用了 getModel() 等方法，需要在这里声明
    QString getModel() const { return model; }
    QString getBrand() const { return brand; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }
};

#endif // PHONE_H
