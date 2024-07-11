#pragma once

#include <string_view>

#include <QDateTime>
#include <QObject>
#include <QVector>

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
    static QString hash(QStringView value);

    QStringView getValue() { return m_value; };

  private:
    QString m_value;
    QVector<Definition *> m_definitions;
    QVector<Category *> m_categories;

    Word *m_antecessor;
    QVector<Word *> m_descendants;
};

class WordProficiency {
  public:
    enum Value : uint8_t { New, Learning, Familiar, Master };

    WordProficiency() = default;
    constexpr WordProficiency(Value aFruit) : m_value(aFruit) {}

    constexpr operator Value() const { return m_value; }
    explicit operator bool() const = delete;

    quint32 weight() {
        switch (this->m_value) {
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

    WordProficiency upgrade() {
        switch (this->m_value) {
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
    Value m_value;
};

class WordTrack : public QObject {
    Q_OBJECT;

  public:
    explicit WordTrack(QObject *parent = nullptr, Word *word = nullptr);
    ~WordTrack();

    WordProficiency getProficiency() { return this->m_proficiency; }
    Word *getWord() { return this->m_word; }

  signals:

  public slots:
    void registerExercise(bool isAnswerCorrect);
    void updateProficiency(WordProficiency new_prof);

    // Calculate the score of how important the word is to learn.
    // Lower means more important
    double calculateScore();

  private:
    Word *m_word;
    WordProficiency m_proficiency;
    QDateTime m_started;
    QDateTime m_lastTrained;
    qint32 m_exercisesDone;
};

class WordTracker : public QObject {
    Q_OBJECT

  public:
    WordTracker(QObject *parent = nullptr);
    ~WordTracker();

  public slots:
    void addWord(Word *word);
    WordTrack *getTrack(Word *word);
    void removeTrack(WordTrack *track);
    QVector<WordTrack *> selectBestWords(int amount);

  private:
    QVector<WordTrack *> m_trackedWords;
    qint32 m_wordCap;
};

class Dictionary : public QObject {
    Q_OBJECT
  public:
    Dictionary(QObject *parent = nullptr);
    ~Dictionary();

    void relateWords(std::string_view pAntecessor, std::string_view pChild);
    QVector<Word *> searchWord(QStringView pWord);

    WordTracker *getTracker() { return this->m_tracker; }

  public slots:
    void addWord(QString pWord, QString pDefinition);
    void removeWord(Word *pWord);

  private:
    QVector<Word *> m_words;
    QVector<Category *> m_categories;
    WordTracker *m_tracker;
};
