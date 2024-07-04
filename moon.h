#ifndef MOON_H
#define MOON_H

#include <QPixmap>
class moon
{
public:
    moon();

    int moon_x;
    int moon_y;


    void moon_move(QPixmap u);


    QPixmap moon_init;


};

#endif // MOON_H
