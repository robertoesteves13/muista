#include "dictionary.hpp"
#include "qdatetime.h"

WordTracker::WordTracker(QObject *parent) : QObject(parent) {
    this->m_wordCap = 20;
}

QVector<WordTrack *> WordTracker::selectBestWords(int amount) {
    QVector<WordTrack *> bestWords = this->m_trackedWords.toVector();

    std::sort(bestWords.begin(), bestWords.end(),
              [&](WordTrack *w1, WordTrack *w2) -> bool {
                  return w1->calculateScore() < w2->calculateScore();
              });

    bestWords = bestWords.sliced(0, amount);
    return bestWords;
}

void WordTracker::addWord(Word *word) {
    WordTrack *tracker = new WordTrack(this, word);
    this->m_trackedWords.append(tracker);
}

void WordTracker::removeTrack(WordTrack *track) {
    int i = this->m_trackedWords.indexOf(track);

    if (i == -1) return;
    this->m_trackedWords.remove(i);
}

WordTrack *WordTracker::getTrack(Word *word) {
    for (int i = 0; i < this->m_trackedWords.length(); ++i) {
        if (this->m_trackedWords[i]->getWord() == word) {
            return this->m_trackedWords[i];
        }
    }

    return nullptr;
}

WordTracker::~WordTracker() {}

WordTrack::WordTrack(QObject *parent, Word *word) : QObject(parent) {
    this->m_word = word;
    this->m_proficiency = WordProficiency::New;
    this->m_started = QDateTime::currentDateTime();
    this->m_lastTrained = QDateTime::currentDateTime();
    this->m_exercisesDone = 0;
}

WordTrack::~WordTrack() {}

void WordTrack::registerExercise(bool isAnswerCorrect) {
    this->m_exercisesDone += 1;

    if (isAnswerCorrect) {
        int upgradeRequirement = this->m_proficiency.weight() * 5;
        if (this->m_exercisesDone >= upgradeRequirement) {
            this->m_proficiency = this->m_proficiency.upgrade();
        }
    }

    // TODO(roberto): Program demotion
}

void WordTrack::updateProficiency(WordProficiency new_prof) {
    this->m_proficiency = new_prof;
}

double WordTrack::calculateScore() {
    quint8 weight = this->m_proficiency.weight();
    QDateTime now = QDateTime::currentDateTime();
    quint32 daysPassed = this->m_lastTrained.daysTo(now);

    if (daysPassed == 0) {
        return 0;
    }
    return weight * (1.0 / daysPassed);
};
