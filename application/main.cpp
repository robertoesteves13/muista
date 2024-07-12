#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlEngine>

#include "application.hpp"
#include "models/course_list.hpp"

#ifdef QT_DEBUG
#include <QQmlDebuggingEnabler>
QQmlTriviallyDestructibleDebuggingEnabler enable;
#endif

int main(int argc, char **argv) {
    MuistaApp app(argc, argv);

    qmlRegisterModule("dev.robertoesteves.muista", 1, 0);
    qmlRegisterType<CourseInfo>("dev.robertoesteves.muista", 1, 0, "Course");
    qmlRegisterType<CourseListModel>("dev.robertoesteves.muista", 1, 0, "CourseListModel");

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
