#pragma once

#include "common/course.hpp"

#include <QApplication>

class MuistaApp : public QApplication {
    Q_OBJECT
  public:
    MuistaApp(int argc, char **argv);
    ~MuistaApp();

  public slots:
    void CreateCourse(Course *course);

  private:
    void startDatabase();
};
