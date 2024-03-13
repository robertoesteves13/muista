#pragma once

#include <QObject>

class CourseReader : public QObject {
  Q_OBJECT
public:
  CourseReader(QObject* parent = nullptr, int id = 0, QString name = "???", QString description = "???");
  ~CourseReader();

public:
    int id;
    QString name, description;
};
