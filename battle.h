#ifndef BATTLE_H
#define BATTLE_H

#include <QWidget>
#include<QPainter>
#include<QLabel>
#include<QKeyEvent>
#include<QDebug>
#include <QTimer>
#include <QList>
#include <QSound>
#include <QSoundEffect>
#include <QtMath>

#include "doge.h"
#include "wheat.h"

#include "battle2.h"
#include "battle3.h"

#include "sky.h"
#include "sun.h"
#include "moon.h"



class battle : public QWidget
{
    Q_OBJECT
public:

    doge doge;
    wheat wheat;
    fruit fruit;
    egg egg;
    tree tree;

    sky sky;
    sun sun;
    moon moon;


    int sky_switch;//天空变化的一个值
    int sun_to_moon;//天空物件变化的值

    int locust_action;//蝗虫动画值
    int insect_killer_left;//农药停留时间值
    bool monkey_stop=1;//猴子移动开关

    int place;//蝗虫出现位置值

    explicit battle(QWidget *parent = nullptr);
    QTimer m_Timer; //人物移动刷新

    QTimer* key_timer;//键盘行动刷新
    QTimer* wheat_Timer;//小麦动画刷新
    QTimer* wheat_gotoharvest;//小麦收获动作刷新
    QTimer* stock_Timer;//库存的刷新
    QTimer* level_Timer;//关卡等级倒计时的刷新


    QList<int> KeyRepeat;//按键组合，用链表存储
    QList<int> wheatgotoharvest;//自动收获按键的存储

    QString aim;

    //声明初始化场景2的信号
    void battlescene2_init();

    void Initbattlescene();//初始化战斗场景
    void DogeMove();//狗头移动
    void dogemovesound();//移动音效

    void playGame();//游戏进行中
    void dotheharvest();//收获动作
    void autoharvest();//自动收获动作
    void reborn();//小麦重新生长
    void inthestock();//当前库存
    void theaim();//当前目标库存
    void currentlevel();//当前关卡等级
    void nextlevel();//进入下一关卡等级

    void sky_change_1();//背景天空的变化
    void sun_change();//天体移动

    void invader_locust();//蝗虫
    void locust_show_up();//蝗虫动画
    void locust_harvest();//蝗虫收获判定
    void insect_killer_show_up();//显示农药
    void insect_killer_hide();//隐藏农药

    //声明接收从场景2回到场景1的信号
    void btbfb2();
    //声明接收从battle3回到battle的信号
    void btbfb3();

    void end();//结束游戏

signals:
    //声明返回的信号
    void BackToTitle();

private:

    bool PressFlag=false;
//////////////库存，任务目标等显示/////////////////////////
    //一个库存数量的标签
    QLabel * wheat_stock_count = new QLabel(this);//小麦库存
    QLabel * fruit_stock_count = new QLabel(this);//果实库存
    QLabel * egg_stock_count = new QLabel(this);//鸡蛋库存
    //一个目标的标签
    QLabel * wheat_aim_label = new QLabel(this);//目标小麦
    QLabel * fruit_aim_label = new QLabel(this);//目标果实
    QLabel * egg_aim_label = new QLabel(this);//目标鸡蛋
    //一个倒计时的标签
    QLabel * time_remain = new QLabel(this);
    //一个当前关卡等级的标签
    QLabel * currentL = new QLabel(NULL);




///////////////音效///////////////////////////////
    //一个背景音的音效
    QSoundEffect * backgroundsound = new QSoundEffect(this);//实例QSoundEffect的指针
    //行走的音效
    QSoundEffect * movesound = new QSoundEffect(this);
    //一个背景音乐的音效
    QSoundEffect * backgroundmusic = new QSoundEffect(this);
    //一个收获的音效
    QSoundEffect * harvestsound = new QSoundEffect(this);
    //杀虫音效
    QSoundEffect * insect_killer_sound = new QSoundEffect(this);
    //蝗虫的音效
    QSoundEffect * locust_come = new QSoundEffect(this);
    QSoundEffect * locust_die = new QSoundEffect(this);



///////////////声明左右两侧场景的对象//////////////////
    //声明第二个场景
    battle2* battlescene2 = new battle2(NULL);
    //声明第三个场景
    battle3* battlescene3 = new battle3(NULL);


protected:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

};

#endif // BATTLE_H
