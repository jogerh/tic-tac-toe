import QtQml
import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import tictactoe
import "TicTacToeUi"

Window {
    id: mainWindow
    visible: true
    width: 760
    height: 810
    minimumWidth: 475
    minimumHeight: 300

    title: qsTr("Tic Tac Toe")

    Rectangle {
        id: root
        anchors.fill: parent
        color: "#424242"

        ColumnLayout {
            anchors.fill: parent

            Board {
                id: board
                textColor: root.color
                backgroundColor: "white"
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredHeight: 300
            }

            GameControls {
                Layout.fillWidth: true
                Layout.preferredHeight: 70
                model: board.model
                font.pixelSize: 30; font.family: "Comic Sans MS"
                backgroundColor: root.color
                textColor: "white"
            }
        }

        Rectangle {
            id: banner
            anchors.fill: parent
            color: "#bb424242"

            visible: false

            Text {
                id: gameResult
                anchors.fill: parent
                text: ""
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                font.pixelSize: 50; font.family: "Comic Sans MS"
                color: "white"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: board.model.revert()
            }
        }

        states: [
            State {
                when: board.model.gameStatus === GameModel.HumanPlays
                PropertyChanges {
                    banner.visible: false
                    cpuTimer.running: false
                }
            },
            State {
                when: board.model.gameStatus === GameModel.CpuPlays
                PropertyChanges {
                    banner.visible: false
                    cpuTimer.running: true
                }
            },
            State {
                when: board.model.gameStatus === GameModel.HumanLoose
                PropertyChanges{
                    banner.visible: true
                    gameResult.text: "You loose"
                }
            },
            State {
                when: board.model.gameStatus === GameModel.HumanWin
                PropertyChanges{
                    banner.visible: true
                    gameResult.text: "You won!"
                }
            },
            State {
                when: board.model.gameStatus === GameModel.Tie
                PropertyChanges{
                    banner.visible: true
                    gameResult.text: "It's a tie :("
                }
            }
        ]

        Timer{
            id: cpuTimer
            interval: 500
            running: false
            onTriggered: board.model.playCpu();
        }
    }
}
