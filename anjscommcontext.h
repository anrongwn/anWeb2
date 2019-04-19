#ifndef ANJSCOMMCONTEXT_H
#define ANJSCOMMCONTEXT_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QJsonObject>

class anJsCommContext : public QObject
{
    Q_OBJECT
public:
    explicit anJsCommContext(QObject *parent = nullptr);
    virtual ~anJsCommContext();

signals:
    void handler(const QJsonObject& param);

public slots:
    virtual void caller(const QJsonObject& param);

};

#endif // ANJSCOMMCONTEXT_H
