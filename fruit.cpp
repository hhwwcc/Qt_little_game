#include "fruit.h"

fruit::fruit()
{
    //加载果实
    fruit_init.load(":res/fruit");
    fruit2_init.load(":res/fruit");
    fruit3_init.load(":res/fruit");

    //加载坠落果实
    fruit_fall.load(":res/fruit");
    fruit_invader_gain.load(":res/fruit");
}

void fruit::fruitmove(int u)
{
    fruit_Y += u;
}

void fruit::invader_fruitmove(int u)
{
    fruit_invader_Y +=u;
}

void fruit::fruit_change_x(QPixmap x)
{
    fruit_fall = x;
}

void fruit::fruit_change_y(QPixmap y)
{
    fruit_fall = y;
}

void fruit::fruit_invader_change(QPixmap x)
{
    fruit_invader_gain = x;
}
