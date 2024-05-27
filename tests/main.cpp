#include <QCoreApplication>
#include <QTest>

#include "tests/dictionary_test.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    WordTest word;
    DictionaryTest dict;

    QTest::qExec(&word);
    QTest::qExec(&dict);

    return 0;
}
