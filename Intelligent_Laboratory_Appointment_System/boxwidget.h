#ifndef BOXWIDGET_H
#define BOXWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class BoxWidget : public QWidget
{
    Q_OBJECT

public:
    enum State {
        Idle,
        Reserved,
        InUse,
        Malfunction
    };

    explicit BoxWidget(int id, QWidget *parent = nullptr);
    void setState(State state);
    State getState() const;
    int getId() const;
    void setReservedBy(const QString &username);
    QString getReservedBy() const;
    void setTimeSlot(const QString &timeSlot);
    QString getTimeSlot() const;
    void clearReservation();
    void checkAndUpdateState();
signals:
    void clicked(int id);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    int id;
    State currentState;
    QColor currentColor;
    QString reservedBy;
    QString timeSlot;
    void updateColor();
};

#endif // BOXWIDGET_H
