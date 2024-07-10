#include "common/dictionary.hpp"
#include "qdatetime.h"

WordTracker::WordTracker(QObject *parent) : QObject(parent) {
    this->wordCap = 20;
}

QVector<WordTrack *> WordTracker::SelectBestWords(int amount) {
    QVector<WordTrack *> bestWords = this->trackedWords.toVector();

    std::sort(bestWords.begin(), bestWords.end(),
              [&](WordTrack *w1, WordTrack *w2) -> bool {
                  return w1->CalculateScore() < w2->CalculateScore();
              });

    bestWords = bestWords.sliced(0, amount);
    return bestWords;
}

void WordTracker::AddWord(Word *word) {
    WordTrack *tracker = new WordTrack(this, word);
    this->trackedWords.append(tracker);
}

void WordTracker::RemoveTrack(WordTrack *track) {
    int i = this->trackedWords.indexOf(track);

    if (i == -1) return;
    this->trackedWords.remove(i);
}

WordTrack *WordTracker::GetTrack(Word *word) {
    for (int i = 0; i < this->trackedWords.length(); ++i) {
        if (this->trackedWords[i]->GetWord() == word) {
            return this->trackedWords[i];
        }
    }

    return nullptr;
}

WordTracker::~WordTracker() {}

WordTrack::WordTrack(QObject *parent, Word *word) : QObject(parent) {
    this->word = word;
    this->proficiency = WordProficiency::New;
    this->started = QDateTime::currentDateTime();
    this->lastTrained = QDateTime::currentDateTime();
    this->exercisesDone = 0;
}

WordTrack::~WordTrack() {}

void WordTrack::RegisterExercise(bool isAnswerCorrect) {
    this->exercisesDone += 1;

    if (isAnswerCorrect) {
        int upgradeRequirement = this->proficiency.Weight() * 5;
        if (this->exercisesDone >= upgradeRequirement) {
            this->proficiency = this->proficiency.Upgrade();
        }
    }

    // TODO(roberto): Program demotion
}

void WordTrack::UpdateProficiency(WordProficiency new_prof) {
    this->proficiency = new_prof;
}

double WordTrack::CalculateScore() {
    quint8 weight = this->proficiency.Weight();
    QDateTime now = QDateTime::currentDateTime();
    quint32 daysPassed = this->lastTrained.daysTo(now);

    if (daysPassed == 0) {
        return 0;
    }
    return weight * (1.0 / daysPassed);
};
