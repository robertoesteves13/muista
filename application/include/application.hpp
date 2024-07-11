#pragma once

#include <QGuiApplication>

#include "course.hpp"

class MuistaApp : public QGuiApplication {
    Q_OBJECT
  public:
    MuistaApp(int argc, char **argv);
    ~MuistaApp();
  public slots:
      QVector<Course*> listCourses();
      void saveCourse(Course *course);


  private:
    void initDatabase();
};
