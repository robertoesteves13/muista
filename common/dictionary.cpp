#include "common/dictionary.hpp"

#include <QDebug>

Category::Category(QObject *parent) : QObject(parent) {}

Category::~Category() {}

Definition::Definition(QObject *parent, QString pMeaning, QString pObservation)
    : QObject(parent) {
    this->meaning = pMeaning;
    this->observation = pObservation;
}

Definition::~Definition() {}

Word::Word(QObject *parent, QString pValue) : QObject(parent) {
    this->value = pValue;
}

Word::~Word() {}

void Word::AddChild(Word &pWord) { this->descendants.push_back(&pWord); }

void Word::AddDefinition(Definition *definition) {
    this->definitions.push_back(definition);
}

void Word::AddCategory(Category *category) {
    this->categories.push_back(category);
}

void Word::SetParent(Word &pWord) { this->antecessor = &pWord; }

// Calculates the hash of value by counting the K most frequent characters
// on the word and also storing the repetition count.
QString Word::GetHash() {
    struct WordHash {
        QChar ch;
        quint16 count;
    };

    const int k = 3;
    WordHash hashes[k] = { 
        WordHash{ .ch = '0', .count = 0 },
        WordHash{ .ch = '0', .count = 0 },
        WordHash{ .ch = '0', .count = 0 }
    };

    for (int i = 0; i < value.length(); i++) {
        WordHash curr{
            .ch = value[i],
            .count = 1,
        };

        for (int j = i + 1; j < value.length(); j++) {
            if (value[i] == value[j]) {
                curr.count += 1;
            }
        }

        for (int i = 0; i < k; i++) {
            if (curr.count > hashes[i].count) {
                WordHash swap = hashes[i];
                hashes[i] = curr;
                curr = swap;
            }
        }
    }

    QString str;
    for (int i = 0; i < k; i++) {
        str += QString(hashes[i].ch) + QString::number(hashes[i].count);
    }

    return str;
}

Dictionary::Dictionary(QObject *parent) : QObject(parent) {}

Dictionary::~Dictionary() {}

void Dictionary::AddWord(QString pWord, QString pDefinition) {}

void Dictionary::RemoveWord(Word *pWord) {}

void Dictionary::RelateWords(std::string_view pAntecessor,
                             std::string_view pChild) {}
