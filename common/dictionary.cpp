#include "common/dictionary.hpp"

#include <QDebug>

#define K_VALUE 3
#define K_LIMIT 10

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

void Word::AddDefinition(QString pMeaning) {
    Definition *definition = new Definition(this, pMeaning);
    this->definitions.push_back(definition);
}

void Word::AddCategory(Category *category) {
    this->categories.push_back(category);
}

void Word::SetParent(Word &pWord) { this->antecessor = &pWord; }

QString Word::GetHash() { return Word::Hash(this->value); }

// Calculates the hash of value by counting the K most frequent characters
// on the word and also storing the repetition count.
QString Word::Hash(QStringView value) {
    struct WordHash {
        QChar ch;
        quint16 count;
    };

    WordHash hashes[K_VALUE] = {WordHash{.ch = '0', .count = 0},
                                WordHash{.ch = '0', .count = 0},
                                WordHash{.ch = '0', .count = 0}};

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

        for (int i = 0; i < K_VALUE && hashes[i].ch != curr.ch; i++) {
            if (curr.count > hashes[i].count) {
                WordHash swap = hashes[i];
                hashes[i] = curr;
                curr = swap;
            }
        }
    }

    QString str;
    for (int i = 0; i < K_VALUE; i++) {
        str += QString(hashes[i].ch) + QString::number(hashes[i].count);
    }

    return str;
}

Dictionary::Dictionary(QObject *parent) : QObject(parent) {}

Dictionary::~Dictionary() {}

void Dictionary::AddWord(QString pWord, QString pDefinition) {
    Word *word = new Word(this, pWord);
    word->AddDefinition(pDefinition);

    this->words.push_back(word);
}

void Dictionary::RemoveWord(Word *pWord) { qFatal() << "not implemented"; }

void Dictionary::RelateWords(std::string_view pAntecessor,
                             std::string_view pChild) {
    qFatal() << "not implemented";
}

int dst_string(QStringView hash1, QStringView hash2) {
    Q_ASSERT(hash1.length() == hash2.length());

    int similarity = 0;
    for (int i = 0; i < K_VALUE; i += 2) {
        for (int j = 0; j < K_VALUE; j += 2) {
            if (hash1[i] == hash2[j])
                similarity +=
                    hash1[i + 1].digitValue() + hash2[j + 1].digitValue();
        }
    }

    return K_LIMIT - similarity;
}

QVector<Word *> Dictionary::SearchWord(QStringView search) {
    QString searchHash = Word::Hash(search);
    QVector<Word *> result;

    for (Word *word : this->words) {
        if (dst_string(searchHash, word->GetHash()) < 7)
            result.push_back(word);
    }

    std::sort(result.begin(), result.end(),
              [&searchHash](Word *w1, Word *w2) -> bool {
                  return dst_string(searchHash, w1->GetHash()) <
                         dst_string(searchHash, w2->GetHash());
              });

    return result;
}
