#include "application.hpp"

#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>

MuistaApp::MuistaApp(int argc, char **argv) : QApplication(argc, argv) { 
    this->startDatabase();
}

void MuistaApp::CreateCourse(Course *course) {
    QSqlQuery query;
    QString sql = "INSERT INTO courses (name, description)"
                  "VALUES (:name, :description)";

    query.prepare(sql);
    query.bindValue(":name", course->name);
    query.bindValue(":description", course->description);
    if (!query.exec()) {
        qDebug() << "Failed to create course:" << query.lastError().text();
    }

    int id = query.lastInsertId().toInt();
    course->id = id;
}

void MuistaApp::startDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString file = QStandardPaths::locate(QStandardPaths::AppLocalDataLocation,
                                          "database.db");
    if (file == "") {
        QString path = QStandardPaths::writableLocation(
            QStandardPaths::AppLocalDataLocation);
        if (path.isEmpty()) {
            qFatal() << "Failed to get AppLocalDataLocation";
        }

        QDir dir(path);
        if (!dir.mkpath(dir.absolutePath())) {
            qFatal() << "Failed to create directory";
        }

        QDir::setCurrent(dir.absolutePath());
        db.setDatabaseName(dir.absoluteFilePath("database.db"));
        if (!db.open()) {
            qDebug() << "Failed to connect to database:"
                     << db.lastError().text();
        }
    } else {
        db.setDatabaseName(file);
        if (!db.open()) {
            qDebug() << "Failed to connect to database:"
                     << db.lastError().text();
        }
    }

    QSqlQuery query;
    QString sql = "CREATE TABLE IF NOT EXISTS courses("
                  "  id_pk INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "  name VARCHAR(255) NOT NULL,"
                  "  description VARCHAR(4096) NOT NULL"
                  ")";

    query.prepare(sql);
    if (!query.exec()) {
        qDebug() << "Failed to create courses table:"
                 << query.lastError().text();
    }
}

MuistaApp::~MuistaApp() {}
