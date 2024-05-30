#include "smallwindow.h"
#include "ui_smallwindow.h"

SmallWindow::SmallWindow(int boxId, bool isMalfunction, const QString &reservedBy, const QString &timeSlot, const QString &username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmallWindow),
    boxId(boxId),
    isMalfunction(isMalfunction),
    currentUsername(username),
    reservedBy(reservedBy),
    timeSlot(timeSlot)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

    actionButton = ui->actionButton;
    timeSlotComboBox = ui->timeSlotComboBox;
    reservationInfoLabel = ui->reservationInfoLabel;

    if (currentUsername == "admin") {
        // 根据 box 的状态设置按钮文本
        actionButton->setText(isMalfunction ? "故障已解决" : "设置为故障");
        timeSlotComboBox->hide();
        reservationInfoLabel->setText("预约者: " + reservedBy + "\n时间段: " + timeSlot);
    } else {
        if(reservedBy == currentUsername){
            actionButton->setText("取消预约");
        } else{
            actionButton->setText("预约");
            QDate currentDate = QDate::currentDate();
            QStringList timeSlots;
            for (int hour = 8; hour <= 17; ++hour) {
                QTime startTime(hour, 0, 0);  // 每小时的开始时间
                QTime endTime(hour + 1, 0, 0);  // 每小时的结束时间
                QDateTime startDateTime(currentDate, startTime);
                QDateTime endDateTime(currentDate, endTime);

                // 将时间段格式化为 "yyyy-MM-dd HH:mm:ss" 的格式并添加到列表
                QString timeSlot = startDateTime.toString("yyyy-MM-dd HH:mm:ss") + " - " + endDateTime.toString("yyyy-MM-dd HH:mm:ss");
                timeSlots << timeSlot;
            }
             timeSlotComboBox->addItems(timeSlots);
            //timeSlotComboBox->addItems({"08:00-10:00", "10:00-12:00", "14:00-16:00", "16:00-18:00"});
        }

        reservationInfoLabel->hide();
    }

    connect(actionButton, &QPushButton::clicked, this, &SmallWindow::on_actionButton_clicked);
}

SmallWindow::~SmallWindow()
{
    delete ui;
}

void SmallWindow::on_actionButton_clicked()
{
    if (currentUsername == "admin") {
        emit changeBoxState(boxId, !isMalfunction);
    } else {
        if(reservedBy == currentUsername) {
            emit cancelReservation(boxId);
        } else{
            QString selectedTimeSlot = timeSlotComboBox->currentText();
            emit reserveBox(boxId, selectedTimeSlot);}

    }
    close(); // 点击按钮后关闭小窗
}
