#ifndef ANWEBPAGE_H
#define ANWEBPAGE_H

#include <QObject>
#include <QWebEnginePage>
#include <QWebChannel>
#include <QString>


class anJsCommContext;
class anWebPage : public QWebEnginePage
{
    Q_OBJECT
public:
    anWebPage(const QString& page, const QString& js, QObject *parent = Q_NULLPTR);
    ~anWebPage();

    void registerCommObject(const QString& objId, anJsCommContext *obj);
    virtual QVariant syncRunJs(const QString& js);

signals:
    void jsCompleted();

public slots:
    void onloadFinished(bool ok);
    void onrenderProcessTerminated(QWebEnginePage::RenderProcessTerminationStatus terminationStatus, int exitCode);
    virtual void onhandler(const QJsonObject& param);

private:
    QString page_;
    QString js_;

};

#endif // ANWEBPAGE_H
