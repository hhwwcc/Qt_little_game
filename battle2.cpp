#include "battle2.h"
#include<QKeyEvent>
#include<stdio.h>


battle2::battle2(QWidget *parent)
    : QWidget{parent}
{
    //设置战斗场景大小
    this->setFixedSize(1600,900);
    this->setWindowTitle("战斗2");
    this->setWindowIcon(QIcon(":/res/wheat_not_harvested"));
    playgame2();
    doge.monkey_X=1600;
//        qDebug()<<"init2";
//        init2();

    //设置走路音效
    movesound2->setSource(QUrl::fromLocalFile(":res/sound/move2.wav"));
    movesound2->setLoopCount(1);

    //设置触碰边缘音效
    bouncesound2->setSource(QUrl::fromLocalFile(":res/sound/bounce.wav"));
    bouncesound2->setLoopCount(1);

    //设置收获音效
    harvestsound2->setSource(QUrl::fromLocalFile(":res/sound/hittree.wav"));
    harvestsound2->setLoopCount(1);

    //设置果树掉落拾取音效
    dropsound->setSource(QUrl::fromLocalFile(":res/sound/dropcollect.wav"));
    dropsound->setLoopCount(1);

    //设置猴子吃音效
    monkey_eat->setSource(QUrl::fromLocalFile(":res/sound/eat.wav"));
    monkey_eat->setLoopCount(1);
    //设置驱赶音效
    barksound->setSource(QUrl::fromLocalFile(":res/sound/bark.wav"));
    barksound->setLoopCount(1);

}

void battle2::init2()
{

    down=0;//开关值置为0
    doge.doge_X=1600;
    doge.monkey_X=0;
    Monkey_left_right=0;//猴子左右移动初始值为0即往右
    monkey_wait=0;
//    加载初始果树
    tree.tree1_change(tree.tree_not_harvested);
    tree.tree2_change(tree.tree_not_harvested);
    tree.tree3_change(tree.tree_not_harvested);

    //初始化果树生命
    tree.tree1_life=150;
    tree.tree2_life=150;
    tree.tree3_life=150;

    //初始化回复累加值
    tree.tree1_reborn=0;
    tree.tree2_reborn=0;
    tree.tree3_reborn=0;

    //初始化果实坐标
    fruit.fruit_Y=-100;
    fruit.fruit_invader_Y=-100;

    //初始化库存
     wheat.wheat_stock = 0;
     tree.fruit_stock = 0;
     egg.egg_stock = 0;
    //初始化目标
     wheat.wheat_aim = 12;
     tree.fruit_aim = 45;
     egg.egg_aim = 3;


}


void battle2::playgame2()//第二个场景的计时器
{

    KeyRepeat2.clear();


//    m2_Timer.start(16);//刷新次数每16毫秒1次
//    connect(&m2_Timer,&QTimer::timeout,[=](){
//        update();//刷新场景
//        inthestock2();//库存
//        theaim2();//目标
//        nextlevel2();//下一目标
//    });
    //第二个场景人物移动
//    key_Timer2 = new QTimer(this);
//    key_Timer2->start(6);//狗头每6ms变化一次
//    connect(key_Timer2,&QTimer::timeout,[=]{

//        dogemove2();//移动
//        dogemovesound2();//移动音效
//        dogebounce2();//碰撞
//    });

    //收获的定时器
//    tree_harvest_timer = new QTimer(this);
//    tree_harvest_timer->start(40);//频率为每50ms1次
//    connect(tree_harvest_timer,&QTimer::timeout,[=]{
//        keyfruitharvest();//收获

//    });

//    //重新长出的定时器
//    tree_reborn_timer = new QTimer(this);
//    tree_reborn_timer->start(1000);//每秒侦测一次果树回复
//    connect(tree_reborn_timer,&QTimer::timeout,[=]{
//        invader_harvest_judge();
//        treereborn();
//        qDebug()<<"bark";
//        qDebug()<<"bark1";
////        qDebug()<<fruit.fruit_invader_Y;
//    });

//    //果实坠落动画定时器
//    fruit_fall_timer = new QTimer(this);
//    fruit_fall_timer->start(3);
//    connect(fruit_fall_timer,&QTimer::timeout,[=]{
//        fruitdrop();
//        invader();
//        fruitdrop_invader();

//    });
//    fruit_fall_timer->stop();
//    qDebug()<<"stop";
//    fruit_fall_timer->stop();
//    qDebug()<<"stop";

}

