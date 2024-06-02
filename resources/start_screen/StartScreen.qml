import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    ColumnLayout {
        anchors.fill: parent

        Rectangle {
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 32
            Text {
                anchors.centerIn: parent
                text: "<b>Course list</b>"
                font.pointSize: 20
            }
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

                CourseItem {
                    name: "Course 1"
                }

                CourseItem {
                    name: "Course 2"
                }
            }
        }

        Row {
            spacing: 12
            bottomPadding: 6
            Layout.alignment: Qt.AlignCenter

            Button {
                text: "Create"
            }

            Button {
                text: "Settings"
            }
        }
    }
}
