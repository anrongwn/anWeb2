#include "anwebview.h"
#include "anwebpage.h"
#include "anjscommcontext.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QMouseEvent>

anWebView::anWebView(QWidget *parent) : QWebEngineView(parent)
{
    QObject::connect(this, &QWebEngineView::loadFinished, this, &anWebView::onloadFinished);
    QObject::connect(this, &QWebEngineView::renderProcessTerminated, this, &anWebView::onrenderProcessTerminated);

    //
    this->settings()->setAttribute(QWebEngineSettings::ShowScrollBars, false);
    this->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    this->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->setContextMenuPolicy(Qt::NoContextMenu);
    //this->setAttribute(Qt::WA_TransparentForMouseEvents, true);


    initPage(QStringList());

    //this->grabMouse();
}

anWebView::~anWebView()
{

}

QWebEnginePage *anWebView::initPage(const QStringList &jslist)
{
    QWebEngineProfile *profile = anWebPage::createWebEngineProfile(jslist);
    anWebPage * page = new anWebPage(profile, this);
    /*
    anWebPage * page = new anWebPage(profile, nullptr);
    */

    anJsCommContext * context = new anJsCommContext(qobject_cast<QObject *>(page));
    QObject::connect(context, &anJsCommContext::handler, this, &anWebView::onhandler);
    page->registerCommObject("context", context);
    this->setPage(page);

    return page;
}

void anWebView::changePage(const QString &pagefile, const QString &jsfile)
{
    QString urlName(R"(D:\MyTest\2019_Qt\anWeb2\page\)");
    urlName+=pagefile;
    QUrl url = QUrl::fromUserInput(urlName);
    page()->load(url);
}

void anWebView::mainpage(const QString &pagefile, const QString &jsfile)
{
    /*//
    if (this->page()){
        this->page()->deleteLater();
    }
    */

    QStringList jslist;
    //jslist.append(QString("mainmenu.js"));
    jslist.append(jsfile);

    QWebEngineProfile *profile = anWebPage::createWebEngineProfile(jslist);
    anWebPage * page = new anWebPage(profile, this);
    /*
    anWebPage * page = new anWebPage(profile, nullptr);
    */

    anJsCommContext * context = new anJsCommContext(qobject_cast<QObject *>(page));
    QObject::connect(context, &anJsCommContext::handler, this, &anWebView::onhandler);
    page->registerCommObject("context", context);
    this->setPage(page);

    //QString urlName("D:\\MyTest\\2019_Qt\\anWeb2\\page\\index.html");
    QString urlName(R"(D:\MyTest\2019_Qt\anWeb2\page\)");
    urlName+=pagefile;
    QUrl url = QUrl::fromUserInput(urlName);
    page->load(url);

}

void anWebView::query(const QString &pagefile, const QString &jsfile)
{
    QStringList jslist;
    //jslist.append(QString("mainmenu.js"));
    jslist.append(jsfile);

    QWebEngineProfile *profile = anWebPage::createWebEngineProfile(jslist);
    anWebPage * page = new anWebPage(profile, this);

    anJsCommContext * context = new anJsCommContext(qobject_cast<QObject *>(page));
    QObject::connect(context, &anJsCommContext::handler, this, &anWebView::onhandler);
    page->registerCommObject("context", context);
    this->setPage(page);

    //QString urlName("D:\\MyTest\\2019_Qt\\anWeb2\\page\\index.html");
    QString urlName(R"(D:\MyTest\2019_Qt\anWeb2\page\)");
    urlName+=pagefile;
    QUrl url = QUrl::fromUserInput(urlName);
    page->load(url);
}

void anWebView::withdrawal(const QString &pagefile, const QString &jsfile)
{
    QStringList jslist;
    //jslist.append(QString("mainmenu.js"));
    jslist.append(jsfile);

    QWebEngineProfile *profile = anWebPage::createWebEngineProfile(jslist);
    anWebPage * page = new anWebPage(profile, this);

    anJsCommContext * context = new anJsCommContext(qobject_cast<QObject *>(page));
    QObject::connect(context, &anJsCommContext::handler, this, &anWebView::onhandler);
    page->registerCommObject("context", context);
    this->setPage(page);

    //QString urlName("D:\\MyTest\\2019_Qt\\anWeb2\\page\\index.html");
    QString urlName(R"(D:\MyTest\2019_Qt\anWeb2\page\)");
    urlName+=pagefile;
    QUrl url = QUrl::fromUserInput(urlName);
    page->load(url);
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

void anWebView::onhandler(const QJsonObject &param)
{
    qDebug() << "===" <<QTime::currentTime().toString("hh:mm:ss.zzz")<<"anWebView::onhandler("<<param<<")";

    if (param.isEmpty()) return;

    QJsonValue id = param.value(QString("id"));
    QString vl = id.toString();
    //if (vl.compare())

    /*//多webpage
    mainpage(param.value("page").toString(), param.value("js").toString());
    */

    //单webpage
    changePage(param.value("page").toString(), param.value("js").toString());

}

QWebEngineView *anWebView::createWindow(QWebEnginePage::WebWindowType type)
{
    Q_UNUSED(type);

    return this;
}

void anWebView::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() << "===" <<QTime::currentTime().toString("hh:mm:ss.zzz")<<"anWebView::mouseDoubleClickEvent("<<event<<")";
    event->ignore();
}
