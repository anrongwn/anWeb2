#ifndef ANWEBVIEW_H
#define ANWEBVIEW_H

#include <QObject>
#include <QWebEngineView>
#include <QWebEngineSettings>

class anWebView : public QWebEngineView
{
    Q_OBJECT
public:
    explicit anWebView(QWidget *parent = Q_NULLPTR);
    ~anWebView();

public slots:
    void onlinkHovered(const QString &url);
    void requestLoadPage(const QUrl &url);
    void onloadFinished(bool ok);

protected:
    QWebEngineView * createWindow(QWebEnginePage::WebWindowType type);
};

#endif // ANWEBVIEW_H