void battle2::paintEvent(QPaintEvent *)//绘制
{
    QPainter painter(this);
    QPixmap battle2;
    battle2.load(":/res/battle2");

    //绘制天空
    painter.drawPixmap(sky.sky_x,0,1600,900,sky.day_init);
    //绘制天空物件
    painter.drawPixmap(sun.sun_x,sun.sun_y,400,400,sun.sun_init);

    //绘制围栏
    painter.drawPixmap(0,-35,1600,900,doge.fence);

    //绘制入侵者
    painter.drawPixmap(doge.monkey_X,450,173,200,doge.monkey_init);
    //绘制果实
    painter.drawPixmap(fruit.fruit_X,fruit.fruit_Y,60,60,fruit.fruit_init);
    painter.drawPixmap(fruit.fruit_invader_X,fruit.fruit_invader_Y,60,60,fruit.fruit_invader_gain);



    //绘制果树
    painter.drawPixmap(20,90,480,600,tree.tree1_init);//绘制初始果树
    painter.drawPixmap(500,90,480,600,tree.tree2_init);
    painter.drawPixmap(980,90,480,600,tree.tree3_init);



    //绘制场景2
    painter.drawPixmap(0,0,1600,900,battle2);

    //绘制库存图标
    painter.drawPixmap(-20,2,70,45,wheat.wheatinstock);//小麦
    painter.drawPixmap(0,30,60,70,fruit.fruit_init);//果实
    painter.drawPixmap(-78,75,200,100,egg.egg_1);//鸡蛋


    painter.drawPixmap(doge.doge_X,532,120,120,doge.doge_0);//绘制到来的狗头
    painter.drawPixmap(doge.bark_voice_X,532,120,120,doge.bark_voice);//驱赶特效

}

void battle2::dogemove2()//第二个场景狗头移动
{
    for(int keycode : KeyRepeat2)
    {
        switch (keycode)
        {
        case Qt::Key_A:
            doge.move(-5);
            doge.change(doge.doge_1);
            if(doge.doge_X<0){
                bouncesound2->play();
                V2=50;//给予人物弹回场景的初加速度
            }

            break;
        case Qt::Key_D:
            doge.move(5);
            doge.change(doge.doge_2);
            if(doge.doge_X>1600){
                this->hide();
                KeyRepeat2.clear();
                backtobattlefrombattle2();
            }
            break;
        }
    }

}

void battle2::dogebounce2()//触碰场景边缘的处理
{
    if(V2>0){//有初速度
        doge.doge_X +=V2;
        V2--;//初速度减少a
    }
}

void battle2::dogemovesound2()//行走音效播放
{
    if(doge.doge_X==100){
        movesound2->play();
    }
    if(doge.doge_X==600){
        movesound2->play();
    }
    if(doge.doge_X==1000){
        movesound2->play();
    }
    if(doge.doge_X==1400){
        movesound2->play();
    }
}

void battle2::keyfruitharvest()//收获按键
{
    for(int hkeycode : KeyRepeat2){
        switch (hkeycode) {
        case Qt::Key_J: harvestjudge();
            break;
        }
    }
}

void battle2::fruitharvest()//收获动画
{
    if(doge.doge_X>40&&doge.doge_X<420){//第一处收获动画
        if(ChangePage==0){
            tree.tree1_change(tree.tree_under_harvest1);
            ChangePage=1;
        }
        else if(ChangePage==1){
            tree.tree1_change(tree.tree_under_harvest2);
            ChangePage=0;
        }
    }
    if(doge.doge_X>520&&doge.doge_X<900){//第二处收获动画
        if(ChangePage==0){
            tree.tree2_change(tree.tree_under_harvest1);
            ChangePage=1;
        }
        else if(ChangePage==1){
            tree.tree2_change(tree.tree_under_harvest2);
            ChangePage=0;
        }
    }
    if(doge.doge_X>1000&&doge.doge_X<1380){//第三处收获动画
        if(ChangePage==0){
            tree.tree3_change(tree.tree_under_harvest1);
            ChangePage=1;
        }
        else if(ChangePage==1){
            tree.tree3_change(tree.tree_under_harvest2);
            ChangePage=0;
        }
    }
}

