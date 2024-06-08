#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"foodwidget.h"
#include<QPainter>
#include<QPixmap>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //主窗口设置
    this->setFixedSize(505, 490);
    this->setWindowIcon(QIcon(":/img/windowIcon.png"));
    this->setWindowTitle("dinner system");
    // 总价格
    curVal = 0.0;
    // 按键icon去除边界
    ui->homeBtn->setStyleSheet("QToolButton { border: 0px;}");
    ui->dinnerBtn->setStyleSheet("QToolButton { border: 0px;}");
    ui->mineBtn->setStyleSheet("QToolButton { border: 0px;}");
    ui->orderBtn->setStyleSheet("QToolButton { border: 0px;}");
    ui->dessertBtn->setStyleSheet("QToolButton { border: 0px;}");
    ui->drinkBtn->setStyleSheet("QToolButton { border: 0px;}");
    ui->mainCourseBtn->setStyleSheet("QToolButton { border: 0px;}");
    // 设置搜索界面图片
    QPixmap pixmap(":/img/search.png");
    pixmap = pixmap.scaled(QSize(25, 25));
    ui->searchlabel->setPixmap(pixmap);
    ui->searchlabel->setAlignment(Qt::AlignCenter);
    //建立菜单
    countMainCourse = 2;  // 建立菜单数
    countDessert = 1;
    countDrink = 1;
    mainCourseArr = new FoodWidget*[countMainCourse];
    dessertArr = new FoodWidget*[countDessert];
    drinkArr = new FoodWidget*[countDrink];
    // 设置主菜单
    mainCourseArr[0] = new FoodWidget(8.8, ":/img/shrimpPrice.png");
    mainCourseArr[0]->setParent(ui->foodWid);
    mainCourseArr[1] = new FoodWidget(13.0, ":/img/chickenPrice.png", 0.0, 100.0);
    mainCourseArr[1]->setParent(ui->foodWid);

    // 设置dessert菜单
    dessertArr[0] = new FoodWidget(8.8, ":/img/cakePrice.png");
    dessertArr[0]->setParent(ui->foodWid);
    for(int i = 0; i < countDessert; ++i)
    {
        dessertArr[0]->hide();
    }

    // 设置drink菜单
    drinkArr[0] = new FoodWidget(2.0, ":/img/cacaPrice.png");
    drinkArr[0]->setParent(ui->foodWid);
    for(int i = 0; i < countDrink; ++i)
    {
        drinkArr[0]->hide();
    }

    // mainCourse按键切换
    connect(ui->mainCourseBtn, &QToolButton::clicked, this, [=](){
        for(int i = 0; i < countMainCourse; ++i)
        {
            if(mainCourseArr[i]->isHidden())
            {
                mainCourseArr[i]->show();
            }
        }
        for(int i = 0; i < countDrink; ++i)
        {
            if(!drinkArr[i]->isHidden())
            {
                drinkArr[i]->hide();
            }
        }
        for(int i = 0; i < countDessert; ++i)
        {
            if(!dessertArr[i]->isHidden())
            {
                dessertArr[i]->hide();
            }
        }
    });

    // drink按键切换
    connect(ui->drinkBtn, &QToolButton::clicked, this, [=](){
        for(int i = 0; i < countMainCourse; ++i)
        {
            if(!mainCourseArr[i]->isHidden())
            {
                mainCourseArr[i]->hide();
            }
        }
        for(int i = 0; i < countDrink; ++i)
        {
            if(drinkArr[i]->isHidden())
            {
                drinkArr[i]->show();
            }
        }
        for(int i = 0; i < countDessert; ++i)
        {
            if(!dessertArr[i]->isHidden())
            {
                dessertArr[i]->hide();
            }
        }
    });

    // dessert按键切换
    connect(ui->dessertBtn, &QToolButton::clicked, this, [=](){
        for(int i = 0; i < countMainCourse; ++i)
        {
            if(!mainCourseArr[i]->isHidden())
            {
                mainCourseArr[i]->hide();
            }
        }
        for(int i = 0; i < countDrink; ++i)
        {
            if(!drinkArr[i]->isHidden())
            {
                drinkArr[i]->hide();
            }
        }
        for(int i = 0; i < countDessert; ++i)
        {
            if(dessertArr[i]->isHidden())
            {
                dessertArr[i]->show();
            }
        }
    });

    // 接收价格信号
    for(int i = 0; i < countMainCourse; ++i)
    {
        connect(mainCourseArr[i], &FoodWidget::foodPrice, this, [=](double price){
            curVal += price;
            ui->totalMoney->setText(QString("%1").arg(curVal));
        });
    }
    for(int i = 0; i < countDessert; ++i)
    {
        connect(dessertArr[i], &FoodWidget::foodPrice, this, [=](double price){
            curVal += price;
            ui->totalMoney->setText(QString("%1").arg(curVal));
        });
    }
    for(int i = 0; i < countDrink; ++i)
    {
        connect(drinkArr[i], &FoodWidget::foodPrice, this, [=](double price){
            curVal += price;
            ui->totalMoney->setText(QString("%1").arg(curVal));
        });
    }
    // 链接支付按钮和界面
    connect(ui->countBtn, &QPushButton::clicked, this, [=](){
        // 支付界面的设置
        Payment* pay = new Payment(this, curVal);
        pay->move(0, this->height() - 390);
        pay->show();
    });
}

//设置初始背景图片
void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap startScene;
    startScene.load(":/img/mainBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), startScene);
}
MainWindow::~MainWindow()
{
    delete ui;
}
