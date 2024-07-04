#ifndef WHEAT_H
#define WHEAT_H

#include<QPixmap>

class wheat
{
public:
    wheat();

    void wheat_change1(QPixmap x);//收获小麦1完成以后切换对应图片
    void wheat_change2(QPixmap x);//收获小麦2完成以后切换对应图片
    void wheat_change3(QPixmap x);//收获小麦3完成以后切换对应图片
    void wheat_change4(QPixmap x);//收获小麦4完成以后切换对应图片
    void wheat_change5(QPixmap x);//收获小麦5完成以后切换对应图片


    //设置每处小麦的生命
    int life1;
    int life2;
    int life3;
    int life4;
    int life5;

    //设置恢复的累加值
    int toreborn1;
    int toreborn2;
    int toreborn3;
    int toreborn4;
    int toreborn5;

    //未被收获的小麦
    QPixmap wheat_not_harvested;

    //已被收获的小麦
    QPixmap wheat_harvested;

    //正在被收获的小麦
    QPixmap wheat_under_harvest1;
    QPixmap wheat_under_harvest2;
    QPixmap wheat_under_harvest3;

    //设置小麦初始值
    QPixmap wheat_1_0;
    QPixmap wheat_2_0;
    QPixmap wheat_3_0;
    QPixmap wheat_4_0;
    QPixmap wheat_5_0;

    //设置库存的小麦
    int wheat_stock;

    //设置每年的目标
    int wheat_aim;
    //设置倒计时
    int time_remain=9999;
    //设置当前关卡等级
    int current_level=0;
    //设置小麦动画的变量
    int wheat_animation=20;

    //设置库存图标
    QPixmap wheatinstock;
};

#endif // WHEAT_H
