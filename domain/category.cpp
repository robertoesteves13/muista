#include "category.hpp"
#include "qobject.h"

Category::Category(QObject *parent, CategoryInfo* info) : QObject(parent) {
    this->m_info = info;
}

bool Category::setValue(QString value) {
    Q_ASSERT(this->m_info != nullptr);

    for (QString possibleValue : this->m_info->getPossibleValues()) {
        if (value == possibleValue) {
            this->m_value = value;
            emit valueChanged();
            return true;
        }
    }

    return false;
}

Category::~Category() {}
