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
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredHeight: 300
            }

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

                    ComboBox {

                        id: control
                        anchors.centerIn: parent
                        currentIndex: 2
                        textRole: "text"
                        valueRole: "level"
                        font.pixelSize: 30; font.family: "Comic Sans MS"

                        background: Rectangle {
                            color: root.color
                        }

                        delegate: ItemDelegate {
                            width: control.width
                            contentItem: Text {
                                text: model[control.textRole]
                                color: "black"
                                font: control.font
                                elide: Text.ElideRight
                                verticalAlignment: Text.AlignVCenter
                            }
                            highlighted: control.highlightedIndex === index
                        }

                        contentItem: Text {
                            text: control.displayText
                            font: control.font
                            color: "white"
                            elide: Text.ElideRight
                        }

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
