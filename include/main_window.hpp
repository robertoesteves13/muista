#pragma once

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
  void createCourse(QString name, QString desc);
  void openCreateCourseDiag();
  void changeScreen(QWidget* widget);

private:
  int startDatabase();
  Ui::MainWindow *ui;
};
