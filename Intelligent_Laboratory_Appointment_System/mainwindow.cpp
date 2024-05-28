#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    loginWidget(new LoginWidget(this)),
    mainWidget(new MainWidget(this)),
    stackedWidget(new QStackedWidget(this))
{
    stackedWidget->addWidget(loginWidget);
    stackedWidget->addWidget(mainWidget);

    setCentralWidget(stackedWidget);


    connect(loginWidget, &LoginWidget::loginSuccessful, this, &MainWindow::showMainWidget);
    resize(800, 600);
}

MainWindow::~MainWindow()
{
}

void MainWindow::showMainWidget()
{
    stackedWidget->setCurrentWidget(mainWidget);
}
