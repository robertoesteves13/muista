#pragma once

#include "common/course.hpp"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
  public slots:
    void openCreateCourseDiag();
    void ChangeToStart();
    void ChangeToEditor(Course *course);

  private:
    void changeScreen(QWidget *widget);

  private:
    Ui::MainWindow *ui;
};
