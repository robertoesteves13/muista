#pragma once

#include <QObject>

class WordTest : public QObject {
    Q_OBJECT
  public:
    WordTest(QObject *parent = nullptr);
    ~WordTest();

  private slots:
    void HashWord_data();
    void HashWord();
};
