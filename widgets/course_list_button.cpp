#include "widgets/course_list_button.hpp"
#include "./ui_course_list_button.h"
#include "screens/start_screen.hpp"

#include <QMenu>
#include <QMouseEvent>
#include <QSqlError>
#include <QSqlQuery>

CourseListButton::CourseListButton(QWidget *parent, Course *course)
    : QWidget(parent), ui(new Ui::CourseListButton) {
    this->ui->setupUi(this);
    this->course = course;
    this->course->setParent(this);

    this->ui->name->setText(course->name);

    this->contextMenu = new QMenu(this);
    this->actionEdit = this->contextMenu->addAction("Edit");
    this->actionDelete = this->contextMenu->addAction("Delete");

    connect(this->actionDelete, &QAction::triggered, this,
            &CourseListButton::deleteCourse);

    connect(this->actionEdit, &QAction::triggered, this,
            &CourseListButton::editCourse);
}

void CourseListButton::deleteCourse() {
    QSqlQuery query;
    QString sql = "DELETE FROM courses WHERE (id_pk = :id)";

    query.prepare(sql);
    query.bindValue(":id", this->course->id);

    if (!query.exec()) {
        qDebug() << "Some error ocurred while deleting a course"
                 << query.lastError().text();
    }

    if (auto screen = qobject_cast<StartScreen *>(this->parent())) {
        screen->removeItem(this);
    }
}

void CourseListButton::editCourse() {
    if (auto screen = qobject_cast<StartScreen *>(this->parent())) {
        screen->editCourse(course);
    }
}

#ifndef QT_NO_CONTEXTMENU
void CourseListButton::contextMenuEvent(QContextMenuEvent *event) {
    this->contextMenu->exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

CourseListButton::~CourseListButton() { delete ui; }
