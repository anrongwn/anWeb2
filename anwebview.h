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

    QWebEnginePage* initPage(const QStringList &jslist);
    void changePage(const QString &pagefile, const QString &jsfile);
    void mainpage(const QString &pagefile, const QString &jsfile);
    void query(const QString &pagefile, const QString &jsfile);
    void withdrawal(const QString &pagefile, const QString &jsfile);

public slots:
    void onlinkHovered(const QString &url);
    void requestLoadPage(const QUrl &url);
    void onloadFinished(bool ok);
    void onrenderProcessTerminated(QWebEnginePage::RenderProcessTerminationStatus terminationStatus, int exitCode);
    void onhandler(const QJsonObject& param);

protected:
    QWebEngineView * createWindow(QWebEnginePage::WebWindowType type);

    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif // ANWEBVIEW_H

