#include "doge.h"

doge::doge()
{
    //第一个场景狗头资源
    doge_0.load(":res/doge_right");
    doge_1.load(":res/doge_left");
    doge_2.load(":res/doge_right");

    //要用到的太阳
    sun_change_figure.load(":res/sky/sun");

    //入侵者
    monkey.load(":res/monkey");
    monkey_init.load(":res/monkey");
    monkey_eat.load(":res/eat");

    locust_init.load(":res/locust");
    locust.load(":res/locust");
    locust_fly.load(":res/locust");

    //道具
    insect_killer.load(":res/insect_killer");
    bark_voice.load(":res/voice");

    //围栏
    fence.load(":res/fence");



}

void doge::move(int x)
{
    doge_X += x;

}

//void doge::monkey_move(int x)
//{
//    monkey_X = x;
//}

void doge::change(QPixmap x)
{
    doge_0 = x ;
}

void doge::monkey_change(QPixmap x)
{
    monkey_init = x;
}

void doge::locust_change(QPixmap x)
{
    locust_init = x;
}

