#include "anwebview.h"
#include "anwebpage.h"
#include "anjscommcontext.h"

anWebView::anWebView(QWidget *parent) : QWebEngineView(parent)
{
    QObject::connect(this, &QWebEngineView::loadFinished, this, &anWebView::onloadFinished);
    QObject::connect(this, &QWebEngineView::renderProcessTerminated, this, &anWebView::onrenderProcessTerminated);

}

anWebView::~anWebView()
{

}

void anWebView::init()
{
    QStringList jslist;
    jslist.append(QString("mainmenu.js"));


    QWebEngineProfile *profile = anWebPage::createWebEngineProfile(jslist);
    anWebPage * mainpage = new anWebPage(profile, this);

    anJsCommContext * context = new anJsCommContext(qobject_cast<QObject *>(mainpage));
    mainpage->registerCommObject("context", context);
    this->setPage(mainpage);

    QString urlName("D:\\MyTest\\2019_Qt\\anWeb2\\page\\index.html");
    QUrl url = QUrl::fromUserInput(urlName);
    mainpage->load(url);

}

void anWebView::onlinkHovered(const QString &url)
{
    Q_UNUSED(url);
}

void anWebView::requestLoadPage(const QUrl &url)
{
     Q_UNUSED(url);
}

void anWebView::onloadFinished(bool ok)
{
     Q_UNUSED(ok);

    qDebug() << "===" <<QTime::currentTime().toString("hh:mm:ss.zzz")<<"anWebView::onloadFinished("<<ok<<")";
}

void anWebView::onrenderProcessTerminated(QWebEnginePage::RenderProcessTerminationStatus terminationStatus, int exitCode)
{
    qDebug() << "===" <<QTime::currentTime().toString("hh:mm:ss.zzz")<<\
                "anWebView::onrenderProcessTerminated("<<terminationStatus<<"," << exitCode<<")";
}

QWebEngineView *anWebView::createWindow(QWebEnginePage::WebWindowType type)
{
    Q_UNUSED(type);

    return this;
}
