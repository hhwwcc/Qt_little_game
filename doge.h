#ifndef DOGE_H
#define DOGE_H
#include <QPixmap>


class doge
{
public:
    doge();

    //人物移动
    void move(int x);
//    void monkey_move(int x);

    //更换人物图片
    void change(QPixmap x);
    void monkey_change(QPixmap x);
    void locust_change(QPixmap x);


    //定义人物坐标（初始化）
    int doge_X;
    int monkey_X;

    int locust_X;
    int locust_Y;
    int locust_life=16;

    int insect_killer_X;
    int bark_voice_X;

    //定义资源对象
    QPixmap doge_0;//主狗头
    QPixmap doge_1;//左边的狗头
    QPixmap doge_2;//右边的狗头
    /////////交替变化要用到的太阳图片
    QPixmap sun_change_figure;
    //////////猴子
    QPixmap monkey_init;
    QPixmap monkey;
    QPixmap monkey_eat;
    ///////蝗虫
    QPixmap locust_init;
    QPixmap locust;
    QPixmap locust_fly;
    //////////农药
    QPixmap insect_killer;
    ////////驱赶特效
    QPixmap bark_voice;
    ////////栅栏
    QPixmap fence;


};

#endif // DOGE_H
