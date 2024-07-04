#ifndef HEN_H
#define HEN_H

#include <QPixmap>

class hen
{
public:
    hen();

    //改变鸡的图片
    void hen1_change(QPixmap x);
    void hen2_change(QPixmap x);
    void hen3_change(QPixmap x);
    void hen4_change(QPixmap x);

    int hen1_Y;//鸡的位置只会上下变化
    int hen2_Y;
    int hen3_Y;
    int hen4_Y;


    QPixmap hen_break;//正在产蛋的鸡

    QPixmap hen_under_harvest;//正在收获中的鸡

    //初始鸡
    QPixmap hen1_init;
    QPixmap hen2_init;
    QPixmap hen3_init;
    QPixmap hen4_init;
};

#endif // HEN_H
