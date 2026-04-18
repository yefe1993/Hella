#include "listctr.h"
#include <QDebug>

ListCtr::ListCtr(QObject *parent)
    : QObject(parent), head(nullptr), tail(nullptr)
{
    display = formatList(head);
    length = getLength();
}

ListCtr::~ListCtr()
{
    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
}

void ListCtr::updateDisplay()
{
    display = formatList(head);
    emit displayChanged();
}

void ListCtr::push_front(int data)
{
    Node* newNode = new Node(data);
    newNode->next = head;
    head = newNode;
    if(tail == nullptr){
        tail = newNode;
    }
}

void ListCtr::push_back(int data)
{
    Node* newNode = new Node(data);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }

    // 情况二：链表非空
    tail->next = newNode;  // 原尾节点的 next 指向新节点
    tail = newNode;        // 更新 tail 为新尾节点
}

void ListCtr::pop_front()
{
    if(head == nullptr){
        return;
    }

    Node* curr = head;
    head = head->next;

    if(head == nullptr){
        tail = nullptr;
    }

    delete curr;
}

void ListCtr::pop_back()
{
    //空表
    if(tail == nullptr){
        return;
    }
    //单节点表
    if(head == tail){
        delete tail;
        tail = nullptr;
        head =nullptr;
        return;
    }

    //多节点表
    Node* curr = head;
    while(curr->next != tail){
        curr = curr->next;
    }
    delete tail;
    tail = curr;
    tail->next = nullptr;
}

void ListCtr::pushF(int val)
{
    qDebug() << "pushF val =" << val;
    push_front(val);
    updateDisplay();
}

void ListCtr::pushB(int val)
{
    push_back(val);
    updateDisplay();
}

void ListCtr::popF()
{
    pop_front();
    updateDisplay();
}

void ListCtr::popB()
{
    pop_back();
    updateDisplay();
}

void ListCtr::mS()
{
    head = mergeSort();
    Node* curr = head;
    while(curr->next){
        curr = curr->next;
    }
    tail = curr;
    sortDisplay = formatList(head);
    emit newDisplayShowChanged();
    qDebug() << sortDisplay;
}

ListCtr::Node *ListCtr::mergeSort()
{
    if (!head || !head->next) {
        return head;
    }

    length = getLength();
    int i = 1;
    Node dummy(0);
    dummy.next = head;
    //Node* prev = nullptr;

    while(i < length){
        Node* prev = &dummy;
        Node* curr = dummy.next;

        while(curr){
            Node* left = curr;
            Node* right = split(left,i);
            Node* next = split(right,i);
            prev->next = merge(left,right);
            while(prev->next){
                prev = prev->next;
            }
            curr = next;
        }
        i = i * 2;
    }

    return dummy.next;
}

QString ListCtr::formatList(const Node* head) const
{
    QStringList parts;
    const Node *curr = head;

    while(curr){
        parts << QString::number(curr->val);//把数字（整数/浮点数）转换成 QString 字符串
        curr = curr->next;
    }

    if(parts.isEmpty()){
        return QStringLiteral("NULL");
    }else{
        return parts.join(QStringLiteral("->"))+QStringLiteral("->NULL");
    }

}

int ListCtr::getLength()
{
    length = 0;
    if(head == nullptr){
        return length;
    }else if(head == tail){
        length = 1;
        return length;
    }else{
        Node* curr = head;
        while(curr){
            ++length;
            curr = curr->next;
        }
        return length;
    }
}

ListCtr::Node *ListCtr::split(Node *h, int i)
{
    Node* ptrNull = h;

    for(int j = 1;j < i && ptrNull != nullptr;++j){
        ptrNull = ptrNull->next;
    }
    if(ptrNull == nullptr) return nullptr;

    Node* rHead = ptrNull->next;
    ptrNull->next = nullptr; //如果 ptrNull == nullptr：空指针风险

    return rHead;
}

ListCtr::Node *ListCtr::merge(Node *leftHead, Node *rightHead)
{
    Node dummy(0);
    Node* end = &dummy;

    while(leftHead && rightHead){
        if(leftHead->val < rightHead->val){
            end->next = leftHead;
            leftHead = leftHead->next;
        }else{
            end->next = rightHead;
            rightHead = rightHead->next;
        }
        end = end->next;
    }
    if(leftHead){
        end->next = leftHead;
    }else{
        end->next = rightHead;
    }
    return dummy.next;
}
