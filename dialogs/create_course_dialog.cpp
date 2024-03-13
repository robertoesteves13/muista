#include "dialogs/create_course_dialog.hpp"
#include "./ui_create_course_dialog.h"

#include <QListWidget>

CreateCourseDialog::CreateCourseDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreateCourseDialog) {
  this->ui->setupUi(this);
}

void CreateCourseDialog::accept() {
  auto course = new Course(nullptr, 0, this->ui->nameEdit->text(), this->ui->descEdit->toPlainText());
  emit this->createCourse(course);
  this->deleteLater();
}

CreateCourseDialog::~CreateCourseDialog() { delete ui; }
