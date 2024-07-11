#include "dictionary.hpp"

#include <QDebug>

Dictionary::Dictionary(QObject *parent) : QObject(parent) {
    this->m_tracker = new WordTracker(this);
}

Dictionary::~Dictionary() {}

void Dictionary::addWord(QString pWord, QString pDefinition) {
    Word *word = new Word(this, pWord);
    word->addDefinition(pDefinition);

    this->m_words.push_back(word);
}

void Dictionary::removeWord(Word *pWord) { qFatal() << "not implemented"; }

void Dictionary::relateWords(std::string_view pAntecessor,
                             std::string_view pChild) {
    qFatal() << "not implemented";
}

QVector<Word *> Dictionary::searchWord(QStringView search) {
    QString searchHash = Word::hash(search);
    QVector<Word *> result;

    for (Word *word : this->m_words) {
        if (word->compareHash(searchHash) < 7)
            result.push_back(word);
    }

    std::sort(result.begin(), result.end(),
              [&searchHash](Word *w1, Word *w2) -> bool {
                  return w1->compareHash(searchHash) <
                         w2->compareHash(searchHash);
              });

    return result;
}
