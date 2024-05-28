#ifndef BOXWIDGET_H
#define BOXWIDGET_H

#include <QWidget>

class BoxWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoxWidget(QWidget *parent = nullptr);

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // BOXWIDGET_H
