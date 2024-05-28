#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    gridLayout = new QGridLayout();  // 创建新的网格布局

    // 创建40个BoxWidget并添加到网格布局中
    for (int i = 0; i < 40; ++i) {
        int row = i / 8;  // 每行8个块
        int col = i % 8;
        BoxWidget *box = new BoxWidget(this);
        gridLayout->addWidget(box, row, col);
        connect(box, &BoxWidget::clicked, this, &MainWidget::handleBoxClicked);
    }

    ui->gridLayoutContainer->setLayout(gridLayout);  // 将gridLayout设置为容器布局
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::handleBoxClicked()
{
    QMessageBox::information(this, "Box Clicked", "A box was clicked!");
}

