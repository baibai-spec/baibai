#include "sale.h"

SalesRecord::SalesRecord() {}

SalesRecord::SalesRecord(const QString &phoneModel, int quantity, double totalPrice, const QDateTime &timestamp)
    : phoneModel(phoneModel), quantity(quantity), totalPrice(totalPrice), timestamp(timestamp) {}

QString SalesRecord::getPhoneModel() const {
    return phoneModel;
}

void SalesRecord::setPhoneModel(const QString &phoneModel) {
    this->phoneModel = phoneModel;
}

int SalesRecord::getQuantity() const {
    return quantity;
}

void SalesRecord::setQuantity(int quantity) {
    this->quantity = quantity;
}

double SalesRecord::getTotalPrice() const {
    return totalPrice;
}

void SalesRecord::setTotalPrice(double totalPrice) {
    this->totalPrice = totalPrice;
}

QDateTime SalesRecord::getTimestamp() const {
    return timestamp;
}

void SalesRecord::setTimestamp(const QDateTime &timestamp) {
    this->timestamp = timestamp;
}
