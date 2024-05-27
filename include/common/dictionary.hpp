#pragma once

#include <string_view>

#include <QObject>
#include <QVector>

class Category : public QObject {
    Q_OBJECT
  public:
    Category(QObject *parent = nullptr);
    ~Category();

  public:
    QString title;
    QString description;
    QVector<QString> possible_values;
};

class Definition : public QObject {
    Q_OBJECT
  public:
    Definition(QObject *parent = nullptr, QString pMeaning = nullptr,
               QString pObservation = nullptr);
    ~Definition();

  public:
    QString meaning;
    QString observation;
};

class Word : public QObject {
    Q_OBJECT
  public:
    Word(QObject *parent = nullptr, QString pValue = nullptr);
    ~Word();

    void AddChild(Word &pWord);
    void AddDefinition(QString pMeaning);
    void AddCategory(Category *category);
    void SetParent(Word &pWord);

    QString GetHash();
    static QString Hash(QStringView value);

    QStringView Value() { return value; };

  private:
    QString value;
    QVector<Definition *> definitions;
    QVector<Category *> categories;

    Word *antecessor;
    QVector<Word *> descendants;
};

class Dictionary : public QObject {
    Q_OBJECT
  public:
    Dictionary(QObject *parent = nullptr);
    ~Dictionary();

    void RelateWords(std::string_view pAntecessor, std::string_view pChild);
    QVector<Word *> SearchWord(QStringView pWord);

  public slots:
    void AddWord(QString pWord, QString pDefinition);
    void RemoveWord(Word *pWord);

  private:
    QVector<Word*> words;
    QVector<Category*> categories;
};
