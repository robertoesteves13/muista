#pragma once

#include "course.hpp"
#include <QAbstractListModel>

class CourseListModel : public QAbstractListModel {
    Q_OBJECT;
    Q_ENUMS(Roles)
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        DescriptionRole
    };

    explicit CourseListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::UserRole) override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void appendData(CourseInfo* course);

private:
    QList<CourseInfo*> m_data;
};
