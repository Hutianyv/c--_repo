#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QMessageBox>
#include <QScreen>
#include <QDateTime>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVBoxLayout>
#include <QTimer>
#include "boxwidget.h"
#include "smallwindow.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    // 初始化布局
    gridLayout = new QGridLayout(this);

    // 初始化时间标签
    QVBoxLayout *topLayout = new QVBoxLayout;
    topLayout->addWidget(ui->label);
    topLayout->addWidget(ui->dateTimeLabel);
    topLayout->setAlignment(Qt::AlignTop); // 顶部对齐
    gridLayout->addLayout(topLayout, 0, 0, 1, 8, Qt::AlignTop);

    // 创建40个BoxWidget并添加到网格布局中
    for (int i = 0; i < 40; ++i) {
        int row = (i / 8) + 1;  // 每行8个块，从第二行开始
        int col = i % 8;
        BoxWidget *box = new BoxWidget(i, this);
        boxWidgets.insert(i, box);
        gridLayout->addWidget(box, row, col);
        connect(box, &BoxWidget::clicked, this, &MainWidget::handleBoxClicked);
    }

    ui->gridLayoutContainer->setLayout(gridLayout); // 将gridLayout设置为容器布局

    loadState();
    updateDateTime();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWidget::updateDateTime);
    timer->start(1000);
    reservationTimer = new QTimer(this);
    connect(reservationTimer, &QTimer::timeout, this, &MainWidget::checkReservations);
    reservationTimer->start(60000);
    checkReservations();
}

MainWidget::~MainWidget()
{
    saveState();
    delete ui;
}

void MainWidget::setLabelText(const QString &text)
{
    currentUsername = text;
    ui->label->setText(text == "admin" ? "实验室管理系统" : "实验室预约系统");
}

void MainWidget::handleBoxClicked(int id)
{
    BoxWidget *box = boxWidgets.value(id);
    if (box) {
        if (box->getState() == BoxWidget::Malfunction && currentUsername != "admin") {
            QMessageBox::warning(this, "Warning", "This box is malfunctioned and cannot be used.");
            return;
        }

        SmallWindow *smallWindow = new SmallWindow(id, box->getState() == BoxWidget::Malfunction, box->getReservedBy(), box->getTimeSlot(), currentUsername, this);
        connect(smallWindow, &SmallWindow::changeBoxState, this, &MainWidget::changeBoxState);
        connect(smallWindow, &SmallWindow::reserveBox, this, &MainWidget::reserveBoxSlot);
        connect(smallWindow, &SmallWindow::cancelReservation, this, &MainWidget::cancelReservation);
        smallWindow->setWindowModality(Qt::ApplicationModal);
        smallWindow->resize(400, 300);

        QScreen *screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int x = (screenGeometry.width() - smallWindow->width()) / 2;
        int y = (screenGeometry.height() - smallWindow->height()) / 2;
        smallWindow->move(x, y);

        smallWindow->show();
    }
}

void MainWidget::changeBoxState(int id, bool toMalfunction)
{
    BoxWidget *box = boxWidgets.value(id);
    if (box) {
        if (toMalfunction) {
            box->setState(BoxWidget::Malfunction);
            box->clearReservation();
        } else {
            box->setState(BoxWidget::Idle);
        }
        saveState();
    }
}

void MainWidget::reserveBoxSlot(int id, const QString &timeSlot)
{
    BoxWidget *box = boxWidgets.value(id);
    if (box) {
        box->setState(BoxWidget::Reserved);
        box->setReservedBy(currentUsername);
        box->setTimeSlot(timeSlot);
        saveState();
    }
}

void MainWidget::updateDateTime()
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    ui->dateTimeLabel->setText(currentDateTime);
}

void MainWidget::saveState()
{
    QJsonArray boxArray;
    for (BoxWidget *box : boxWidgets) {
        QJsonObject boxObj;
        boxObj["id"] = box->getId();
        boxObj["state"] = box->getState();
        boxObj["reservedBy"] = box->getReservedBy();
        boxObj["timeSlot"] = box->getTimeSlot();
        boxArray.append(boxObj);
    }

    QJsonObject rootObj;
    rootObj["boxes"] = boxArray;

    QJsonDocument doc(rootObj);
    QFile file("state.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void MainWidget::loadState()
{
    QFile file("state.json");
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject rootObj = doc.object();
    QJsonArray boxArray = rootObj["boxes"].toArray();

    for (const QJsonValue &value : boxArray) {
        QJsonObject boxObj = value.toObject();
        int id = boxObj["id"].toInt();
        BoxWidget::State state = static_cast<BoxWidget::State>(boxObj["state"].toInt());
        QString reservedBy = boxObj["reservedBy"].toString();
        QString timeSlot = boxObj["timeSlot"].toString();

        BoxWidget *box = boxWidgets.value(id);
        if (box) {
            box->setState(state);
            box->setReservedBy(reservedBy);
            box->setTimeSlot(timeSlot);
        }
    }
}
void MainWidget::checkReservations() {
    QDateTime currentTime = QDateTime::currentDateTime();
    for (BoxWidget *box : boxWidgets) {
        if (box->getState() == BoxWidget::Reserved) {
            QString timeSlot = box->getTimeSlot();
            QStringList times = timeSlot.split(" - ");
            if (times.size() == 2) {
                QDateTime reservationStartTime = QDateTime::fromString(times[0], "yyyy-MM-dd HH:mm:ss");
                QDateTime reservationEndTime = QDateTime::fromString(times[1], "yyyy-MM-dd HH:mm:ss");
                if (reservationStartTime.isValid() && reservationEndTime.isValid()) {
                    if (currentTime >= reservationStartTime && currentTime < reservationEndTime) {
                        box->setState(BoxWidget::InUse);
                    } else if (currentTime >= reservationEndTime) {
                        box->setState(BoxWidget::Idle);
                        box->setReservedBy("");
                        box->setTimeSlot("");
                    }
                }
            }
        }
    }
    saveState();  // 保存状态
}

void MainWidget::cancelReservation(int id)
{
    BoxWidget *box = boxWidgets.value(id);
    if (box) {
        box->setState(BoxWidget::Idle);
        box->setReservedBy("");
        box->setTimeSlot("");
        saveState();
    }
}
