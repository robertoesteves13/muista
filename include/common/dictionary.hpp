#pragma once

#include "qdatetime.h"
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

class WordProficiency {
  public:
    enum Value : uint8_t { New, Learning, Familiar, Master };

    WordProficiency() = default;
    constexpr WordProficiency(Value aFruit) : value(aFruit) {}

    constexpr operator Value() const { return value; }
    explicit operator bool() const = delete;

    quint32 Weight() {
        switch (this->value) {
        case WordProficiency::New:
            return 0;
        case WordProficiency::Learning:
            return 1;
        case WordProficiency::Familiar:
            return 3;
        case WordProficiency::Master:
            return 5;
        }
    }

    WordProficiency Upgrade() {
        switch (this->value) {
        case WordProficiency::New:
            return WordProficiency::Learning;
        case WordProficiency::Learning:
            return WordProficiency::Familiar;
        case WordProficiency::Familiar:
            return WordProficiency::Master;
        case WordProficiency::Master:
            return WordProficiency::Master;
        }
    }

  private:
    Value value;
};

class WordTrack : public QObject {
    Q_OBJECT;

  public:
    explicit WordTrack(QObject *parent = nullptr, Word *word = nullptr);
    ~WordTrack();

    WordProficiency Proficiency() { return this->proficiency; }
    Word* GetWord() { return this->word; }

  signals:

  public slots:
    void RegisterExercise(bool isAnswerCorrect);
    void UpdateProficiency(WordProficiency new_prof);

    // Calculate the score of how important the word is to learn between 0-1.
    // Lower means more important
    double CalculateScore();

  private:
    Word *word;
    WordProficiency proficiency;
    QDateTime started;
    QDateTime lastTrained;
    qint32 exercisesDone;
};

class WordTracker : public QObject {
    Q_OBJECT

  public:
    WordTracker(QObject *parent = nullptr);
    ~WordTracker();

  public slots:
    void AddWord(Word *word);
    WordTrack *GetTrack(Word *word);
    QVector<WordTrack *> SelectBestWords(int amount);

  private:
    QVector<WordTrack *> trackedWords;
    qint32 wordCap;
};

class Dictionary : public QObject {
    Q_OBJECT
  public:
    Dictionary(QObject *parent = nullptr);
    ~Dictionary();

    void RelateWords(std::string_view pAntecessor, std::string_view pChild);
    QVector<Word *> SearchWord(QStringView pWord);

    WordTracker* Tracker() { return this->tracker; }

  public slots:
    void AddWord(QString pWord, QString pDefinition);
    void RemoveWord(Word *pWord);

  private:
    QVector<Word *> words;
    QVector<Category *> categories;
    WordTracker *tracker;
};
