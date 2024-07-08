#pragma once

#include "common/dictionary.hpp"
#include <QObject>
#include <QProperty>
#include <QQmlEngine>

class Course : public QObject {
    Q_OBJECT

    Q_PROPERTY(qint32 id READ Id)
    Q_PROPERTY(QStringView name READ Name)
    Q_PROPERTY(QStringView description READ Description)
    QML_ELEMENT
  public:
    Course(QObject *parent = nullptr, int id = 0, QString name = "???",
           QString description = "???");
    ~Course();

    int Id() { return id; }
    QStringView Name() { return name; }
    QStringView Description() { return description; }

  private:
    qint32 id;
    QString name, description;
    Dictionary dictionary;
};

class CourseSerializer {
  public:
    static void Serialize(QIODevice *device, Course *course);
    static Course *Deserialize(QIODevice *device, QObject *parent);
};

class Lesson : public QObject {
    Q_OBJECT
    public:
        Lesson(QObject *parent = nullptr);
        ~Lesson();

        QStringView Name() { return this->name; }
        QStringView Content() { return this->content; }
    private:
        QString name;
        QString content;
};

