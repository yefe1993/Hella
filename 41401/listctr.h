#ifndef LISTCTR_H
#define LISTCTR_H

#include <QObject>
#include <QString>
#include <iostream>
#include <memory>

using namespace std;

class ListCtr : public QObject
{
    Q_OBJECT
    /*---------------------------------------------------------------------------
     * Q_PROPERTY = 传数据
     * Q_INVOKABLE = 调函数
     *
     * property数据类型————QString
     * property名称————originalDisplay
     * property访问权限————READ originalDisplay(读取函数，所有属性访问都走函数接口)
     * Qt关键字————CONSTANT(成员属性永远不会变，QML不用监听)
     * Qt关键字————NOTIFY(成员属性可能会变，一旦变了请通知QML更新)
     *
     * NOTIFY reversedDisplayChanged:当这个属性的值发生变化时，通过信号 reversedDisplayChanged 通知 QML 更新,必须配套一个 signal
     * --------------------------------------------------------------------------
     */
    Q_PROPERTY(QString originalDisplay READ originalDisplay CONSTANT)//原链表,成员属性
    Q_PROPERTY(QString reversedDisplay READ reversedDisplay NOTIFY reversedDisplayChanged)//反转链表,成员属性

public:

    QString originalDisplay() const {
        return m_originalDisplay;
    }
    QString reversedDisplay() const {
        return m_reversedDisplay;
    }

    Q_INVOKABLE void reverse();

    struct Node{
        int val;
        std::unique_ptr<Node> next;

        Node(int v):val(v),next(nullptr){}
    };

    explicit ListCtr(QObject *parent = nullptr);

    // 属性读取函数



signals:
    void reversedDisplayChanged();   

private:
    QString formatList(const std::unique_ptr<Node> &head) const;
    std::unique_ptr<Node> m_head; //头指针
    QString m_originalDisplay;
    QString m_reversedDisplay;
};

#endif // LISTCTR_H
