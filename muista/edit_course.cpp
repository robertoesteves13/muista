#include "edit_course.hpp"
#include "./ui_edit_course_window.h"

EditCourseWindow::EditCourseWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::EditCourseWindow) {
    this->ui->setupUi(this);
}

void EditCourseWindow::LoadCourse(Course *course) {
}

EditCourseWindow::~EditCourseWindow() {
    delete ui;
}
