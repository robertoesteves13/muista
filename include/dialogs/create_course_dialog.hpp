#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class CreateCourseDialog;
}
QT_END_NAMESPACE

class CreateCourseDialog : public QDialog {
  Q_OBJECT
public:
  CreateCourseDialog(QWidget *parent = nullptr);
  ~CreateCourseDialog();
signals:
  void createCourse(QString, QString);
public slots:
  void accept() override;
private:
  Ui::CreateCourseDialog *ui;
};
