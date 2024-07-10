import QtQuick.Controls

import "start_screen"

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Muista")

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&New...")
            }
            Action {
                text: qsTr("&Open...")
            }
            Action {
                text: qsTr("&Save")
            }
            Action {
                text: qsTr("Save &As...")
            }
            MenuSeparator {}
            Action {
                text: qsTr("&Quit")
            }
        }

        Menu {
            title: qsTr("&Edit")
            Action {
                text: qsTr("Cu&t")
            }
            Action {
                text: qsTr("&Copy")
            }
            Action {
                text: qsTr("&Paste")
            }
        }

        Menu {
            title: qsTr("&Help")
            Action {
                text: qsTr("&About")
            }
        }
    }

    StartScreen {
        objectName: "StartScreen"
        anchors.fill: parent
    }

}
