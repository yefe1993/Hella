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

    Q_PROPERTY(QString originalDisplay READ originalDisplay CONSTANT)//原链表,成员属性
    Q_PROPERTY(QString reversedDisplay READ reversedDisplay NOTIFY reversedDisplayChanged)//反转链表,成员属性


public:
    struct Node{
        int val;
        std::unique_ptr<Node> next;

        Node(int v):val(v),next(nullptr){}
    };

    class iterator{
    private:
        Node* curr;

    public:
        //---------------------------------构造函数
        iterator(Node* ptr = nullptr):curr(ptr){}

        //---------------------------------运算符重载*返回val、++自增返回iterator&、返回!=bool
        //期望 *it 能够 读、写 节点中的值（int val），所以返回 int&（取 该指针 指向的地址 的存储值）。
        int& operator*() const{
            return curr->val;
        }
        //返回自增后迭代器自身的引用，为了*it解引用能修改节点数据
        iterator& operator++(){
            if(curr){
                curr = curr->next.get();
            }
            return *this;
        }
        bool operator!=(const iterator& other) const{
            return curr != other.curr;
        }
    };

    //普通类 class Name { ... };

    QString originalDisplay() const {
        return m_originalDisplay;
    }
    QString reversedDisplay() const {
        return m_reversedDisplay;
    }

    Q_INVOKABLE void reverse();

    explicit ListCtr(QObject *parent = nullptr);

    //-----------------------------------------begin()、end()
    iterator begin() {
        return iterator(m_head.get());  // 获取头节点的裸指针
    }
    iterator end() {
        return iterator(nullptr);  // 获取头节点的裸指针
    }
signals:
    void reversedDisplayChanged();

private:
    QString formatList(const std::unique_ptr<Node> &head) const;
    std::unique_ptr<Node> m_head; //头指针
    QString m_originalDisplay;
    QString m_reversedDisplay;


};

#endif // LISTCTR_H
