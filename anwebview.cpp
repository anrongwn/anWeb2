#include "anwebview.h"

anWebView::anWebView(QWidget *parent) : QWebEngineView(parent)
{

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
}

QWebEngineView *anWebView::createWindow(QWebEnginePage::WebWindowType type)
{
    Q_UNUSED(type);

    return this;
}
