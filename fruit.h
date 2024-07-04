#ifndef FRUIT_H
#define FRUIT_H

#include<QPixmap>

class fruit
{
public:
    fruit();

    void fruitmove(int u);
    void invader_fruitmove(int u);

    //果实的位置
    int fruit_X;
    int fruit_Y;

    int fruit_invader_X;
    int fruit_invader_Y;


    void fruit_change_x(QPixmap x);
    void fruit_change_y(QPixmap y);

    void fruit_invader_change(QPixmap x);

    QPixmap fruit_init;//初始果实
    QPixmap fruit2_init;
    QPixmap fruit3_init;

    QPixmap fruit_fall;//坠落果实
    QPixmap fruit_invader_gain;//给入侵者的果实
};

#endif // FRUIT_H
