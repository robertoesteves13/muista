#pragma once

#include "common/dictionary.hpp"
#include <QObject>

class WordTest : public QObject {
    Q_OBJECT

  private slots:
    void HashWord_data();
    void HashWord();
};

class DictionaryTest : public QObject {
    Q_OBJECT
  private slots:
    void SearchWord();
};
