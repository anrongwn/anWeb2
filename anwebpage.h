#ifndef ANWEBPAGE_H
#define ANWEBPAGE_H

#include <QObject>
#include <QWebEnginePage>
#include <QWebChannel>
#include <QWebEngineProfile>
#include <QStringList>
#include <QString>


class anJsCommContext;
class anWebPage : public QWebEnginePage
{
    Q_OBJECT
public:
    anWebPage(QObject *parent = Q_NULLPTR)=delete;
    anWebPage(QWebEngineProfile *profile, QObject *parent = Q_NULLPTR);
    ~anWebPage();

    void registerCommObject(const QString& objId, anJsCommContext *obj);
    virtual QVariant syncRunJs(const QString& js);

    static QWebEngineProfile* createWebEngineProfile(const QStringList& jslist, QObject *parent=nullptr);

    QString injectedJSrcipt(const QString &fn);
    QString injectedJSrcipt2(const QString &fn);

signals:
    void jsCompleted();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;


    void javaScriptConsoleMessage(QWebEnginePage::JavaScriptConsoleMessageLevel level, \
                                          const QString &message, int lineNumber, const QString &sourceID) override;


public slots:
    void onloadStarted();
    void onloadFinished(bool ok);
    void onrenderProcessTerminated(QWebEnginePage::RenderProcessTerminationStatus terminationStatus, int exitCode);
    virtual void onhandler(const QJsonObject& param);
    void triggerAction(QWebEnginePage::WebAction action, bool checked = false) override;

};

#endif // ANWEBPAGE_H
