#pragma once

#include "dictionary.hpp"
#include "word_tracker.hpp"

#include <QObject>
#include <QTest>

class WordTest : public QObject {
    Q_OBJECT
  private slots:
    void HashWord_data() {
        QTest::addColumn<Word *>("word");
        QTest::addColumn<QString>("result");

        QTest::addRow("english") << new Word(this, "coyote") << "o2c1y1";
        QTest::addRow("english") << new Word(this, "poo") << "o2p100";
        QTest::addRow("spanish") << new Word(this, "perro") << "r2e1p1";
        QTest::addRow("portuguese") << new Word(this, "caiaque") << "a2c1i1";
        QTest::addRow("japanese")
            << new Word(this, "こんにちは") << "\u30531\u30931\u306B1";
        QTest::addRow("chinese")
            << new Word(this, "热狗") << QString("\u70ED1\u72D7100");
        QTest::addRow("russian")
            << new Word(this, "Спасибо") << "\u04211\u043F1\u04301";
    }

    void HashWord() {
        QFETCH(Word *, word);
        QFETCH(QString, result);

        QCOMPARE(word->getHash(), result);
    }

    void CategoryTest() {
        Dictionary *dict = new Dictionary(this);
        dict->addWord("cachorro", "dog");
        dict->createCategory("Type", "Type of word");

        Word *word = dict->searchWord(QString("cachorro")).first();
        CategoryInfo *info = dict->getCategories().first();
        info->addValue("Noun");
        info->addValue("Verb");
        info->addValue("Adjective");
        info->addValue("Adverb");

        {
            bool result = word->addCategory(info, "Noun");
            QCOMPARE(true, result);
        }

        {
            Category *expected = new Category(this, info);
            expected->setValue("Noun");

            QVector<Category *> categories = word->getCategories();
            QCOMPARE(1, categories.length());
            QCOMPARE(expected->getValue(), categories.first()->getValue());
        }

        {
            dict->removeCategory(info);
            QCOMPARE(0, dict->getCategories().length());
            QCOMPARE(0, word->getCategories().length());
        }
    }
};

class DictionaryTest : public QObject {
    Q_OBJECT
  private slots:
    void SearchWord() {
        Dictionary *dict = new Dictionary(this);
        dict->addWord("cachorro", "dog");
        dict->addWord("gato", "cat");
        dict->addWord("colher", "spoon");
        dict->addWord("garfo", "fork");
        dict->addWord("porta", "door");
        dict->addWord("pote", "pot");

        QVector<Word *> expected = QVector<Word *>();
        expected.push_back(new Word(this, "pote"));
        expected.push_back(new Word(this, "porta"));

        QVector<Word *> result = dict->searchWord(QString("po"));

        QCOMPARE(result.length(), expected.length());
        for (int i = 0; i < result.length(); i++) {
            QVERIFY(result[i]->getValue() != expected[i]->getValue());
        }
    }
};

class WordTrackerTest : public QObject {
    Q_OBJECT;
  private slots:
    void GetBestWords() {
        Dictionary *dict = new Dictionary(this);
        dict->addWord("cachorro", "dog");
        dict->addWord("gato", "cat");
        dict->addWord("colher", "spoon");
        dict->addWord("garfo", "fork");
        dict->addWord("porta", "door");
        dict->addWord("pote", "pot");

        WordTracker *tracker = new WordTracker(this);

        Word *word = dict->searchWord(QString("cachorro")).first();
        tracker->addTrack(word);

        WordTrack *track = tracker->getTrack(word);
        track->registerExercise(true);

        WordProficiency expected = WordProficiency::Learning;
        QCOMPARE(track->getProficiency(), expected);
    }
};
