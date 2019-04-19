#include "anwebpage.h"
#include <QDebug>
#include <QEventLoop>
#include "anjscommcontext.h"

anWebPage::anWebPage(const QString& page, const QString& js, QObject *parent):\
    QWebEnginePage(parent),
    page_(page), js_(js)
{

}

anWebPage::~anWebPage()
{

}

void anWebPage::registerCommObject(const QString &objId, anJsCommContext *obj)
{
    QWebChannel * channel = new QWebChannel(this);
    channel->registerObject(objId, obj);
    setWebChannel(channel);

    QObject::connect(obj, &anJsCommContext::handler, this, &anWebPage::onhandler);

}

QVariant anWebPage::syncRunJs(const QString &js)
{
    //同步
    QEventLoop loop;
    QObject::connect(this, &anWebPage::jsCompleted, &loop, &QEventLoop::quit);

    QVariant result;
    this->runJavaScript(js, [&](const QVariant &v){

        result = std::move(v);
        emit jsCompleted();

        qDebug()<< "===" << QTime::currentTime().toString("hh:mm:ss.zzz")<<" runJavaScript result: " << result;

    });

    //必须调用，否则无法及时唤醒事件处理，导致runJavaScript回调延时。
    loop.wakeUp();

    loop.exec(QEventLoop::AllEvents);

    qDebug()<<"==="<< QTime::currentTime().toString("hh:mm:ss.zzz")<<" syncRunJs, loop.exec() exit.";

    //c++11 move constructs
    return std::move(result);
}

void anWebPage::onloadFinished(bool ok)
{
    Q_UNUSED(ok);

   qDebug() << "===" <<QTime::currentTime().toString("hh:mm:ss.zzz")<<"anWebPage::onloadFinished("<<ok<<")";
}

void anWebPage::onrenderProcessTerminated(QWebEnginePage::RenderProcessTerminationStatus terminationStatus, int exitCode)
{
    qDebug() << "===" <<QTime::currentTime().toString("hh:mm:ss.zzz")<<\
                "anWebPage::onrenderProcessTerminated("<<terminationStatus<<"," << exitCode<<")";
}

void anWebPage::onhandler(const QJsonObject &param)
{

}
