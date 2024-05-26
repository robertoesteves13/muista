#include <QCoreApplication>
#include <QTest>

#include "tests/dictionary_test.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    WordTest word;
    QTest::qExec(&word);

    return 0;
}