void battle2::harvestjudge()//判定收获
{
    if(fruit.fruit_Y<0){
        fruit.fruit_Y=900;
    }
    if(doge.doge_X>40&&doge.doge_X<420){//第一处果树

        if(tree.tree1_life>0){
            fruit.fruit_X=doge.doge_X;//在狗头当前位置播放一个果实掉落动画
            tree.tree1_life-=1;
            tree.fruit_stock+=1;
            fruitharvest();//放一次果树动画
            if(fruit.fruit_Y>523){
                fruit.fruit_Y=180;//重置果实位置
            }
//            harvestsound2->play();
        }
        else if(tree.tree1_life<=0){

            tree.tree1_change(tree.tree_harvested);
        }
    }
    if(doge.doge_X>520&&doge.doge_X<900){//第二处果树
        if(tree.tree2_life>0){
            tree.tree2_life-=1;
            tree.fruit_stock+=1;
            fruitharvest();//放一次果树动画
            if(fruit.fruit_Y>532){
                fruit.fruit_X=doge.doge_X;//在狗头当前位置播放一个果实掉落动画
                fruit.fruit_Y=180;
            }
//            harvestsound2->play();
        }
        else if(tree.tree2_life<=0){
            tree.tree2_change(tree.tree_harvested);
        }

    }
    if(doge.doge_X>1000&&doge.doge_X<1380){//第三处果树
        if(tree.tree3_life>0){
            tree.tree3_life-=1;
            tree.fruit_stock+=1;
            fruitharvest();//放一次果树动画
            if(fruit.fruit_Y>532){
                fruit.fruit_X=doge.doge_X;//在狗头当前位置播放一个果实掉落动画
                fruit.fruit_Y=180;
            }
//            harvestsound2->play();
        }
        else if(tree.tree3_life<=0){
            tree.tree3_change(tree.tree_harvested);
        }
    }
}

void battle2::treereborn()//重新长出
{
    //第一处果树回复
    if(tree.tree1_life==0){//在果树生命值为0的时候
        tree.tree1_reborn+=1;//增加一点回复值

//        qDebug()<<tree.tree1_reborn;
    }
    if(tree.tree1_reborn==20){//回复值为20
        tree.tree1_life+=150;//回满果树生命
        tree.tree1_reborn=0;//重置回复值为0
        tree.tree1_change(tree.tree_not_harvested);
//        qDebug()<<tree.tree1_life;
    }

    //第二处果树回复
    if(tree.tree2_life==0){
        tree.tree2_reborn+=1;
//        qDebug()<<tree.tree2_reborn;
    }
    if(tree.tree2_reborn==20){
        tree.tree2_life=150;
        tree.tree2_reborn=0;
        tree.tree2_change(tree.tree_not_harvested);
//        qDebug()<<tree.tree2_life;
    }
    //第三处果树回复
    if(tree.tree3_life==0){
        tree.tree3_reborn+=1;
//        qDebug()<<tree.tree3_reborn;
    }
    if(tree.tree3_reborn==20){
        tree.tree3_life=150;
        tree.tree3_reborn=0;
        tree.tree3_change(tree.tree_not_harvested);
//        qDebug()<<tree.tree3_life;
    }
}

void battle2::fruitdrop()//果实动画
{

    fruit.fruit_change_x(fruit.fruit_fall);
    if(fruit.fruit_Y>0&&fruit.fruit_Y<532){//如果果实掉落到狗头位置则应该消失
        fruit.fruit_Y+=20;
    }
    if(fruit.fruit_Y==200){
        harvestsound2->play();
        fruit.fruit_Y+=20;
    }
    if(fruit.fruit_Y>532&&fruit.fruit_Y<547){
        dropsound->play();
        fruit.fruit_Y=900;
    }

}

void battle2::fruitdrop_invader()//入侵者果实动画
{

    fruit.fruit_change_y(fruit.fruit_fall);
    if(fruit.fruit_invader_Y>0&&fruit.fruit_invader_Y<532){//如果果实掉落到猴子位置则应该消失
        doge.monkey_change(doge.monkey_eat);
        fruit.fruit_invader_Y+=10;
    }
    if(fruit.fruit_invader_Y==200){
        harvestsound2->play();
        fruit.fruit_invader_Y+=10;
    }
    if(fruit.fruit_invader_Y==480){
        monkey_eat->play();
        fruit.fruit_invader_Y+=10;
        doge.monkey_change(doge.monkey);
        fruit.fruit_invader_Y=900;

    }
}

