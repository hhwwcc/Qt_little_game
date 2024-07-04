#include "wheat.h"

wheat::wheat()
{
    //加载未被收获的小麦图片
    wheat_not_harvested.load(":res/wheat_not_harvested.png");

    //加载已被收获的小麦的图片
    wheat_harvested.load(":res/wheat_harvested.png");

    //加载正在被收获的小麦图片
    wheat_under_harvest1.load(":res/wheat_under_harvest1");
    wheat_under_harvest2.load(":res/wheat_under_harvest2");
    wheat_under_harvest3.load(":res/wheat_under_harvest3");
    //设置初始状态下的小麦的图片
    wheat_1_0.load(":res/wheat_not_harvested.png");
    wheat_2_0.load(":res/wheat_not_harvested.png");
    wheat_3_0.load(":res/wheat_not_harvested.png");
    wheat_4_0.load(":res/wheat_not_harvested.png");
    wheat_5_0.load(":res/wheat_not_harvested.png");
    //加载库存图标
    wheatinstock.load(":res/stock.png");
}

void wheat::wheat_change1(QPixmap x)
{
    wheat_1_0 = x;
}

void wheat::wheat_change2(QPixmap x)
{
    wheat_2_0 = x;
}

void wheat::wheat_change3(QPixmap x)
{
    wheat_3_0 = x;
}

void wheat::wheat_change4(QPixmap x)
{
    wheat_4_0 = x;
}

void wheat::wheat_change5(QPixmap x)
{
    wheat_5_0 = x;
}

