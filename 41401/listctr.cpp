#include "listctr.h"

//static不属于类本身，无需使用成员函数，纯算法函数（只有输入、输出）
static std::unique_ptr<ListCtr::Node> reverseList(std::unique_ptr<ListCtr::Node> head){
    //curr 和 prev 是“状态变量”
    std::unique_ptr<ListCtr::Node> prev = nullptr;
    std::unique_ptr<ListCtr::Node> curr = std::move(head);

    /*
     * ***********操作****************成本*******
       ** 创建 unique_ptr 变量  *  极低（栈上）  **
       **   move unique_ptr	   *    O(1)     **
       **     new Node	       *  真正的成本   **
       ****************************************
     */

    while(curr){
        // next 是一次性的“临时快照”，每个 curr 的 next 都不同
        std::unique_ptr<ListCtr::Node> next = std::move(curr->next);
        curr->next = std::move(prev);
        prev = std::move(curr);
        curr = std::move(next);
    }

    return prev;
}

QString ListCtr::formatList(const std::unique_ptr<Node> &head) const{
    QStringList parts;
    const Node *curr = head.get();

    while(curr){
        parts << QString::number(curr->val);//把数字（整数/浮点数）转换成 QString 字符串
        curr = curr->next.get();
    }

    if(parts.isEmpty()){
        return QStringLiteral("NULL");
    }else{
        return parts.join(QStringLiteral("->"))+QStringLiteral("->NULL");
    }
}

ListCtr::ListCtr(QObject *parent)
    : QObject(parent)
{
    m_head = std::make_unique<Node>(1);
    m_head->next = std::make_unique<Node>(2);
    m_head->next->next = std::make_unique<Node>(3);
    m_head->next->next->next = std::make_unique<Node>(4);
    m_originalDisplay = formatList(m_head);
    m_reversedDisplay = QStringLiteral("（尚未反转）");
}

void ListCtr::reverse(){
    m_head = reverseList(std::move(m_head));
    m_reversedDisplay = formatList(m_head);
    emit reversedDisplayChanged();
}