void battle2::invader()//入侵者
{


    ////////////////////在范围内往右
    if(Monkey_left_right==0&&doge.monkey_X<1050&&doge.monkey_X>160){//在160到1050这个范围内左右值为0往右
        doge.monkey_X+=1;
    }
    else if(doge.monkey_X>=1050&&doge.monkey_X<1200){//超出1050吧左右值置1开始往左移动
        Monkey_left_right=1;
        doge.monkey_X-=1;
    }
    /////////////////////在范围内往左
    else if(Monkey_left_right==1&&doge.monkey_X>160&&doge.monkey_X<1050){//在160到1050这个范围内左右值为1往左
        doge.monkey_X-=1;
    }
    ////////////////////超出范围则往右
    else if(doge.monkey_X<=160&&doge.monkey_X>=-200){
        Monkey_left_right=0;
        doge.monkey_X+=1;
    }
    ///////////被赶出去以后直接朝农场方向移动
    if(doge.monkey_X<-200){
        doge.monkey_X+=1;
    }
    if(doge.monkey_X>-200){
        monkey_wait=0;
    }
    else if(doge.monkey_X<-200&&monkey_wait==0){
        monkey_wait=1;
        doge.monkey_X=-8000;
    }
}
void battle2::invader_harvest(){//入侵者收获动画
    if(doge.monkey_X>160&&doge.monkey_X<300){
        /////////////////加入果树反馈动画
        if(ChangePage_invader==0){
            tree.tree1_change(tree.tree_under_harvest1);
            ChangePage_invader=1;
        }
        else if(ChangePage_invader==1){
            tree.tree1_change(tree.tree_under_harvest2);
            ChangePage_invader=0;
        }
    }
    if(doge.monkey_X>640&&doge.monkey_X<780){
        //////////////////第二处果树动画
        if(ChangePage2_invader==0){
            tree.tree2_change(tree.tree_under_harvest1);
            ChangePage2_invader=1;
        }
        else if(ChangePage2_invader==1){
            tree.tree2_change(tree.tree_under_harvest2);
            ChangePage2_invader=0;
        }
    }
    if(doge.monkey_X>900&&doge.monkey_X<=1050){
        ///////////////动画
        if(ChangePage3_invader==0){
            tree.tree3_change(tree.tree_under_harvest1);
            ChangePage3_invader=1;
        }
        else if(ChangePage3_invader==1){
            tree.tree3_change(tree.tree_under_harvest2);
            ChangePage3_invader=0;
        }
    }
}

void battle2::invader_harvest_judge()//入侵者判定
{
    if(fruit.fruit_invader_Y<0){
        fruit.fruit_invader_Y=900;
    }
    if(doge.monkey_X>160&&doge.monkey_X<300){
        if(tree.tree1_life>0){//如果有果实
            fruit.fruit_invader_X=doge.monkey_X+75;//果实从猴子头上坠落
            tree.tree1_life-=1;
            invader_harvest();//播放动画
            if(fruit.fruit_invader_Y>523){
                fruit.fruit_invader_Y=180;//重置果实位置
            }
            if(tree.tree1_life==0){
                tree.tree1_change(tree.tree_harvested);
            }
        }
    }

    if(doge.monkey_X>640&&doge.monkey_X<780){
        if(tree.tree2_life>0){//如果有果实
            fruit.fruit_invader_X=doge.monkey_X+75;//果实从猴子头上坠落
            tree.tree2_life-=1;
            invader_harvest();//播放动画
            if(fruit.fruit_invader_Y>523){
                fruit.fruit_invader_Y=180;//重置果实位置
            }
            if(tree.tree2_life==0){
                tree.tree2_change(tree.tree_harvested);
            }
        }
    }
    if(doge.monkey_X>900&&doge.monkey_X<1050){
        if(tree.tree3_life>0){//如果有果实
            fruit.fruit_invader_X=doge.monkey_X+75;//果实从猴子头上坠落
            tree.tree3_life-=1;
//            qDebug()<<tree.tree3_life;
            invader_harvest();//播放动画
            if(fruit.fruit_invader_Y>523){
                fruit.fruit_invader_Y=180;//重置果实位置
            }
            if(tree.tree3_life==0){
                tree.tree3_change(tree.tree_harvested);
            }
        }
    }
}

void battle2::bark()//驱赶入侵者
{
    if(VMonkey>0){
        VMonkey-=1;
        doge.monkey_X-=VMonkey;
    }
}

