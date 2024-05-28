#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "loginwidget.h"
#include "mainwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showMainWidget();

private:
    LoginWidget *loginWidget;
    MainWidget *mainWidget;
    QStackedWidget *stackedWidget;
};

#endif // MAINWINDOW_H
