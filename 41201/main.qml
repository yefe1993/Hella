import QtQuick 2.15 // 基础零件箱：窗户(Window)、文字(Text)、矩形(Rectangle)
import QtQuick.Window 2.15
import QtQuick.Controls 2.15  // 高级零件箱：按钮(Button)、输入框、滑块 (这些都是现成的交互控件)
import QtQuick.Layouts 1.15   // 自动排版箱：ColumnLayout(竖排)、RowLayout(横排)

ApplicationWindow {
    width: 600
    height: 400
    visible: true
    title:"智能指针处理单链表反转"

    ColumnLayout{ //顺序就是从上到下显示的顺序
        anchors.centerIn: parent //锚定 (Anchors) - 把货架钉在窗体上
        spacing: 20

        // 标题
        Text {
            text: qsTr("链表反转")
            font.pixelSize: 30
            font.family: "Consolas, monospace"
            Layout.alignment: Qt.AlignHCenter
        }
        // 显示原链表
        Text {
            text: "原链表: " + listShow.originalDisplay
            font.pixelSize: 22  //字体的像素大小
            font.family: "Consolas, monospace"  //设置字体“家族”（font family）  monospace系统默认等宽字体
            wrapMode: Text.Wrap //如果文字太长了，装不下怎么办？换行显示。防止撑破窗口
            Layout.preferredWidth: 350
        }
        // 反转后
        Text {
            text: "反转后: " + listShow.reversedDisplay

            font.pixelSize: 22
            font.family: "Consolas, monospace"
            wrapMode: Text.Wrap
            Layout.preferredWidth: 350
        }
        Button {
            text: "执行反转"
            Layout.alignment: Qt.AlignHCenter  // Align Center 居中对齐

            onClicked: listShow.reverse()
        }

    }


}