//void battle2::monkey_to_stop()//猴子在游戏外停止
//{
//    if(monkey_stop==1){
//        doge.monkey_X=-200;
//    }
//}

void battle2::bark_voice_show()//显示声音图片
{
    doge.bark_voice_X=doge.doge_X-70;
    voice_left=0;
}

void battle2::bark_voice_hide()//隐藏声音图片
{
    if(voice_left<15){//停留值小于15则加1，每1毫秒加1
        voice_left+=1;
    }
    else{//15毫秒后移出声音图片
        doge.bark_voice_X=1600;
    }
}

///显示库存数量的实现
void battle2::inthestock2()
{
        //设置显示当前收获的小麦
        wheat_stock_count->setParent(this);
        QString wheat_stock_string = QString::number(wheat.wheat_stock);//qt特有int型转string型
        QFont wheat_font("黑体",30,30,1);
        wheat_stock_count->setFont(wheat_font);
        wheat_stock_count->setText(wheat_stock_string);//第一次显示库存为0之后为当前库存数
        wheat_stock_count->move(60,0);
        wheat_stock_count->setFixedSize(200,50);

        //设置显示当前收获的果实
        fruit_stock_count->setParent(this);
        QString fruit_stock_string = QString::number(tree.fruit_stock);//qt特有int型转string型
        QFont fruit_font("黑体",30,30,1);
        fruit_stock_count->setFont(fruit_font);
        fruit_stock_count->setText(fruit_stock_string);//第一次显示库存为0之后为当前库存数
        fruit_stock_count->move(55,50);
        fruit_stock_count->setFixedSize(200,50);

        //设置显示当前收获的鸡蛋
        egg_stock_count->setParent(this);
        QString egg_stock_string = QString::number(egg.egg_stock);//qt特有int型转string型
        QFont egg_stock("黑体",30,30,1);
        egg_stock_count->setFont(egg_stock);
        egg_stock_count->setText(egg_stock_string);//第一次显示库存为0之后为当前库存数
        egg_stock_count->move(50,100);
        egg_stock_count->setFixedSize(200,50);

}
///当前库存目标的实现
void battle2::theaim2()
{
        //目标小麦数量
        wheat_aim_label->setParent(this);
        QString wheat_aim_string = QString::number(wheat.wheat_aim);
        QFont aimfont("黑体",25,25,1);
        wheat_aim_label->setText("目标:"+wheat_aim_string);
        wheat_aim_label->setFont(aimfont);
        wheat_aim_label->move(160,-25);
        wheat_aim_label->setFixedSize(400,100);

        //目标果实数量
        fruit_aim_label->setParent(this);
        QString fruit_aim_string = QString::number(tree.fruit_aim);
        fruit_aim_label->setText("目标:"+fruit_aim_string);
        fruit_aim_label->setFont(aimfont);
        fruit_aim_label->move(155,25);
        fruit_aim_label->setFixedSize(400,100);

        //目标鸡蛋数量
        egg_aim_label->setParent(this);
        QString egg_aim_string = QString::number(egg.egg_aim);
        egg_aim_label->setText("目标:"+egg_aim_string);
        egg_aim_label->setFont(aimfont);
        egg_aim_label->move(148,75);
        egg_aim_label->setFixedSize(400,100);

}
///进入下一关卡的实现
void battle2::nextlevel2()
{
//        time_remain->setParent(this);
//        QString timeremain = QString::number(wheat.time_remain);
//        QFont font("黑体",50,50,1);
//        time_remain->setText("下一年:"+timeremain);
//        time_remain->setFont(font);
//        time_remain->move(530,-10);
//        time_remain->setFixedSize(400,100);
//        if(wheat.time_remain==21){
//            wheat.time_remain-=1;
//        }
//        if(wheat.time_remain==2&&tree.fruit_stock>=tree.fruit_aim){


//        }

}
//键盘按下
void battle2::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_A://向左走
        case Qt::Key_D://向右走
        case Qt::Key_J:
            KeyRepeat2.append(event->key());
        break;
        case Qt::Key_K:
            if(doge.monkey_X>-200){
                VMonkey=40;//喝退
            }
            barksound->play();//播放音效
            bark_voice_show();
        break;

        }
}
//键盘松开
void battle2::keyReleaseEvent(QKeyEvent *event)
{
        if(KeyRepeat2.contains(event->key())){
            KeyRepeat2.removeOne(event->key());
        }
}
