#pragma once

#include "common/course.hpp"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class CourseEditorScreen;
}
QT_END_NAMESPACE

class CourseEditorScreen : public QWidget {
    Q_OBJECT;

  public:
    explicit CourseEditorScreen(QWidget *parent = nullptr);
    ~CourseEditorScreen();

    void SetCourse(Course *course);

  signals:

  public slots:

  private:
    Ui::CourseEditorScreen *ui;
    Course *course;
};
