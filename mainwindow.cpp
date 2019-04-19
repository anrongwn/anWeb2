#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pWebView_(nullptr)
{
    ui->setupUi(this);

    initWebView();
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

anWebView *MainWindow::initWebView()
{
    if (nullptr==pWebView_){
        pWebView_ = new anWebView(this);
    }

    pWebView_->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    pWebView_->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);

    pWebView_->setAttribute(Qt::WA_DeleteOnClose, true);
    pWebView_->setContextMenuPolicy(Qt::NoContextMenu);

    pWebView_->init();

    /*
    QString urlName("D:\\MyTest\\2019_Qt\\anWeb2\\page\\index.html");
    QUrl url = QUrl::fromUserInput(urlName);
    pWebView_->load(url);
    */

    pWebView_->showFullScreen();
    return pWebView_;
}
