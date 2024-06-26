#pragma once

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
};

class CourseSerializer {
  public:
    static void Serialize(QIODevice *device, Course *course);
    static Course *Deserialize(QIODevice *device, QObject *parent);
};
