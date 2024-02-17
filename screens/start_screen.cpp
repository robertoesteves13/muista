#include "screens/start_screen.hpp"
#include "ui_start_screen.h"
#include "widgets/course_list_button.hpp"

#include <QLayoutItem>
#include <QSqlError>
#include <QSqlQuery>

StartScreen::StartScreen(QWidget *parent)
    : QWidget(parent), ui(new Ui::StartScreen) {
    this->ui->setupUi(this);
}

StartScreen::~StartScreen() { delete ui; }

void StartScreen::updateList() {
    QSqlQuery query;
    QString sql = "SELECT id_pk, name, description FROM courses";

    query.prepare(sql);
    if (!query.exec()) {
        qDebug() << "Failed to get course:" << query.lastError().text();
    }

    while (!this->ui->courseList->isEmpty()) {
        QLayoutItem *item = this->ui->courseList->takeAt(0);
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString desc = query.value(2).toString();

        auto course = new Course(this, id, name, desc);
        auto button = new CourseListButton(this, course);

        this->ui->courseList->addWidget(button);
    }

    this->checkIfEmpty();
}

void StartScreen::removeItem(CourseListButton* button) {
    if (button) {
        this->ui->courseList->removeWidget(button);
        delete button;
        this->checkIfEmpty();
    }
}

void StartScreen::checkIfEmpty() {
    if (this->ui->courseList->count() == 0) {
        auto label =
            new QLabel("No courses have been found, try to create one!", this);
        label->setAlignment(Qt::AlignCenter);
        this->ui->courseList->addWidget(label);
    }
}

void StartScreen::insertCourse(Course* course) {
    auto button = new CourseListButton(this, course);

    auto item = this->ui->courseList->itemAt(0);
    if (item) {
        if (qobject_cast<QLabel*>(item->widget())) {
            delete this->ui->courseList->takeAt(0)->widget();
        }
    }

    this->ui->courseList->addWidget(button);
}
