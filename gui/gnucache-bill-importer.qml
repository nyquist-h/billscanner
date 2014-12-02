import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.2

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Button {
        id: exportBtn
        x: 547
        y: 450
        text: qsTr("Export")
    }

    Button {
        id: cancleBtn
        x: 461
        y: 450
        text: qsTr("Cancle")
    }

    Button {
        id: photoBtn
        x: 11
        y: 450
        text: qsTr("Take photo")
    }

    Button {
        id: scanBtn
        x: 97
        y: 450
        text: qsTr("Scan")
    }

    Button {
        id: importBtn
        x: 183
        y: 450
        text: "Import"
    }

    GroupBox {
        id: billGroupBox
        x: 11
        y: 20
        width: 616
        height: 418
        visible: true
        checkable: false
        flat: true
        title: qsTr("Group Box")

        SplitView {
            id: billLayout
            x: 21
            y: 0
            width: 257
            height: 379
            orientation: Qt.Horizontal
        }

        Slider {
            id: billSlider
            x: 0
            y: 0
            width: 22
            height: 351
            orientation: Qt.Vertical
        }
    }
}
