import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root
    implicitWidth: layout.implicitWidth
    implicitHeight: layout.implicitHeight

    signal onCancel
    signal onCreate

    ColumnLayout {
        id: layout
        Layout.fillWidth: true
        Layout.fillHeight: true

        TextField {
            id: nameField
            Layout.fillWidth: true
            placeholderText: "Enter name"
        }

        Frame {
            Layout.minimumHeight: 200
            Layout.minimumWidth: 280

            padding: 0
            TextArea {
                id: descriptionField
                Layout.fillWidth: true
                Layout.fillHeight: true

                implicitWidth: parent.width
                implicitHeight: parent.height

                placeholderText: "Enter description"
            }

        }


        RowLayout {
            Layout.alignment: Qt.AlignRight
            Button {
                text: "Cancel"
                onPressed: () => {
                    nameField.text = '';
                    descriptionField.text = '';
                    root.onCancel();
                }
            }
            Button {
                text: "Create"
                onPressed: root.onCreate()
            }
        }
    }
        
}
