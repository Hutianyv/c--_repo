#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QMap>
#include <QVBoxLayout>
#include "boxwidget.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void setLabelText(const QString &text);

private slots:
    void handleBoxClicked(int id);
    void changeBoxState(int id, bool toMalfunction);
    void reserveBoxSlot(int id, const QString &timeSlot);
    void updateDateTime();
    void checkReservations();
    void cancelReservation(int id);

private:
    Ui::MainWidget *ui;
    QGridLayout *gridLayout;
    QMap<int, BoxWidget*> boxWidgets;
    QString currentUsername;
    QTimer *reservationTimer;
    void saveState();
    void loadState();

};

#endif // MAINWIDGET_H
