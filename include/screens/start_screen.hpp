#pragma once

#include "widgets/course_list_button.hpp"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class StartScreen;
}
QT_END_NAMESPACE

class StartScreen : public QWidget {
    Q_OBJECT
  public:
    StartScreen(QWidget *parent = nullptr);
    ~StartScreen();

    void insertCourse(int id, QString name, QString desc);
    void removeItem(CourseListButton* button);
    void checkIfEmpty();
  public slots:
    void updateList();

  private:
    Ui::StartScreen *ui;
};
