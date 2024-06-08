#ifndef PAYMENT_H
#define PAYMENT_H

#include <QWidget>
#include<QPaintEvent>
#include<QPainter>
#include<QPixmap>

namespace Ui {
class Payment;
}

class Payment : public QWidget
{
    Q_OBJECT

public:
    explicit Payment(QWidget *parent = nullptr, double price = 0.0);
    void paintEvent(QPaintEvent* ) override;  //  初始背景图片
    ~Payment();

private:
    Ui::Payment *ui;
};

#endif // PAYMENT_H
