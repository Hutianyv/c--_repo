#ifndef SMALLWINDOW_H
#define SMALLWINDOW_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QStringList>

namespace Ui {
class SmallWindow;
}

class SmallWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SmallWindow(int boxId, bool isMalfunction, const QString &reservedBy, const QString &timeSlot, const QString &username, QWidget *parent = nullptr);
    ~SmallWindow();

signals:
    void changeBoxState(int boxId, bool toMalfunction);
    void reserveBox(int boxId, const QString &timeSlot);
    void cancelReservation(int boxId);
private slots:
    void on_actionButton_clicked();

private:
    Ui::SmallWindow *ui;
    int boxId;
    bool isMalfunction;
    QString currentUsername;
    QString reservedBy;
    QString timeSlot;
    QComboBox *timeSlotComboBox;
    QLabel *reservationInfoLabel;
    QPushButton *actionButton;
};

#endif // SMALLWINDOW_H
