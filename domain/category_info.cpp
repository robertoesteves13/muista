#include "category.hpp"
#include "qobject.h"

CategoryInfo::CategoryInfo(QObject *parent) : QObject(parent) {}

void CategoryInfo::setName(QString name) {
    this->m_name = name;
    emit dataChanged();
}

void CategoryInfo::setDescription(QString description) {
    this->m_description = description;
    emit dataChanged();
}

bool CategoryInfo::addValue(QString value) {
    if (this->m_possibleValues.contains(value)) {
        return false;
    } else {
        this->m_possibleValues.append(value);
        emit dataChanged();
        return true;
    }
}

bool CategoryInfo::removeValue(QString value) {
    int i = this->m_possibleValues.indexOf(value);
    if (i >= 0) {
        this->m_possibleValues.remove(i);
        emit dataChanged();
        return true;
    } else {
        return false;
    }
}

CategoryInfo::~CategoryInfo() {}
