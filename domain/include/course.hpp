#pragma once

#include <QObject>
#include <QProperty>
#include <QQmlEngine>

class Course : public QObject {
    Q_OBJECT

    Q_PROPERTY(int identifier READ getId)
    Q_PROPERTY(QString name READ getName)
    Q_PROPERTY(QString description READ getDescription)
    QML_ELEMENT
  public:
    Course(QObject *parent = nullptr, int id = 0, QString name = "???",
           QString description = "???");
    ~Course();

    int getId() { return m_id; }
    QString getName() { return m_name; }
    QString getDescription() { return m_description; }

    void setName(QString name);
    void setDescription(QString description);

  signals:
    void courseChanged();

  private:
    qint32 m_id;
    QString m_name, m_description;
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
