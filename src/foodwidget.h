#ifndef FOODWIDGET_H
#define FOODWIDGET_H

#include<QPaintEvent>
#include <QWidget>
#include<QString>
namespace Ui {
class FoodWidget;
}

class FoodWidget : public QWidget
{
    Q_OBJECT

public:
    //explicit FoodWidget(QWidget *parent = nullptr);
    FoodWidget(double price = 0.0, QString imgPath = "", double x = 0.0, double y = 0.0);
    ~FoodWidget();
    void paintEvent(QPaintEvent *) override;
    // 按键弹跳曲线
    void zoomDown();
    void zoomUp();
signals:
    void foodPrice(double price);

private:
    double food_price;
    QString imagePath;
    double posX;
    double posY;
    Ui::FoodWidget *ui;
    // 按键是否已经被点击
    bool isClick;
};

#endif // FOODWIDGET_H
