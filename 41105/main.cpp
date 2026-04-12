#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <memory>
#include <iostream>
#include <QDebug>

using namespace std;

struct Node{
    int val;
    //链表内部用 std::unique_ptr<Node> next 管理所有权
    //优点：删除头节点，整个链表自动销毁，完美防止内存泄漏
    //缺点：反转结点容易翻车————由于 unique_ptr 独占所有权，必须时刻用 std::move 转移所有权，代码会变得很“重”
    std::unique_ptr<Node> next;

    Node(int v):val(v),next(nullptr){}
};

//操作时用裸指针（Node*）来做遍历和反转，不动所有权。这样既保证自动释放，又保持操作灵活
std::unique_ptr<Node> reverseList(std::unique_ptr<Node> head){
    //三指针迭代算法，时间复杂度O(1)
    std::unique_ptr<Node> prev = nullptr;
    std::unique_ptr<Node> curr = std::move(head);

    while(curr){
        std::unique_ptr<Node> next = std::move(curr->next);
        curr->next = std::move(prev); //断链重连(箭头)
        prev = std::move(curr);
        curr = std::move(next);
    }
    return prev;
    // C++ 的一个自动优化规则：当函数返回一个局部智能指针（如 prev）时，编译器会自动隐式std::move
    // 等号左边值显示，等号右边值隐式
}

void printList(const std::unique_ptr<Node>& head){ //1.const————只读不修改承诺 // 2.引用传递————不转移所有权
    const Node* curr = head.get(); //1.只读裸指针 //2.get()取出智能指针里封装的Node*，即同类变量
    while(curr){
        qDebug() << curr->val << "->";
        curr = curr->next.get();  //通过 get() 取下一节点的裸指针
    }
    qDebug()<< "null";
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    std::unique_ptr<Node> head = std::make_unique<Node>(1);
    head->next = std::make_unique<Node>(2);
    head->next->next = std::make_unique<Node>(3);
    head->next->next->next = std::make_unique<Node>(4);

    qDebug() << "原链表：";
    printList(head);

    //任何需要交出 unique_ptr 所有权的场合，必须显式使用 std::move
    head = reverseList(std::move(head));
    /*执行前： head 指向 原链表
                   |
                   v
           head = reverseList(std::move(head));
                                 |
                                 v
                        head 交出所有权，变成空
                                 |
                                 v
                        reverseList 内部得到 原链表 所有权，一顿操作后返回 反转链表 所有权
                                 |
                                 v
                    head 重新指向 新链表 ，即 反转链表
            */

    qDebug() << "反转后：";
    printList(head);

    return app.exec();
}
