#pragma once

#include "common/dictionary.hpp"
#include <QObject>
#include <QProperty>
#include <QQmlEngine>

class Course : public QObject {
    Q_OBJECT

    Q_PROPERTY(int identifier READ Id)
    Q_PROPERTY(QString name READ Name)
    Q_PROPERTY(QString description READ Description)
    QML_ELEMENT
  public:
    Course(QObject *parent = nullptr, int id = 0, QString name = "???",
           QString description = "???");
    ~Course();

    int Id() { return id; }
    QString Name() { return name; }
    QString Description() { return description; }

  public slots:
    QVector<Word *> SearchDefinition(QStringView word);

  signals:
    QStringView addWordRequest();
    QStringView removeWordRequest();

  private:
    qint32 id;
    QString name, description;
    Dictionary *dictionary;
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

  signals:
    QStringView definitionRequest();

  private:
    QString name;
    QString content;
};
