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
            id: fileButton
            anchors.top:portList.bottom
              label: "File"
              value: player.midiFile;
              onClicked: {
                  pageStack.push(filePickerPage, {}, PageStackAction.Immediate)
              }
        }

        Component {
              id: filePickerPage
              FilePickerPage {
                  id: filePickerPage2
                  nameFilters: [ '*.mid', '*.MID' ]
                      onSelectedContentPropertiesChanged: {
                          selectedMidiFile.value = selectedContentProperties.filePath
                  }
                  property bool subPageInitialized: false
                  onStatusChanged: {
                      if ((status === PageStatus.Active) && !subPageInitialized && selectedMidiFile.value !== "") {
                          var path2 = selectedMidiFile.value.substring(0,selectedMidiFile.value.lastIndexOf("/"))
                          var name2 = path2.substring(path2.lastIndexOf("/") + 1)
                          // It's unfortunate that FilePickerPage does not have API for selecting starting point,
                          // this is bound to break at some point
                          this.children[1].selected({
                                                    name: name2,
                                                    iconSource: 'image://theme/icon-m-device',
                                                    path: path2
                                                    })
                          subPageInitialized = true
                      }
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
            anchors.top: fileButton.bottom
            text: application.errorString
            color: Theme.errorColor
        }
    }
}
