#pragma once

#include <QObject>

class Course : public QObject {
  Q_OBJECT
public:
  Course(QObject* parent = nullptr, int id = 0, QString name = "???", QString description = "???");
  ~Course();

public:
    int id;
    QString name, description;
};
