import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import tictactoe

RowLayout {
    Layout.fillWidth: true
    Layout.preferredHeight: 70

    BusyIndicator {
        running: board.model.gameStatus === GameModel.CpuPlays
    }

    Rectangle {
        Layout.fillWidth: true
        Text {
            anchors.centerIn: parent
            text: "Wins: " + board.model.gameStats.Wins
            fontSizeMode: Text.Fit; font.pixelSize: 30; font.family: "Comic Sans MS"
            color: "white"
        }
    }
    Rectangle {
        Layout.fillWidth: true
        Text {
            anchors.centerIn: parent
            text: "Ties: " + board.model.gameStats.Ties
            fontSizeMode: Text.Fit; font.pixelSize: 30; font.family: "Comic Sans MS"
            color: "white"
        }
    }
    Rectangle {
        Layout.fillWidth: true
        Text {
            anchors.centerIn: parent
            text: "Losses: " + board.model.gameStats.Losses
            fontSizeMode: Text.Fit; font.pixelSize: 30; font.family: "Comic Sans MS"
            color: "white"
        }
    }
    Rectangle{
        Layout.fillWidth: true
        color: "green"
        Layout.preferredWidth: 2

        LevelComboBox{
            anchors.centerIn: parent
            font.pixelSize: 30; font.family: "Comic Sans MS"
            currentIndex: 2

            backgroundColor: root.color
            textColor: "white"

            model: ListModel {
                id: difficultyItems
                ListElement {text: "Easy"; level: GameModel.Easy}
                ListElement {text: "Medium"; level: GameModel.Medium}
                ListElement {text: "Impossible"; level: GameModel.Impossible}
            }

            onCurrentIndexChanged: board.model.difficulty = difficultyItems.get(currentIndex).level
        }
    }
}
