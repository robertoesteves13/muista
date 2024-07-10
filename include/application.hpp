#pragma once

#include <QGuiApplication>

#include "common/course.hpp"

class MuistaApp : public QGuiApplication {
    Q_OBJECT
  public:
    MuistaApp(int argc, char **argv);
    ~MuistaApp();
  public slots:
      QVector<Course*> ListCourses();
      void SaveCourse(Course *course);


  private:
    void initDatabase();
};
