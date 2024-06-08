#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "foodwidget.h"
#include"payment.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent* );  //  初始背景图片
private:
    // 存储菜单的widget
    int countMainCourse;
    int countDessert;
    int countDrink;
    FoodWidget** mainCourseArr;
    FoodWidget** dessertArr;
    FoodWidget** drinkArr;
    Ui::MainWindow *ui;
    // 总价格
    double curVal;
};
#endif // MAINWINDOW_H
