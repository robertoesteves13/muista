import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    id: root

    required property string courseName
    property real padding: 16

    width: parent.width
    Text {
        Layout.alignment: Qt.AlignLeft
        Layout.leftMargin: root.padding

        text: root.courseName
    }

    Row {
        Layout.alignment: Qt.AlignRight
        Layout.rightMargin: root.padding
        spacing: 16

        Button {
            text: "Open"
        }

        Button {
            text: "Edit"
        }
    }
}
