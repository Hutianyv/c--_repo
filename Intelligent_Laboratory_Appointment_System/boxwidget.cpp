#include "boxwidget.h"
#include <QPainter>
#include <QMouseEvent>

BoxWidget::BoxWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(50, 50);  // 设置每个块的固定大小
}

void BoxWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::blue);  // 设置填充颜色
    painter.drawRect(0, 0, width(), height());  // 绘制矩形块
}

void BoxWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }
}
