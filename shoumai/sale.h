#ifndef SALESRECORD_H
#define SALESRECORD_H

#include <QString>
#include <QDateTime>

class SalesRecord {
public:
    SalesRecord();
    SalesRecord(const QString &phoneModel, int quantity, double totalPrice, const QDateTime &timestamp);

    QString getPhoneModel() const;
    void setPhoneModel(const QString &phoneModel);

    int getQuantity() const;
    void setQuantity(int quantity);

    double getTotalPrice() const;
    void setTotalPrice(double totalPrice);

    QDateTime getTimestamp() const;
    void setTimestamp(const QDateTime &timestamp);

private:
    QString phoneModel;
    int quantity;
    double totalPrice;
    QDateTime timestamp;
};

#endif // SALESRECORD_H
