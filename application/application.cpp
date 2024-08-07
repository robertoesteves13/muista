#include "application.hpp"

#include <QDir>
#include <QStandardPaths>

#define DATA_LOCATION QStandardPaths::AppLocalDataLocation

MuistaApp::MuistaApp(int argc, char **argv) : QGuiApplication(argc, argv) {
    this->setOrganizationDomain("robertoesteves.dev");
    this->setApplicationName("muista");
    this->setApplicationDisplayName("Muista");

    QString path = QStandardPaths::writableLocation(DATA_LOCATION);
    QDir dir(path);

    if (path.isEmpty()) {
        qFatal("Can't determine a path to store application files!");
    }

    if (!dir.exists()) {
        QDir().mkdir(dir.absolutePath());
        dir.mkdir("courses");
    }
}

MuistaApp::~MuistaApp() {}

QVector<CourseInfo *> MuistaApp::listCourses() {
    QString path = QStandardPaths::locate(DATA_LOCATION, "courses/");
    QDir coursesDir(path);

    QVector<CourseInfo *> courses;
    for (QFileInfo info : coursesDir.entryInfoList(
             QDir::Filter::Dirs | QDir::Filter::NoDotAndDotDot)) {
        QDir courseDir(info.absoluteFilePath());
        QFile manifest = QFile(courseDir.filePath("manifest.xml"));
        CourseInfo *course = CourseSerializer::Deserialize(&manifest, this);
        courses.push_back(course);
    }

    return courses;
}

void MuistaApp::saveCourse(CourseInfo *course) {
    QString path = QStandardPaths::locate(DATA_LOCATION, "courses/");
    QDir coursesDir(path);

    QString dirName =
        QString::number(course->getId()) + ":" + course->getName();

    bool created;
    int inc = 0;
    do {
        if (inc != 0) {
            dirName += "(" + QString::number(inc) + ")";
        }
        ++inc;

        created = coursesDir.mkdir(dirName);
    } while (!created);

    QDir courseDir(coursesDir.filePath(dirName));
    QFile manifestFile(courseDir.filePath("manifest.xml"));

    manifestFile.open(QFile::WriteOnly);
    CourseSerializer::Serialize(&manifestFile, course);
    manifestFile.close();
}

void MuistaApp::initDatabase() {}
