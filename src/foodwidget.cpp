#include "foodwidget.h"
#include "ui_foodwidget.h"
#include<QPainter>
#include<QPixmap>
#include<QThread>
#include<QPropertyAnimation>

FoodWidget::FoodWidget(double price, QString imgPath, double x, double y)
    : food_price(price), imagePath(imgPath), posX(x), posY(y),
        ui(new Ui::FoodWidget)
{
    ui->setupUi(this);
    // 设置大小
    this->setFixedSize(QSize(330, 90));
    // 设置位置
    this->move(posX, posY);
    // 设置按键
    ui->chooseBtn->move(250, 50);
    ui->chooseBtn->setIcon(QIcon(":/img/choose.png"));
    ui->chooseBtn->setStyleSheet("QPushButton { border: 0px;}");
    ui->chooseBtn->setIconSize(QSize(ui->chooseBtn->width(), ui->chooseBtn->height()));
    isClick = true;  // 控制多次点击风险

    connect(ui->chooseBtn, &QPushButton::clicked, this, [=](){
        if(this->isClick)
        {
            isClick = false;
            this->zoomDown();
            this->zoomUp();
            emit this->foodPrice(this->food_price);
            isClick = true;
        }
    });
}
// 初始背景
void FoodWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix(imagePath);
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}

void FoodWidget::zoomUp()
{
    //创建动态对象
    QPropertyAnimation* animation = new QPropertyAnimation(ui->chooseBtn, "geometry");
    // geometry 属性为按钮的几何位置和属性大小

    //设置动画时间间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(ui->chooseBtn->x(), ui->chooseBtn->y() + 5, ui->chooseBtn->width(),
                                   ui->chooseBtn->height()));
    // 结束位置
    animation->setEndValue(QRect(ui->chooseBtn->x(), ui->chooseBtn->y(), ui->chooseBtn->width(),
                                 ui->chooseBtn->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void FoodWidget::zoomDown()
{

    QPropertyAnimation* animation = new QPropertyAnimation(ui->chooseBtn, "geometry");
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(ui->chooseBtn->x(), ui->chooseBtn->y(), ui->chooseBtn->width(),
                                   ui->chooseBtn->height()));
    // 结束位置
    animation->setEndValue(QRect(ui->chooseBtn->x(), ui->chooseBtn->y() + 5, ui->chooseBtn->width(),
                                 ui->chooseBtn->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

FoodWidget::~FoodWidget()
{
    delete ui;
}
