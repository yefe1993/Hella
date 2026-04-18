#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include "listctr.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //继承自QObject元对象类————创建C++类时 Base class 这里默认是空的，手动选择 QObject
    ListCtr list;
    /*
     * rootContext()————QML全局作用域，需要#include <QQmlContext>
     * setContextProperty()————连接通道，将 C++ 对象，注册到 qml ,在qml里看到的 listShow 是C++对象
     * QStringLiteral()————在编译期就变成QString，避免运行时转换(浪费时间)
     * */
    engine.rootContext()->setContextProperty(QStringLiteral("listShow"),&list);

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

    return app.exec();
}
