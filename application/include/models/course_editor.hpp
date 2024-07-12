#pragma once

#include "course.hpp"
#include "dictionary.hpp"
#include "lesson.hpp"

#include <QObject>
#include <QVector>

class CourseEditorModel : public QObject {
    Q_OBJECT

    QML_ELEMENT
  public:
    explicit CourseEditorModel(QObject *parent = nullptr);
    void load(CourseInfo* course);

    void createLesson(QString name);

  public slots:
    void populateDictionaryFromLessons();

  private:
    CourseInfo *m_currentCourse;
    QVector<LessonInfo*> m_lessons;
    Dictionary* m_dictionary;
};
