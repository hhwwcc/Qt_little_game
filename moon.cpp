#include "moon.h"

moon::moon()
{
    moon_init.load(":res/sky/moon");


}

void moon::moon_move(QPixmap u)
{
    moon_init = u;
}
