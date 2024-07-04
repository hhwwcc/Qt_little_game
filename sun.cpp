#include "sun.h"

sun::sun()
{
    sun_init.load(":res/sky/sun");

}

void sun::sun_move(QPixmap x)
{
    sun_init = x;
}
