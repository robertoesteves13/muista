#include "main_window.hpp"
#include "./ui_main_window.h"
#include "application.hpp"
#include "dialogs/create_course_dialog.hpp"
#include "screens/start_screen.hpp"

#include <QDir>
#include <QListWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);
    this->ChangeToStart();
}

void MainWindow::ChangeToStart() {
    auto startScreen = new StartScreen(this);
    startScreen->updateList();
    this->changeScreen(startScreen);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::changeScreen(QWidget *widget) {
    if (!this->ui->layout->isEmpty()) {
        if (QWidget *widget = this->ui->layout->takeAt(0)->widget()) {
            widget->deleteLater();
        }

        if (!this->ui->layout->isEmpty()) {
            qDebug()
                << "WARN: Main window screen has more than one widget (don't "
                   "manipulate layout directly!)";
        }
    }

    widget->setParent(this);
    this->ui->layout->addWidget(widget);
}

void MainWindow::openCreateCourseDiag() {
    auto dialog = new CreateCourseDialog(this);
    auto app = QApplication::instance();
    if (auto muista = qobject_cast<MuistaApp *>(app)) {
        QObject::connect(dialog, &CreateCourseDialog::createCourse, muista,
                         &MuistaApp::CreateCourse);
    }

    if (StartScreen *scr = qobject_cast<StartScreen *>(
            this->ui->layout->itemAt(0)->widget())) {
        QObject::connect(dialog, &CreateCourseDialog::createCourse, scr,
                         &StartScreen::updateList);
    }

    dialog->show();
}
