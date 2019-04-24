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
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    anWebView * initWebView();

private:
    Ui::MainWindow *ui;

    anWebView * pWebView_;

    Qt::WindowFlags oldflags_;
    QSize oldsize_;
};

#endif // MAINWINDOW_H
