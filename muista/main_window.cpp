#include "main_window.hpp"
#include "./ui_main_window.h"
#include "dialogs/create_course_dialog.hpp"
#include "screens/start_screen.hpp"
#include "widgets/course_list_button.hpp"

#include <QDir>
#include <QListWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);

    int err = startDatabase();
    if (err != 0) {
        throw err;
    }

    auto startScreen = new StartScreen(this);
    startScreen->updateList();
    this->changeScreen(startScreen);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::changeScreen(QWidget *widget) {

    if (!this->ui->layout->isEmpty()) {
        if (QWidget *widget = this->ui->layout->takeAt(0)->widget()) {
            widget->deleteLater();
        }

        if (!this->ui->layout->isEmpty()) {
        qDebug() << "WARN: Main window screen has more than one widget (don't "
                    "manipulate layout directly!)";
        }
    }

    widget->setParent(this);
    this->ui->layout->addWidget(widget);
}

void MainWindow::createCourse(QString name, QString desc) {
    QSqlQuery query;
    QString sql = "INSERT INTO courses (name, description)"
                  "VALUES (:name, :description)";

    query.prepare(sql);
    query.bindValue(":name", name);
    query.bindValue(":description", desc);
    if (!query.exec()) {
        qDebug() << "Failed to create course:" << query.lastError().text();
    }

    int id = query.lastInsertId().toInt();
    if (StartScreen *screen = qobject_cast<StartScreen*>(this->ui->layout->itemAt(0)->widget())) {
        screen->insertCourse(id, name, desc);
    }
}

void MainWindow::openCreateCourseDiag() {
    auto dialog = new CreateCourseDialog(this);
    QObject::connect(dialog, &CreateCourseDialog::createCourse, this,
                     &MainWindow::createCourse);

    dialog->show();
}

int MainWindow::startDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString file = QStandardPaths::locate(QStandardPaths::AppLocalDataLocation,
                                          "database.db");
    if (file == "") {
        QString path = QStandardPaths::writableLocation(
            QStandardPaths::AppLocalDataLocation);
        if (path.isEmpty()) {
            qFatal() << "Failed to get AppLocalDataLocation";
            return 1;
        }

        QDir dir(path);
        if (!dir.mkpath(dir.absolutePath())) {
            qFatal() << "Failed to create directory";
            return 1;
        }

        QDir::setCurrent(dir.absolutePath());
        db.setDatabaseName(dir.absoluteFilePath("database.db"));
        if (!db.open()) {
            qDebug() << "Failed to connect to database:"
                     << db.lastError().text();
            return 1;
        }
    } else {
        db.setDatabaseName(file);
        if (!db.open()) {
            qDebug() << "Failed to connect to database:"
                     << db.lastError().text();
            return 1;
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
        return 1;
    }

    return 0;
}
