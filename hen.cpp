#include "hen.h"

hen::hen()
{
    hen_break.load(":res/hen.png");//加载生产鸡

    hen_under_harvest.load(":res/hen_harvest");//加载收获鸡

    hen1_init.load(":res/hen");//初始状态下的鸡
    hen2_init.load(":res/hen");
    hen3_init.load(":res/hen");
    hen4_init.load(":res/hen");
}

void hen::hen1_change(QPixmap x)
{
    hen1_init = x;
}

void hen::hen2_change(QPixmap x)
{
    hen2_init = x;
}

void hen::hen3_change(QPixmap x)
{
    hen3_init = x;
}

void hen::hen4_change(QPixmap x)
{
    hen4_init = x;
}
