import QtQuick 2.0
import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    SilicaFlickable {
        contentHeight: column.height
        anchors.fill: parent

        Column {
            id: column
            anchors.fill: parent

            PageHeader {
                title: "Sailmidi"
                description: "Version 1.0"
            }

            Label {
                text: "Copyright(c) 2023 Ville Nummela"
            }

            Label {
                text: "Sources available at:"
            }

            LinkedLabel {
                plainText: "https://github.com/vige/sailmidi"
            }
        }
    }
}
