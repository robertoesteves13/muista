#include "tests/dictionary_test.hpp"
#include "common/dictionary.hpp"

#include <QTest>

WordTest::WordTest(QObject *parent) : QObject(parent) {}
WordTest::~WordTest() {}

void WordTest::HashWord_data() {
    QTest::addColumn<Word*>("word");
    QTest::addColumn<QString>("result");

    QTest::addRow("english") << new Word(this, "coyote") << "o2c1y1";
    QTest::addRow("spanish") << new Word(this, "perro") << "r2e1p1";
    QTest::addRow("portuguese") << new Word(this, "caiaque") << "a2c1i1";
    QTest::addRow("japanese") << new Word(this, "こんにちは") << "\u30531\u30931\u306B1";
    QTest::addRow("chinese") << new Word(this, "热狗") << QString("\u70ED1\u72D7100");
    QTest::addRow("russian") << new Word(this, "Спасибо") << "\u04211\u043F1\u04301";
}

void WordTest::HashWord() {
    QFETCH(Word *, word);
    QFETCH(QString, result);

    QCOMPARE(word->GetHash(), result);
}
