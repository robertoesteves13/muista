#include "models/course_list.hpp"

CourseListModel::CourseListModel(QObject *parent) : QAbstractListModel(parent) {
    this->appendData(new CourseInfo(this, 0, "finnish", "test"));
}

int CourseListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return this->m_data.length();
}

QVariant CourseListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    switch (role) {
        case NameRole:
            return this->m_data[index.row()]->getName();
        case DescriptionRole:
            return this->m_data[index.row()]->getDescription();
    }

    return QVariant();
}

bool CourseListModel::setData(const QModelIndex &index, const QVariant &value,
                              int role) {
    return false;
}

QHash<int, QByteArray> CourseListModel::roleNames() const
{
    QHash<int, QByteArray> result;

    result[NameRole] = "courseName";
    result[DescriptionRole] = "descriptionRole";

    return result;
}

void CourseListModel::appendData(CourseInfo *course) {
    this->beginInsertRows(QModelIndex(), this->m_data.length(), this->m_data.length());

    this->m_data.append(course);

    this->endInsertRows();
}
