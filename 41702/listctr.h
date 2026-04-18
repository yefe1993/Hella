#ifndef LISTCTR_H
#define LISTCTR_H

#include <QObject>
#include <QString>

class ListCtr : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString displayShow READ displayShow NOTIFY displayChanged)
    Q_PROPERTY(QString newDisplayShow READ newDisplayShow NOTIFY newDisplayShowChanged)

public:
    explicit ListCtr(QObject *parent = nullptr);
    ~ListCtr();

    QString displayShow() const{
        return display;
    }

    QString newDisplayShow() const{
        return sortDisplay;
    }

    void updateDisplay();

    struct Node {
        int val;
        Node* next;
        Node(int v) : val(v), next(nullptr) {}
    };

    // 链表操作
    void push_front(int data);
    void push_back(int data);
    void pop_front();
    void pop_back();

    // QML 调用
    Q_INVOKABLE void pushF(int val);
    Q_INVOKABLE void pushB(int val);
    Q_INVOKABLE void popF();
    Q_INVOKABLE void popB();

    Q_INVOKABLE void mS();

    Node* mergeSort();

signals:
    // NOTIFY 信号
    void displayChanged();
    void newDisplayShowChanged();

private:
    QString formatList(const Node* head) const;
    Node* head;
    Node* tail;
    QString display;
    QString sortDisplay;

    Node* merge(Node* leftHead,Node* rightHead);
    int length;

    int getLength();

    Node* split(Node* h,int i);
};

#endif // LISTCTR_H
