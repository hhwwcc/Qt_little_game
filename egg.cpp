#include "egg.h"

egg::egg()
{
    //初始鸡蛋
    egg_full.load(":res/egg/egg_5.png");

    //正在收获的鸡蛋
    egg_1.load(":res/egg/egg_1");
    egg_2.load(":res/egg/egg_2");
    egg_3.load(":res/egg/egg_3");
    egg_4.load(":res/egg/egg_4");
    egg_5.load(":res/egg/egg_5");

    //鸡蛋的初始变化
    egg1_init.load(":res/egg/egg_5");
    egg2_init.load(":res/egg/egg_5");
    egg3_init.load(":res/egg/egg_5");
    egg4_init.load(":res/egg/egg_5");

}

void egg::egg1_change(QPixmap x)
{
    egg1_init = x;
}

void egg::egg2_change(QPixmap x)
{
    egg2_init = x;
}

void egg::egg3_change(QPixmap x)
{
    egg3_init = x;
}

void egg::egg4_change(QPixmap x)
{
    egg4_init = x;
}
