#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "anwebview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void resizeEvent(QResizeEvent *event);

private:
    anWebView * initWebView();

private:
    Ui::MainWindow *ui;

    anWebView * pWebView_;
};

#endif // MAINWINDOW_H
