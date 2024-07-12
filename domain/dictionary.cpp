#include "dictionary.hpp"

#include <QDebug>
#include <QMessageLogger>

Dictionary::Dictionary(QObject *parent) : QObject(parent) {}

Dictionary::~Dictionary() {}

bool Dictionary::addWord(QString value, QString definition) {
    for (qsizetype i = 0; i < this->m_words.length(); ++i) {
        if (this->m_words[i]->getValue() == value)
            return false;
    }
    Word *word = new Word(this, value);
    word->addDefinition(definition);

    this->m_words.append(word);
    emit wordsChanged();
    return true;
}

bool Dictionary::removeWord(Word *word) {
    int i = this->m_words.indexOf(word);
    if (i < 0)
        return false;

    this->m_words.remove(i);
    emit wordsChanged();
    return true;
}

void Dictionary::relateWords(std::string_view pAntecessor,
                             std::string_view pChild) {
    qFatal("not implemented");
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

bool Dictionary::createCategory(QString name, QString description) {
    for (CategoryInfo *info : this->m_categories) {
        if (info->getName() == name) {
            return false;
        }
    }

    CategoryInfo *info = new CategoryInfo(this);
    info->setName(name);
    info->setDescription(description);
    this->m_categories.append(info);

    emit categoriesChanged();
    return true;
}

bool Dictionary::removeCategory(CategoryInfo *info) {
    uint64_t i = this->m_categories.indexOf(info);
    if (i < 0) {
        return false;
    }

    for (Word* word : this->m_words) {
        for (Category* category : word->getCategories()) {
            if (category->getInfo() == info) {
                word->removeCategory(category);
                break;
            }
        }
    }

    this->m_categories.remove(i);
    emit categoriesChanged();
    return true;
}
