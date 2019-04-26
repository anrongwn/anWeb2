#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QDebug>
#include <array>

template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept{
    return N;
}

int main(int argc, char *argv[])
{
    int na[]={1,3,5,7,9};
    std::array<int, arraySize(na)> ana={1,3,5,7,9};

    //int *p = nullptr;
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
    QTextCodec *localeCodec = QTextCodec::codecForLocale();
    qDebug() << "===LocaleCodec.name = " << localeCodec->name();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

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
