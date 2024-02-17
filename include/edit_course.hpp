#pragma once

#include "common/course.hpp"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class EditCourseWindow;
}
QT_END_NAMESPACE

class EditCourseWindow : public QMainWindow {
    Q_OBJECT
  public:
    EditCourseWindow(QWidget *parent = nullptr);
    ~EditCourseWindow();

  public slots:
    void LoadCourse(Course* course);

  private:
    Ui::EditCourseWindow *ui;
};
