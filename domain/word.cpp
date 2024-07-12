#include "word.hpp"

#define K_VALUE 3
#define K_LIMIT 10

Word::Word(QObject *parent, QString pValue) : QObject(parent) {
    this->m_value = pValue;
}

Word::~Word() {}

void Word::addChild(Word &pWord) { this->m_descendants.push_back(&pWord); }

void Word::addDefinition(QString pMeaning) {
    Definition *definition = new Definition(this, pMeaning);
    this->m_definitions.push_back(definition);
}

bool Word::addCategory(CategoryInfo *info, QString value) {
    Category *category = new Category(this, info);
    if (category->setValue(value)) {
        this->m_categories.append(category);
        return true;
    } else {
        return false;
    }
}

bool Word::removeCategory(Category* category) {
    int i = this->m_categories.indexOf(category);
    if (i >= 0) {
        this->m_categories.remove(i);
        return true;
    }

    return false;
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

int Word::compareHash(Word *word) { return this->compareHash(word->getHash()); }

int Word::compareHash(QStringView paramHash) {
    QString currentHash = this->getHash();
    Q_ASSERT(currentHash.length() == paramHash.length());

    int similarity = 0;
    for (int i = 0; i < K_VALUE; i += 2) {
        for (int j = 0; j < K_VALUE; j += 2) {
            if (currentHash[i] == paramHash[j])
                similarity += currentHash[i + 1].digitValue() +
                              paramHash[j + 1].digitValue();
        }
    }

    return K_LIMIT - similarity;
}
