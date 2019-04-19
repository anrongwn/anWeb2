#include "anwebpage.h"
#include <QDebug>
#include <QEventLoop>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>
#include <QFile>
#include "anjscommcontext.h"


anWebPage::anWebPage(QWebEngineProfile *profile, QObject *parent) : \
    QWebEnginePage(profile, parent)
{
    profile->setParent(this);
    QObject::connect(this, &QWebEnginePage::loadFinished, this, &anWebPage::onloadFinished);
}

anWebPage::~anWebPage()
{

}

void anWebPage::registerCommObject(const QString &objId, anJsCommContext *obj)
{
    QWebChannel * channel = new QWebChannel(this);
    channel->registerObject(objId, obj);
    setWebChannel(channel);

    QObject::connect(obj, &anJsCommContext::handler, this, &anWebPage::onhandler);

}

QVariant anWebPage::syncRunJs(const QString &js)
{
    //同步
    QEventLoop loop;
    QObject::connect(this, &anWebPage::jsCompleted, &loop, &QEventLoop::quit);

    QVariant result;
    this->runJavaScript(js, QWebEngineScript::MainWorld, [&](const QVariant &v){

        result = std::move(v);
        emit jsCompleted();

        qDebug()<< "===" << QTime::currentTime().toString("hh:mm:ss.zzz")<<" runJavaScript result: " << result;

    });

    //必须调用，否则无法及时唤醒事件处理，导致runJavaScript回调延时。
    loop.wakeUp();

    loop.exec(QEventLoop::AllEvents);

    qDebug()<<"==="<< QTime::currentTime().toString("hh:mm:ss.zzz")<<" syncRunJs, loop.exec() exit.";

    //c++11 move constructs
    return std::move(result);
}

QWebEngineProfile *anWebPage::createWebEngineProfile(const QStringList &jslist, QObject *parent)
{
    QWebEngineProfile * profile = new QWebEngineProfile("anWebProfile", parent);
    QString jsAll;

    //load qwebchannel.js
    QString path(R"(:/js/qwebchannel.js)");
    QFile jsfile(path);
    if (jsfile.open(QIODevice::ReadOnly)){
        jsAll += jsfile.readAll().constData();
    }
    jsfile.close();

    path = QString(R"(:/js/anweb2init.js)");
    QFile jsfile2(path);
    if (jsfile2.open(QIODevice::ReadOnly)){
        jsAll += jsfile2.readAll().constData();
    }
    jsfile2.close();

    /*//
    for(auto js:jslist){
        jsAll+="\r\n";

        QString jsfn(R"(:/js/)");
        jsfn+=js;
        QFile tmp(jsfn);
        if (tmp.open(QIODevice::ReadOnly)){
            jsAll += tmp.readAll().constData();
        }
        tmp.close();
    }
    */

    {
        QWebEngineScript script;
        script.setSourceCode(jsAll);
        script.setName("qwebchannel.js");
        script.setWorldId(QWebEngineScript::MainWorld);
        script.setInjectionPoint(QWebEngineScript::DocumentCreation);
        script.setRunsOnSubFrames(false);
        profile->scripts()->insert(script);
    }

    return profile;
}

QString anWebPage::loadJSrcipt(const QString &fn)
{
    QString js;//("(function(){\r\n");
    js+="var ohead= document.getElementsByTagName('body')[0];\r\nvar oscript= document.createElement('script');\r\noscript.type= 'text/javascript';\r\n";
    js+="oscript.text='";

    QString path(R"(:/js/)");
    path+=fn;
    QFile jsfile(path);
    QString text;
    //text+="var content;function fn(){content=\"hello,wangjr\";/*sdfadf*/;};fn();document.write(content);";
    /*
    text+="var ohead= document.getElementsByTagName('body')[0];var oscript= document.createElement('script');\
        oscript.type= 'text/javascript';oscript.text='var context;\
        function init(){new QWebChannel(qt.webChannelTransport, function(channel){context = channel.objects.context;});\
        document.getElementById(\"bn1\").onclick=onBtnSendMsg;};function onBtnSendMsg(){var cmd = document.getElementById(\"in1\").value;sendMessage(cmd);};\
        function sendMessage(msg){context.onMsg(1, msg);};function recvMessage(msg){var obj = document.getElementById(\"in1\");obj.value=msg;return \"index.html--recvMessage\";};\
        init();';\
        ohead.appendChild(oscript);";
        */


    /*js文件中注释不能用//，字符串使用""，每个语名结束要有;(含}，最后行不能有换行)*/
    if (jsfile.open(QIODevice::ReadOnly)){

        text+= jsfile.readAll().constData();

        text.replace("\r\n", "");
        //qDebug()<< "===loadJS::addScript open" << path << text;
    }
    else{
         qDebug()<< "===loadJS::addScript open" << path << " failed.";
    }


    js+=text;
    js+="';\r\nohead.appendChild(oscript);\r\n";
    //js+="\r\nohead.appendChild(oscript);\r\n";
    //js+=QString("})();\r\n");


    /*
    QFile inf(R"(D:\MyTest\2019_Qt\myWeb1\temp.js)");
    if (inf.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        inf.write(js.toUtf8());
        inf.flush();
        inf.close();
    }
    qDebug()<< "===" << QTime::currentTime().toString("hh:mm:ss.zzz")<<" loadJS::addScript result: " << js;
    */

    return js ;
}

QString anWebPage::loadJSrcipt2(const QString &fn)
{
    QString path(R"(:/js/)");
    path+=fn;
    QFile jsfile(path);
    QString jsAll;

    if (jsfile.open(QIODevice::ReadOnly)){

        jsAll+= jsfile.readAll().constData();
    }
    else{
        qDebug()<< "===loadJS::loadJSrcipt2 open" << path << " failed.";
    }


    QWebEngineScript script;
    script.setSourceCode(jsAll);
    script.setName(fn);
    script.setWorldId(QWebEngineScript::MainWorld);
    script.setInjectionPoint(QWebEngineScript::Deferred);
    script.setRunsOnSubFrames(true);
    profile()->scripts()->insert(script);

    return jsAll;

}

void anWebPage::onloadFinished(bool ok)
{
    Q_UNUSED(ok);

   qDebug() << "===" <<QTime::currentTime().toString("hh:mm:ss.zzz")<<"anWebPage::onloadFinished("<<ok<<")";


   QString js = loadJSrcipt("mainmenu.js");
   syncRunJs(js);


    /*
   loadJSrcipt2("mainmenu.js");
   syncRunJs("init();");
   */


}

void anWebPage::onrenderProcessTerminated(QWebEnginePage::RenderProcessTerminationStatus terminationStatus, int exitCode)
{
    qDebug() << "===" <<QTime::currentTime().toString("hh:mm:ss.zzz")<<\
                "anWebPage::onrenderProcessTerminated("<<terminationStatus<<"," << exitCode<<")";
}

void anWebPage::onhandler(const QJsonObject &param)
{
    qDebug() << "===" <<QTime::currentTime().toString("hh:mm:ss.zzz")<<"anWebPage::onhandler("<<param<<")";
}