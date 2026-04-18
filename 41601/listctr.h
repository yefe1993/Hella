#ifndef LISTCTR_H
#define LISTCTR_H

#include <QObject>
#include <QString>

class ListCtr : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString displayShow READ displayShow NOTIFY displayChanged)

public:
    explicit ListCtr(QObject *parent = nullptr);
    ~ListCtr();

    QString displayShow() const{
        return display;
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

signals:
    // ✅ 只有一个 NOTIFY 信号
    void displayChanged();

private:
    QString formatList(const Node* head) const;
    Node* head;
    Node* tail;
    QString display;
};

#endif // LISTCTR_H
