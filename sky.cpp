#include "sky.h"

sky::sky()
{
    //白天
    day.load(":res/sky/Blue Skies");
    day_change.load(":res/sky/Atlas");
    //夜晚
    night.load(":res/sky/Frost");
    night_change.load(":res/sky/King Yna");
    //初始化天空位置
    sky_x=0;
    //初始化天空
    day_init.load(":res/sky/Atlas");


}

void sky::sky_change(QPixmap x)
{
    day_init = x;

}
