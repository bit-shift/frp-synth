import QtQuick 2.3
import QtQuick.Controls 1.3

ApplicationWindow {
    visible: true
    width: 200
    height: 300
    title: qsTr("frp-synth")

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

    Item {
        id: controls
        height: 250

        Item {
            id: waveKnob
            anchors.top: parent.top
            anchors.left: parent.left

            anchors.leftMargin: 20
            anchors.topMargin: 20

            Text {
                id: waveLabel
                text: qsTr("Waveform")
            }

            GroupBox {
                anchors.top: waveLabel.bottom
                anchors.topMargin: 0

                ExclusiveGroup { id: tabPositionGroup }
                RadioButton {
                    id: sineButton
                    text: "Sine"
                    checked: true
                    exclusiveGroup: tabPositionGroup
                    anchors.top: parent.top
                }
                RadioButton {
                    id: sawButton
                    text: "Saw"
                    exclusiveGroup: tabPositionGroup
                    anchors.top: sineButton.bottom
                }
                RadioButton {
                    id: squareButton
                    text: "Square"
                    exclusiveGroup: tabPositionGroup
                    anchors.top: sawButton.bottom
                }
            }

        }

        Item {
            id: freqKnob
            anchors.top: parent.top
            anchors.left: waveKnob.left

            anchors.leftMargin: 100
            anchors.topMargin: 20

            Text {
                id: freqLabel
                text: qsTr("Freq")
            }

            Slider {
                id: frequencyControl
                objectName: "frequencyControl"
                value: 0.0
                height: 200
                orientation: Qt.Vertical
                anchors.top: freqLabel.bottom;
                maximumValue: 10.0
            }


            Text {
                text: frequencyControl.value.toPrecision(2)
                anchors.top: frequencyControl.bottom;
            }
        }
    }



    Item {
        anchors.top: controls.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20

        Button {
            id: startStop
            objectName: "startStop"
            text: "Start"
            onClicked: {
                if ( text == "Start" ) {
                    text = "Stop";
                } else {
                    text = "Start";
                }
            }
        }
    }
}
