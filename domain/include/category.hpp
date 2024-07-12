#pragma once

#include <QObject>

class CategoryInfo : public QObject {
    Q_OBJECT
  public:
    CategoryInfo(QObject *parent = nullptr);
    ~CategoryInfo();

    QString getName() { return m_name; }
    QString getDescription() { return m_description; }
    const QVector<QString> getPossibleValues() { return m_possibleValues; }

    void setName(QString name);
    void setDescription(QString description);

    bool addValue(QString value);
    bool removeValue(QString value);

  signals:
    void dataChanged();

  private:
    QString m_name;
    QString m_description;
    QVector<QString> m_possibleValues;
};

class Category : public QObject {
    Q_OBJECT
  public:
    Category(QObject *parent = nullptr, CategoryInfo *info = nullptr);
    ~Category();

    CategoryInfo *getInfo() { return m_info; }
    QString getValue() { return m_value; }
    bool setValue(QString value);

  signals:
    void valueChanged();

  private:
    CategoryInfo *m_info;
    QString m_value;
};
