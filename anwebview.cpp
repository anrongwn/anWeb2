#include "anwebview.h"

anWebView::anWebView(QWidget *parent) : QWebEngineView(parent)
{
    QObject::connect(this, &QWebEngineView::loadFinished, this, &anWebView::onloadFinished);
    QObject::connect(this, &QWebEngineView::renderProcessTerminated, this, &anWebView::onrenderProcessTerminated);

}

anWebView::~anWebView()
{

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
