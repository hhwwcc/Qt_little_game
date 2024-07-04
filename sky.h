#ifndef SKY_H
#define SKY_H

#include <QPixmap>


class sky
{
public:
    sky();

    void sky_change(QPixmap x);

    //图片放置的位置
    int sky_x;

    //天空图片
    QPixmap day;
    QPixmap day_change;
    QPixmap night_change;
    QPixmap night;


    //天空初始
    QPixmap day_init;

};

#endif // SKY_H
