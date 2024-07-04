#ifndef EGG_H
#define EGG_H

#include <QPixmap>

class egg
{
public:
    egg();

    //鸡蛋图片改变
    void egg1_change(QPixmap x);
    void egg2_change(QPixmap x);
    void egg3_change(QPixmap x);
    void egg4_change(QPixmap x);

    int egg_X;//变化的坐标
    int egg2_X;
    int egg3_X;
    int egg4_X;

    int egg1_life;//鸡蛋的生命
    int egg2_life;
    int egg3_life;
    int egg4_life;

    //鸡蛋库存
    int egg_stock;

    //设置每年的目标
    int egg_aim;

    //鸡窝鸡蛋已经屯满
    QPixmap egg_full;

    //正在收获的鸡蛋
    QPixmap egg_1;
    QPixmap egg_2;
    QPixmap egg_3;
    QPixmap egg_4;
    QPixmap egg_5;

    //初始鸡蛋
    QPixmap egg1_init;
    QPixmap egg2_init;
    QPixmap egg3_init;
    QPixmap egg4_init;


};

#endif // EGG_H
