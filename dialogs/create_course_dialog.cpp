#include "dialogs/create_course_dialog.hpp"
#include "./ui_create_course_dialog.h"

#include <QListWidget>
#include <format>

CreateCourseDialog::CreateCourseDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreateCourseDialog) {
  this->ui->setupUi(this);
}

void CreateCourseDialog::accept() {
  emit this->createCourse(this->ui->nameEdit->text(), this->ui->descEdit->toPlainText());
  this->deleteLater();
}

CreateCourseDialog::~CreateCourseDialog() { delete ui; }
