#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pWebView_(nullptr)
{
    ui->setupUi(this);

    initWebView();

    //增加获取按键能力
    this->grabKeyboard();
    //this->grabMouse();


    oldflags_=windowFlags();
    oldsize_=size();

    //installEventFilter(this);
}

MainWindow::~MainWindow()
{
    if(pWebView_){
        pWebView_->deleteLater();
    }

    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    if(pWebView_){
        pWebView_->resize(this->size());
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{


    switch (event->key())
    {
    case Qt::Key_Escape:
        /*
        setWindowFlags(oldflags_);
        showNormal();
        */
        this->close();//关闭
        break;
    case Qt::Key_F11:
        /*
        setWindowFlags(Qt::WindowStaysOnTopHint);//置顶
        showFullScreen();   //全屏
        */
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    event->ignore();
    //event->accept();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if ((watched==pWebView_)&&(event->type() == QEvent::MouseButtonDblClick)){
        qDebug()<<"==="<< QTime::currentTime().toString("hh:mm:ss.zzz")<<"anWebPage::eventFilter QEvent::MouseButtonDblClick";
        return true;
    }

    return QWidget::eventFilter(watched, event);
}

anWebView *MainWindow::initWebView()
{
    if (nullptr==pWebView_){
        pWebView_ = new anWebView(this);
    }

    /*//多webpage
    pWebView_->mainpage("index.html", "mainmenu.js");
    */

    //单webpage
    pWebView_->changePage("index.html", "mainmenu.js");

    /*
    QString urlName("D:\\MyTest\\2019_Qt\\anWeb2\\page\\index.html");
    QUrl url = QUrl::fromUserInput(urlName);
    pWebView_->load(url);
    */

    pWebView_->showFullScreen();
    return pWebView_;
}
