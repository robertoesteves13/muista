#pragma once

#include <QObject>
#include <QDateTime>

#include "word_proficiency.hpp"
#include "word.hpp"

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
