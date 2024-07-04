#ifndef SUN_H
#define SUN_H
#include <QPixmap>
class sun
{
public:
    sun();

    int sun_x;
    int sun_y;

    void sun_move(QPixmap x);

    QPixmap sun_init;
};

#endif // SUN_H
