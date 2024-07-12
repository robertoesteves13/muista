#include "lesson.hpp"

LessonInfo::LessonInfo(QObject *parent) : QObject(parent) {}

void LessonInfo::setName(QString name) {
    this->m_name = name;
    emit dataChanged();
}
