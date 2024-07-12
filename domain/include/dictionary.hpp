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

    const QVector<CategoryInfo *> getCategories() { return m_categories; }

  public slots:
    bool addWord(QString pWord, QString pDefinition);
    bool removeWord(Word *pWord);

    bool createCategory(QString name, QString description);
    bool removeCategory(CategoryInfo *category);

  signals:
    void wordsChanged();
    void categoriesChanged();

  private:
    QVector<Word *> m_words;
    QVector<CategoryInfo *> m_categories;
};
