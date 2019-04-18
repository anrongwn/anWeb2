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

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
