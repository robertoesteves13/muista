#include "dictionary.hpp"

#include <QDebug>

#define K_VALUE 3
#define K_LIMIT 10

Category::Category(QObject *parent) : QObject(parent) {}

Category::~Category() {}

Definition::Definition(QObject *parent, QString pMeaning, QString pObservation)
    : QObject(parent) {
    this->m_meaning = pMeaning;
    this->m_observation = pObservation;
}

Definition::~Definition() {}

Word::Word(QObject *parent, QString pValue) : QObject(parent) {
    this->m_value = pValue;
}

Word::~Word() {}

void Word::addChild(Word &pWord) { this->m_descendants.push_back(&pWord); }

void Word::addDefinition(QString pMeaning) {
    Definition *definition = new Definition(this, pMeaning);
    this->m_definitions.push_back(definition);
}

void Word::addCategory(Category *category) {
    this->m_categories.push_back(category);
}

void Word::setWordParent(Word &pWord) { this->m_antecessor = &pWord; }

QString Word::getHash() { return Word::hash(this->m_value); }

// Calculates the hash of value by counting the K most frequent characters
// on the word and also storing the repetition count.
QString Word::hash(QStringView value) {
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

QVector<Word *> Dictionary::searchWord(QStringView search) {
    QString searchHash = Word::hash(search);
    QVector<Word *> result;

    for (Word *word : this->m_words) {
        if (dst_string(searchHash, word->getHash()) < 7)
            result.push_back(word);
    }

    std::sort(result.begin(), result.end(),
              [&searchHash](Word *w1, Word *w2) -> bool {
                  return dst_string(searchHash, w1->getHash()) <
                         dst_string(searchHash, w2->getHash());
              });

    return result;
}
