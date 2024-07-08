#pragma once

#include "common/dictionary.hpp"

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

        QCOMPARE(word->GetHash(), result);
    }
};

class DictionaryTest : public QObject {
    Q_OBJECT
  private slots:
    void SearchWord() {
        Dictionary *dict = new Dictionary(this);
        dict->AddWord("cachorro", "dog");
        dict->AddWord("gato", "cat");
        dict->AddWord("colher", "spoon");
        dict->AddWord("garfo", "fork");
        dict->AddWord("porta", "door");
        dict->AddWord("pote", "pot");

        QVector<Word *> expected = QVector<Word *>();
        expected.push_back(new Word(this, "pote"));
        expected.push_back(new Word(this, "porta"));

        QVector<Word *> result = dict->SearchWord(QString("po"));

        QCOMPARE(result.length(), expected.length());
        for (int i = 0; i < result.length(); i++) {
            QVERIFY(result[i]->Value() != expected[i]->Value());
        }
    }
};

class WordTrackerTest : public QObject {
    Q_OBJECT;
  private slots:
      void GetBestWords() {
        Dictionary *dict = new Dictionary(this);
        dict->AddWord("cachorro", "dog");
        dict->AddWord("gato", "cat");
        dict->AddWord("colher", "spoon");
        dict->AddWord("garfo", "fork");
        dict->AddWord("porta", "door");
        dict->AddWord("pote", "pot");


        WordTracker* tracker = dict->Tracker();

        Word* word = dict->SearchWord(QString("cachorro")).first();
        tracker->AddWord(word);

        WordTrack* track = tracker->GetTrack(word);
        track->RegisterExercise(true);

        WordProficiency expected = WordProficiency::Learning;
        QCOMPARE(track->Proficiency(), expected);
      }
};
