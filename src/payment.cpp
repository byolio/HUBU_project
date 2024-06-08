#include "payment.h"
#include "ui_payment.h"
#include<QString>
Payment::Payment(QWidget *parent, double price)
    : QWidget(parent)
    , ui(new Ui::Payment)
{
    ui->setupUi(this);
    // 设置界面
    this->setFixedSize(505, 390);
    this->setWindowModality(Qt::ApplicationModal);
    // 设置count大小
    ui->count->setFixedSize(QSize(60, 100));
    int psz = QString::number(price).size();
    if(psz == 1)
    {
        ui->count->move(238, 120);
    }
    else if(psz == 2 || psz == 3)
    {
        ui->count->move(234, 120);
    }
    else if(psz == 4)
    {
        ui->count->move(230, 120);
    }
    ui->count->setText(QString("%1").arg(price));
    // 设置支付按键
    ui->payBtn->setFixedSize(95, 150);
    ui->payBtn->setIconSize(QSize(ui->payBtn->width(), ui->payBtn->height()));
    ui->payBtn->setStyleSheet("QPushButton { border: 0px;}");

}
void Payment::paintEvent(QPaintEvent* )
{
    QPainter painter(this);
    QPixmap pix(":/img/countBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}

Payment::~Payment()
{
    delete ui;
}
