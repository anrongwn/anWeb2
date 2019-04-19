#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QDebug>

int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
    QTextCodec *systemCodec = QTextCodec::codecForLocale();
    qDebug() << "===systemCodec.naem = " << systemCodec->name();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

    //初始应用对象
    QApplication a(argc, argv);

    //修改 QtWebEngineProcess.exe 进程名为 anrongWeb.exe
#ifdef _DEBUG
    QString webengingProcessPath = QCoreApplication::applicationDirPath() + "/" + "anrongWebd.exe";
#else
    QString webengingProcessPath = QCoreApplication::applicationDirPath() + "/" + "anrongWeb.exe";
#endif
    qputenv("QTWEBENGINEPROCESS_PATH", webengingProcessPath.toLocal8Bit());

    /*
    //增加 单进程模式 环境变量
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", QString("--single-process ").toLocal8Bit());
    */

    //初始化主窗口
    MainWindow w;
    w.show();

    return a.exec();
}
