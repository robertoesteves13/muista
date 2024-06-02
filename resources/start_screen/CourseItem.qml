import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root
    required property int identifier
    required property string name
    property real padding: 16

    width: parent.width
    height: 24

    RowLayout {
        width: parent.width

        Text {
            Layout.alignment: Qt.AlignLeft
            Layout.leftMargin: root.padding

            text: root.name
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
}
