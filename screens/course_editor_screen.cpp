#include "screens/course_editor_screen.hpp"
#include "ui_course_editor_screen.h"

CourseEditorScreen::CourseEditorScreen(QWidget *parent)
    : QWidget(parent), ui(new Ui::CourseEditorScreen) {
    this->ui->setupUi(this);
}

CourseEditorScreen::~CourseEditorScreen() { delete ui; }

void CourseEditorScreen::SetCourse(Course *course) {
    this->course = course;
    this->course->setParent(this);
}
