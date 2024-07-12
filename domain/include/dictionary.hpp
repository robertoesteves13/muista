#pragma once

#include <string_view>

#include <QObject>
#include <QVector>

#include "word.hpp"

class Dictionary : public QObject {
    Q_OBJECT
  public:
    Dictionary(QObject *parent = nullptr);
    ~Dictionary();

    void relateWords(std::string_view pAntecessor, std::string_view pChild);
    QVector<Word *> searchWord(QStringView pWord);

  public slots:
    void addWord(QString pWord, QString pDefinition);
    void removeWord(Word *pWord);

  private:
    QVector<Word *> m_words;
    QVector<Category *> m_categories;
};
