#pragma once

#include <QObject>
#include <QProperty>
#include <QQmlEngine>

class CourseInfo : public QObject {
    Q_OBJECT

    Q_PROPERTY(int identifier READ getId)
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(QString description READ getDescription WRITE setDescription)
    QML_ELEMENT
  public:
    CourseInfo(QObject *parent = nullptr, int id = 0, QString name = "???",
               QString description = "???");
    ~CourseInfo();

    int getId() { return m_id; }
    QString getName() { return m_name; }
    QString getDescription() { return m_description; }

    void setName(QString name);
    void setDescription(QString description);

  signals:
    void dataChanged();

  private:
    qint32 m_id;
    QString m_name, m_description;
};

class CourseSerializer {
  public:
    static void Serialize(QIODevice *device, CourseInfo *course);
    static CourseInfo *Deserialize(QIODevice *device, QObject *parent);
};
