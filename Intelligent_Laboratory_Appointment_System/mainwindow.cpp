#include "mainwindow.h"
#include <QApplication>
#include <QLineEdit>
#include <QIcon>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    loginWidget(new LoginWidget(this)),
    mainWidget(new MainWidget(this)),
    stackedWidget(new QStackedWidget(this))
{
    stackedWidget->addWidget(loginWidget);
    stackedWidget->addWidget(mainWidget);
    setCentralWidget(stackedWidget);

    connect(loginWidget, &LoginWidget::loginButtonClicked, this, &MainWindow::showMainWidget);

    resize(800, 600);  // 设置窗口大小
    setWindowIcon(QIcon(":/library.jpg"));  // 使用资源文件中的图标
}

MainWindow::~MainWindow()
{
}

void MainWindow::showMainWidget()
{
    // 获取登录用户名
    QLineEdit *usernameLineEdit = loginWidget->findChild<QLineEdit*>("usernameLineEdit");
    QLineEdit *passwordLineEdit = loginWidget->findChild<QLineEdit*>("passwordLineEdit");
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    if ((username == "admin" && password == "password") || (username == "B23040523" && password == "password")) {
        mainWidget->setLabelText(username);
        stackedWidget->setCurrentWidget(mainWidget);
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password");
    }
}
