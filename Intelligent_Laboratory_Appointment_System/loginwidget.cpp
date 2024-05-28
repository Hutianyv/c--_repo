#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QMessageBox>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    // 连接按钮点击信号到槽函数
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWidget::onLoginButtonClicked);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::onLoginButtonClicked()
{
    QString username = ui->usernameLineEdit->text();  // 确保.ui文件中设置了对象名称
    QString password = ui->passwordLineEdit->text();  // 确保.ui文件中设置了对象名称

    if (username == "admin" && password == "password") {
        emit loginSuccessful();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password");
    }
}
