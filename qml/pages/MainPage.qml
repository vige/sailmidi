import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.Pickers 1.0
import sailmidi 1.0

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent
        contentHeight: midiColumn.height

        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
        }

        SilicaListView {
            id: portList

            height: parent.height / 3

            model: player.portModel

            header: PageHeader {
                id: header
                title: "MIDI ports"
            }

            delegate: ListItem {
                Button {
                    x: Theme.horizontalPageMargin
                    text: name
                    color: open ? Theme.highlightColor : Theme.primaryColor
                    onClicked: player.portModel.openPort(index)
                }                
            }
        }


        ValueButton {
            anchors.top:portList.bottom
//              anchors.centerIn: parent
              label: "File"
              value: player.midiFile;
              onClicked: {
                  pageStack.push(filePickerPage)
              }
        }

        Component {
              id: filePickerPage
              FilePickerPage {
                  nameFilters: [ '*.mid', '*.MID' ]
                      onSelectedContentPropertiesChanged: {
                      player.midiFile = selectedContentProperties.filePath
                  }
              }
         }

        IconButton {
            anchors.bottom: parent.bottom
            width: parent.width / 2
            height: parent.width / 2
            x: parent.width / 4
            id: playButton
            icon.source: "image://theme/icon-l-play"
            visible: !player.playing
            onClicked: player.play()
        }

        IconButton {
            anchors.bottom: parent.bottom
            width: parent.width / 2
            height: parent.width / 2
            x: parent.width / 4
            id: stopButton
            icon.source: "image://theme/icon-m-stop"
            visible: player.playing
            onClicked: player.stop()
        }


        Label {
            id: errorLabel
        }
    }
}
