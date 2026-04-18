import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    width: 840
    height: 480
    visible: true
    title: qsTr("单链表的头尾增删")

    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 30
        spacing: 30

        RowLayout{
            Layout.fillWidth: true
            spacing: 20

            Button {
                text: "链表头部插入新节点"
                Layout.preferredWidth: 200
                onClicked: {
                    let val = parseInt(inputFront.text)
                    if (!isNaN(val)) {
                        Linklist.pushF(val)
                    }
                }
            }

            TextField {
                id: inputFront
                placeholderText: "输入头部新节点的数据值"
                Layout.preferredWidth: 200
            }

            Item {
                Layout.fillWidth: true
            } // 空白占位

            Button {
                text: "链表头部删除头节点"
                Layout.preferredWidth: 200
                onClicked: {
                    // 通过 id 读取文本，转换后调用 C++ 函数
                    Linklist.popF()
                }
            }
        }
        RowLayout{
            Layout.fillWidth: true
            spacing: 20

            Button {
                text:"链表尾部插入新节点"
                Layout.preferredWidth: 200
                onClicked: {
                    let val = parseInt(inputBack.text)
                    if (!isNaN(val)) {
                        Linklist.pushB(val)
                    }
                }
            }

            TextField{
                id: inputBack
                placeholderText: "输入尾部新节点的数据值"
                Layout.preferredWidth: 200
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                text:"链表尾部删除末节点"
                Layout.preferredWidth: 200
                onClicked: {
                    // 通过 id 读取文本，转换后调用 C++ 函数
                    Linklist.popB()
                }
            }
        }

        Text {
            Layout.fillWidth: true
            text: "链表: " + Linklist.displayShow
            font.pixelSize: 22  //字体的像素大小
            font.family: "Consolas, monospace"  //设置字体“家族”（font family）  monospace系统默认等宽字体
            wrapMode: Text.Wrap //如果文字太长了，装不下怎么办？换行显示。防止撑破窗口
        }
    }
}
