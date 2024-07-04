#ifndef BATTLE2_H
#define BATTLE2_H

#include <QWidget>
#include <QPainter>
#include <QList>
#include <QTimer>
#include <QKeyEvent>
#include <QLabel>
#include<QDebug>
#include <QSound>
#include <QSoundEffect>
#include <QIcon>


#include "doge.h"
#include "tree.h"
#include "egg.h"
#include "wheat.h"
#include "fruit.h"

#include "sky.h"
#include "sun.h"
#include "moon.h"



class battle2 : public QWidget
{
    Q_OBJECT
public:

    int down;//开关值
    int sky_switch;//天空变化的一个值


    int V2=0;//碰撞的数值
    int voice_left;//声音图片停留时间的值

    int VMonkey=0;//猴子的速度
    int Monkey_left_right=0;//猴子左右移动
    int monkey_action_cache=0;//猴子不动的时候偷取动作的冷却
    int monkey_wait=0;//猴子被赶出去后再回来的时间值

    int ChangePage=0;//收获动画的值
    int ChangePage2=0;//收获动画的值
    int ChangePage3=0;//收获动画的值

    int ChangePage_invader=0;
    int ChangePage2_invader=0;
    int ChangePage3_invader=0;


    tree tree;
    doge doge;
    wheat wheat;
    fruit fruit;
    egg egg;

    sky sky;
    sun sun;
    moon moon;


    explicit battle2(QWidget *parent = nullptr);

    void init2();//初始化场景
    void dogemove2();//第二个场景的人物移动
    void dogebounce2();//触碰场景边缘
    void dogemovesound2();//移动音效
    void keyfruitharvest();//收获按键
    void fruitharvest();//收获动画
    void harvestjudge();//收获判定
    void treereborn();//果实重新长出
    void fruitdrop();//果实动画
    void fruitdrop_invader();//入侵者果实动画

    void invader();//入侵者
    void invader_harvest();//入侵者现身的时机
    void invader_harvest_judge();//判定入侵者收获
    void bark();//驱赶入侵者

    void monkey_to_stop();//入侵者在游戏进行外
    void bark_voice_show();//显示声音图片
    void bark_voice_hide();//隐藏声音图片

    void inthestock2();//库存
    void theaim2();//目标
    void nextlevel2();//下一等级的条件

    void playgame2();//第二个场景的计时器

//    QTimer m2_Timer;//游戏进行时计时器
//    QTimer * key_Timer2;//第二个场景的键盘人物移动
//    QTimer * tree_harvest_timer;//收获定时器
//    QTimer * tree_reborn_timer;//回复判定定时器
//    QTimer * fruit_fall_timer;//果实动画判定定时器

    QList<int> KeyRepeat2;//移动按键组合链表
    QList<int> HarvestRepeat;//收获按键组合





signals:
    void backtobattlefrombattle2();//声明回到第一个场景的信号

private:
    //行走的音效
    QSoundEffect * movesound2 = new QSoundEffect(this);
    //触碰场景边缘
    QSoundEffect * bouncesound2 = new QSoundEffect(this);
    //收获音效
    QSoundEffect * harvestsound2 = new QSoundEffect(this);
    //掉落拾取音效
    QSoundEffect * dropsound = new QSoundEffect(this);
//    //猴子吃音效
    QSoundEffect * monkey_eat = new QSoundEffect(this);
//    驱赶入侵者音效
    QSoundEffect * barksound = new QSoundEffect(this);

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

protected:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
};

#endif // BATTLE2_H
