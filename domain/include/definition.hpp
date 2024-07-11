#pragma once

#include <QObject>

class Definition : public QObject {
    Q_OBJECT
  public:
    Definition(QObject *parent = nullptr, QString pMeaning = nullptr,
               QString pObservation = nullptr);
    ~Definition();

  public:
    QString m_meaning;
    QString m_observation;
};

