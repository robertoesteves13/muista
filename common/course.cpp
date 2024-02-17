#include "common/course.hpp"

Course::Course(QObject* parent, int id, QString name, QString description) : QObject(parent) {
    this->id = id;
    this->name = name;
    this->description = description;
}

Course::~Course() {}
