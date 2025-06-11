#include "Phone.h"

Phone::Phone() {}

Phone::Phone(const QString &model, const QString &brand, double price, int stock)
    : model(model), brand(brand), price(price), stock(stock) {}

QString Phone::getModel() const {
    return model;
}

void Phone::setModel(const QString &model) {
    this->model = model;
}

QString Phone::getBrand() const {
    return brand;
}

void Phone::setBrand(const QString &brand) {
    this->brand = brand;
}

double Phone::getPrice() const {
    return price;
}

void Phone::setPrice(double price) {
    this->price = price;
}

int Phone::getStock() const {
    return stock;
}

void Phone::setStock(int stock) {
    this->stock = stock;
}
