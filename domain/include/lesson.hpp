#pragma once

#include <QObject>

class LessonInfo : public QObject {
    Q_OBJECT;

  public:
    enum LessonType : uint8_t { Reading, Explanation, Exercise };
    explicit LessonInfo(QObject *parent = nullptr);

    QString getName() { return m_name; }
    LessonType getType() { return m_type; }

    void setName(QString name);

  signals:
    void dataChanged();

  private:
    QString m_name;
    LessonType m_type;
};

class ReadingLesson : public QObject {
    Q_OBJECT
  public:
    ReadingLesson(QObject *parent = nullptr);
    ~ReadingLesson();

    QString getContent() { return m_content; }

  private:
    QString m_content;
};
