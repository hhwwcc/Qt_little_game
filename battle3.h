 #ifndef BATTLE3_H
#define BATTLE3_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QLabel>
#include <QList>
#include <QSound>
#include <QSoundEffect>



#include "doge.h"
#include "henhouse.h"
#include "egg.h"
#include "hen.h"
#include "wheat.h"
#include "tree.h"
#include "fruit.h"

#include "sky.h"
#include "sun.h"


class battle3 : public QWidget
{
    Q_OBJECT
public:

    int V3=0;//触碰场景边缘的初速度
    int WARN=0;//提醒开关

    doge doge;
    henhouse henhouse;
    egg egg;
    hen hen;
    wheat wheat;
    tree tree;
    fruit fruit;

    sky sky;
    sun sun;


    explicit battle3(QWidget *parent = nullptr);

    void init3();//初始化游戏
    void playgame3();//游戏进行
    void dogemove3();//第三个场景狗头移动的实现
    void dogemovesound3();//移动音效
    void dogebounce3();//触碰场景边缘

    void fullremind();//鸡蛋满提醒

    void henmove();//鸡动画
    void eggharvest();//收获
    void eggmove();//鸡蛋动画
    void eggreborn();//鸡蛋生产

    void inthestock3();//库存
    void theaim3();//目标

    QList<int> keyrepeat3;//移动链表
    QTimer m3_Timer;//第三个场景游戏进行计时器
    QTimer * key_Timer3;//人物动作
    QTimer * egg_timer;//鸡蛋生产定时器



signals:
    void backtobattlefrombattle3();//声明从battle3回到battle的信号

private:
    //移动音效
    QSoundEffect * movesound3 = new QSoundEffect(this);
    //碰撞音效
    QSoundEffect * bouncesound3 = new QSoundEffect(this);
    //收获音效
    QSoundEffect * harvestsound3 = new QSoundEffect(this);
    //下蛋音效
    QSoundEffect * eggdrop = new QSoundEffect(this);
    //提示音效
    QSoundEffect * eggfull = new QSoundEffect(this);

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

#endif // BATTLE3_H
