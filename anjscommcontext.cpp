#include "anjscommcontext.h"

anJsCommContext::anJsCommContext(QObject *parent) : QObject(parent)
{

}

anJsCommContext::~anJsCommContext()
{

}

void anJsCommContext::caller(const QJsonObject &param)
{
    emit handler(param);
}
