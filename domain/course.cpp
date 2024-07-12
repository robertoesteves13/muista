#include "course.hpp"

#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

CourseInfo::CourseInfo(QObject *parent, int id, QString name, QString description)
    : QObject(parent) {
    this->m_id = id;
    this->m_name = name;
    this->m_description = description;
}

void CourseInfo::setName(QString name)
{
    this->m_name = name;
    emit this->dataChanged();
}

void CourseInfo::setDescription(QString description)
{
    this->m_description = description;
    emit this->dataChanged();
}

CourseInfo::~CourseInfo() {}

void CourseSerializer::Serialize(QIODevice *device, CourseInfo *course) {
    QXmlStreamWriter w(device);
    w.setAutoFormatting(true);
    w.writeStartDocument();

    w.writeStartElement("Course");
    w.writeAttribute("id", QString::number(course->getId()));
    w.writeTextElement("Name", course->getName());
    w.writeTextElement("Description", course->getDescription());
    w.writeEndElement();

    w.writeEndDocument();
}

CourseInfo *CourseSerializer::Deserialize(QIODevice *device, QObject *parent) {
    QXmlStreamReader r(device);
    QMap<QString, QString> map;

    while (!r.atEnd()) {
        auto t = r.readNext();
        switch (t) {
        case QXmlStreamReader::NoToken:
            break;
        case QXmlStreamReader::Invalid:
            break;
        case QXmlStreamReader::StartDocument:
            break;
        case QXmlStreamReader::EndDocument:
            break;
        case QXmlStreamReader::StartElement:
            if (r.name().toString() == "Course") {
                map.insert("id", r.attributes().value("id").toString());
            }

            if (r.name().toString() == "Name") {
                map.insert("name", r.readElementText());
            }

            if (r.name().toString() == "Description") {
                map.insert("description", r.readElementText());
            }
        case QXmlStreamReader::EndElement:
            break;
        case QXmlStreamReader::Characters:
            break;
        case QXmlStreamReader::Comment:
            break;
        case QXmlStreamReader::DTD:
            break;
        case QXmlStreamReader::EntityReference:
            break;
        case QXmlStreamReader::ProcessingInstruction:
            break;
        }
    }

    return new CourseInfo(parent, map["id"].toInt(), map["name"],
                      map["description"]);
}
