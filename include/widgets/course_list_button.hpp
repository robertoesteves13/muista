#pragma once

#include <QContextMenuEvent>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class CourseListButton;
}
QT_END_NAMESPACE

class CourseListButton : public QWidget {
    Q_OBJECT
  public:
    CourseListButton(QWidget *parent = nullptr, int id = 0, QString label = "",
                     QString description = "");
    ~CourseListButton();
  public slots:
      void deleteCourse();

  protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

  private:
    Ui::CourseListButton *ui;
    QMenu *contextMenu;
    QAction *actionEdit, *actionDelete;

    int id;
};
