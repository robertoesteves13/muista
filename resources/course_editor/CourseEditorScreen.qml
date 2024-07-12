import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Control {
    component LessonEdit: Text {
        text: 'Work in progress...'

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    component DictionaryEdit : RowLayout {
    }

    contentItem: Column {
        TabBar {
            id: bar
            contentWidth: parent.width
            TabButton {
                text: 'Lessons'
            }
            TabButton {
                text: 'Dictionary'
            }
        }

        StackLayout {
            height: parent.height
            width: parent.width
            currentIndex: bar.currentIndex

            LessonEdit { }
        }
    }
}
