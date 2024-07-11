#pragma once

#include <QObject>

#include "category.hpp"
#include "definition.hpp"

class Word : public QObject {
    Q_OBJECT
  public:
    Word(QObject *parent = nullptr, QString pValue = nullptr);
    ~Word();

    void addChild(Word &pWord);
    void addDefinition(QString pMeaning);
    void addCategory(Category *category);
    void setWordParent(Word &pWord);

    QString getHash();
    int compareHash(Word* word);
    int compareHash(QStringView word);
    static QString hash(QStringView value);

    QStringView getValue() { return m_value; };

  private:
    QString m_value;
    QVector<Definition *> m_definitions;
    QVector<Category *> m_categories;

    Word *m_antecessor;
    QVector<Word *> m_descendants;
};
