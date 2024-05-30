#include "boxwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDateTime>

BoxWidget::BoxWidget(int id, QWidget *parent)
    : QWidget(parent), id(id), currentState(Idle), currentColor(Qt::blue)
{
    setFixedSize(50, 50);
    updateColor();
}

void BoxWidget::setState(State state)
{
    currentState = state;
    updateColor();
    update();
}

BoxWidget::State BoxWidget::getState() const
{
    return currentState;
}

int BoxWidget::getId() const
{
    return id;
}

void BoxWidget::setReservedBy(const QString &username)
{
    reservedBy = username;
}

QString BoxWidget::getReservedBy() const
{
    return reservedBy;
}

void BoxWidget::setTimeSlot(const QString &timeSlot)
{
    this->timeSlot = timeSlot;
}

QString BoxWidget::getTimeSlot() const
{
    return timeSlot;
}
void BoxWidget::checkAndUpdateState()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QDateTime startTime = QDateTime::fromString(timeSlot.split(" - ").first(), "yyyy-MM-dd HH:mm:ss");
    QDateTime endTime = QDateTime::fromString(timeSlot.split(" - ").last(), "yyyy-MM-dd HH:mm:ss");

    if (currentState == Reserved) {
        if (currentTime >= startTime && currentTime <= endTime) {
            setState(InUse);
        } else if (currentTime > endTime) {
            setState(Idle);
            clearReservation();
        }
    } else if (currentState == InUse && currentTime > endTime) {
        setState(Idle);
        clearReservation();
    }
}

void BoxWidget::clearReservation()
{
    reservedBy.clear();
    timeSlot.clear();
}

void BoxWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBrush(currentColor);
    painter.drawRect(0, 0, width(), height());
}

void BoxWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked(id);
    }
}

void BoxWidget::updateColor()
{
    switch (currentState) {
    case Idle:
        currentColor = Qt::blue;
        break;
    case Reserved:
        currentColor = Qt::green;
        break;
    case InUse:
        currentColor = Qt::yellow;
        break;
    case Malfunction:
        currentColor = Qt::red;
        break;
    }
}
