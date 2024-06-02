import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import dev.robertoesteves.muista

Item {
    id: root
    property list<Course> courses

    ColumnLayout {
        anchors.fill: parent

        Text {
            Layout.alignment: Qt.AlignCenter
            text: "<b>Course list</b>"
            font.pointSize: 20
        }

        ScrollView {
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            Layout.fillHeight: true
            contentWidth: parent.width

            Column {
                anchors.fill: parent
                Layout.fillWidth: true
                topPadding: 12
                bottomPadding: 12
                spacing: 12

                ListView {
                    model: root.courses
                    delegate: CourseItem {
                        identifier: id
                        name: name
                    }
                }

                Rectangle {
                    color: "red"
                }
            }
        }

        Row {
            spacing: 12
            bottomPadding: 6
            Layout.alignment: Qt.AlignCenter

            Button {
                text: "Create"
                onPressed: addCourse.visible = true
            }

            Button {
                text: "Settings"
            }
        }
    }

    Popup {
        id: addCourse

        anchors.centerIn: Overlay.overlay
        contentWidth: view.implicitWidth
        contentHeight: view.implicitHeight

        modal: true
        focus: true

        AddCourse {
            id: view
            onOnCancel: () => {
                addCourse.visible = false;
            }
        }
    }
}
