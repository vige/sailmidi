import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {

    anchors.fill: parent

    Image {
        source: "../pages/harbour-sailmidi.png"
        anchors.centerIn: parent
        width: parent.width
        height: width
        opacity: 0.5
    }

    Column {

        anchors.centerIn: parent
        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("SailMidi")
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: player.midiFile.split("/").pop()
        }

    }

    CoverActionList {
        id: playAction
        enabled: !player.playing

        CoverAction {
            iconSource: "image://theme/icon-cover-play"
            onTriggered: player.play()

        }
    }

    CoverActionList {
        id: stopAction
        enabled: player.playing

        CoverAction {
            iconSource: "image://theme/icon-m-stop"
            onTriggered: player.stop()
        }
    }

}
