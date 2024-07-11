#pragma once

#include <QObject>

class Category : public QObject {
    Q_OBJECT
  public:
    Category(QObject *parent = nullptr);
    ~Category();

  public:
    QString m_title;
    QString m_description;
    QVector<QString> m_possibleValues;
};

