#pragma once

#include <QObject>

#include "word.hpp"
#include "word_track.hpp"

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

