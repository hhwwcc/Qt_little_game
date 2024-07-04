#include "battle3.h"
#include <QDebug>

battle3::battle3(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(1600,900);
    this->setWindowTitle("战斗");
    this->setWindowIcon(QIcon(":/res/wheat_not_harvested"));

    //设置走路音效
    movesound3->setSource(QUrl::fromLocalFile(":res/sound/move2.wav"));
    movesound3->setLoopCount(1);

    //设置触碰边缘音效
    bouncesound3->setSource(QUrl::fromLocalFile(":res/sound/bounce.wav"));
    bouncesound3->setLoopCount(1);

    //设置收获音效
    harvestsound3->setSource(QUrl::fromLocalFile(":res/sound/henhouse/collectegg.wav"));
    harvestsound3->setLoopCount(1);
    //设置下蛋音效
    eggdrop->setSource(QUrl::fromLocalFile(":res/sound/henhouse/egg.wav"));
    eggdrop->setLoopCount(1);
    //设置提示音效
    eggfull->setSource(QUrl::fromLocalFile(":res/sound/henhouse/eggfull.wav"));
    eggfull->setLoopCount(1);

    playgame3();//刷新场景
}

void battle3::init3()
{
    hen.hen1_Y=450;//初始鸡的位置
    hen.hen2_Y=450;
    hen.hen3_Y=450;
    hen.hen4_Y=450;

    egg.egg1_life=5;//初始鸡蛋的生命
    egg.egg2_life=5;
    egg.egg3_life=5;
    egg.egg4_life=5;

    egg.egg_X=400;//初始鸡蛋位置
    egg.egg2_X=609;
    egg.egg3_X=818;
    egg.egg4_X=1027;

    //初始化库存
     wheat.wheat_stock = 0;
     tree.fruit_stock = 0;
     egg.egg_stock = 0;
    //初始化目标
     wheat.wheat_aim = 12;
     tree.fruit_aim = 45;
     egg.egg_aim = 3;

    WARN=1;//提醒初始为关
}

void battle3::playgame3()//定时器
{
    init3();
    keyrepeat3.clear();
    doge.doge_X=-120;//初始狗头位置

    m3_Timer.start(6);
    connect(&m3_Timer,&QTimer::timeout,[=](){
        update();//更新场景
        inthestock3();
        theaim3();
    });

    //鸡蛋生产定时器
    egg_timer = new QTimer(this);
    egg_timer->start(3000);
    connect(egg_timer,&QTimer::timeout,[=](){
        eggreborn();
    });

    //狗头移动计时器
    key_Timer3 = new QTimer(this);
    key_Timer3->start(6);//狗头每6ms移动一次
    connect(key_Timer3,&QTimer::timeout,[=](){
        henmove();
        dogemove3();
        dogemovesound3();
        dogebounce3();
        eggmove();
        fullremind();
    });



}

void battle3::dogemove3()//狗头移动
{
    for(int keycode : keyrepeat3){
        switch (keycode) {
        case Qt::Key_A:
            doge.doge_X -= 5;
            doge.change(doge.doge_1);
            if(doge.doge_X<=-120){
                keyrepeat3.clear();//清除按键组合
                this->hide();
                backtobattlefrombattle3();//发送信号到battle
            }
            break;
        case Qt::Key_D:
            doge.doge_X += 5;
            doge.change(doge.doge_2);
            if(doge.doge_X>1485){
                bouncesound3->play();
                V3=50;//给予人物一个弹回场景的初速度
                }
        }
        break;
    }

}

void battle3::dogemovesound3()//移动音效
{
    if(doge.doge_X==100){
        movesound3->play();
    }
    if(doge.doge_X==600){
        movesound3->play();
    }
    if(doge.doge_X==1000){
        movesound3->play();
    }
    if(doge.doge_X==1400){
        movesound3->play();
    }
}

void battle3::dogebounce3()//场景三触碰边缘的处理
{
    if(V3>0){
        doge.doge_X -=V3;
        V3--;
    }
}

void battle3::fullremind()//鸡蛋满提醒
{
    if(egg.egg1_life==5&&egg.egg2_life==5&&egg.egg3_life==5&&egg.egg4_life==5){
        if(WARN==0){
            eggfull->play();
            WARN=1;//关闭提醒
        }
    }
}

void battle3::henmove()//鸡窝的动画
{
    //未被抬起来的鸡会进行生产
    if(hen.hen1_Y==450){
        hen.hen1_change(hen.hen_break);
    }
    if(hen.hen2_Y==450){
        hen.hen2_change(hen.hen_break);
    }
    if(hen.hen3_Y==450){
        hen.hen3_change(hen.hen_break);
    }
    if(hen.hen4_Y==450){
        hen.hen4_change(hen.hen_break);
    }
//////////////////////////////////第一处鸡窝
    //途经各个鸡窝都会抬起鸡看看有多少蛋
    if(doge.doge_X>=370&&doge.doge_X<=480){
        if(hen.hen1_Y>350){
            hen.hen1_change(hen.hen_under_harvest);
            hen.hen1_Y-=3;
        }
    }
    else{//把鸡放回去继续生产
        if(hen.hen1_Y<=450){
            hen.hen1_Y+=3;
        }
    }
////////////////////////////////第二处鸡窝
    if(doge.doge_X>=600&&doge.doge_X<=710){
        if(hen.hen2_Y>350){
            hen.hen2_change(hen.hen_under_harvest);
            hen.hen2_Y-=3;
        }
    }
    else{
        if(hen.hen2_Y<=450){
            hen.hen2_Y+=3;
        }
    }
////////////////////////////////第三处鸡窝
    if(doge.doge_X>=800&&doge.doge_X<=910){
        if(hen.hen3_Y>350){
            hen.hen3_change(hen.hen_under_harvest);
            hen.hen3_Y-=3;
        }
    }
    else{//把鸡放回去继续生产
        if(hen.hen3_Y<=450){
            hen.hen3_Y+=3;
        }
    }
////////////////////////////////第四处鸡窝
    if(doge.doge_X>=1000&&doge.doge_X<=1110){
        if(hen.hen4_Y>350){
            hen.hen4_change(hen.hen_under_harvest);
            hen.hen4_Y-=3;
        }
    }
    else{//把鸡放回去继续生产
        if(hen.hen4_Y<=450){
            hen.hen4_Y+=3;
        }
    }
}

void battle3::eggharvest()//收获
{
//////////////////////////////////第一处鸡窝
    //途经各个鸡窝都会抬起鸡看看有多少蛋
    if(doge.doge_X>=370&&doge.doge_X<=480){
        if(egg.egg1_life>0){
            WARN=0;//开启提醒
            egg.egg1_life-=1;
            egg.egg_stock+=1;
            harvestsound3->play();
        }
        eggmove();
    }
////////////////////////////////第二处鸡窝
    if(doge.doge_X>=600&&doge.doge_X<=710){
        if(egg.egg2_life>0){
            WARN=0;
            egg.egg2_life-=1;
            egg.egg_stock+=1;
            harvestsound3->play();
        }
        eggmove();
    }
////////////////////////////////第三处鸡窝
    if(doge.doge_X>=800&&doge.doge_X<=910){
        if(egg.egg3_life>0){
            WARN=0;
            egg.egg3_life-=1;
            egg.egg_stock+=1;
            harvestsound3->play();
        }
        eggmove();
    }
////////////////////////////////第四处鸡窝
    if(doge.doge_X>=1000&&doge.doge_X<=1110){
        if(egg.egg4_life>0){
            WARN=0;
            egg.egg4_life-=1;
            egg.egg_stock+=1;
            harvestsound3->play();
        }
        eggmove();
    }
}

void battle3::eggmove()//鸡蛋动画
{
////////////////////////////////////////////////第一处鸡窝的鸡蛋
    if(egg.egg1_life==5){//如果生命值为5
        egg.egg1_change(egg.egg_5);//换为5个鸡蛋的图片
        egg.egg_X=400;
    }
    else if(egg.egg1_life==4){
        egg.egg1_change(egg.egg_4);
        egg.egg_X=400;
    }
    else if(egg.egg1_life==3){
        egg.egg1_change(egg.egg_3);
        egg.egg_X=400;
    }
    else if(egg.egg1_life==2){
        egg.egg1_change(egg.egg_2);
        egg.egg_X=400;
    }
    else if(egg.egg1_life==1){
        egg.egg1_change(egg.egg_1);
        egg.egg_X=400;
    }
    else if(egg.egg1_life==0){
        egg.egg_X=1600;
    }
////////////////////////////////////////////////第二处鸡窝的鸡蛋
    if(egg.egg2_life==5){//如果生命值为5
        egg.egg2_change(egg.egg_5);//换为5个鸡蛋的图片
        egg.egg2_X=609;
    }
    else if(egg.egg2_life==4){
        egg.egg2_change(egg.egg_4);
        egg.egg2_X=609;
    }
    else if(egg.egg2_life==3){
        egg.egg2_change(egg.egg_3);
        egg.egg2_X=609;
    }
    else if(egg.egg2_life==2){
        egg.egg2_change(egg.egg_2);
        egg.egg2_X=609;
    }
    else if(egg.egg2_life==1){
        egg.egg2_change(egg.egg_1);
        egg.egg2_X=609;
    }
    else{
        egg.egg2_X=1600;
    }
////////////////////////////////////////////////第二处鸡窝的鸡蛋
    if(egg.egg3_life==5){//如果生命值为5
        egg.egg3_change(egg.egg_5);//换为5个鸡蛋的图片
        egg.egg3_X=818;
    }
    else if(egg.egg3_life==4){
        egg.egg3_change(egg.egg_4);
        egg.egg3_X=818;
    }
    else if(egg.egg3_life==3){
        egg.egg3_change(egg.egg_3);
        egg.egg3_X=818;
    }
    else if(egg.egg3_life==2){
        egg.egg3_change(egg.egg_2);
        egg.egg3_X=818;
    }
    else if(egg.egg3_life==1){
        egg.egg3_change(egg.egg_1);
        egg.egg3_X=818;
    }
    else{
        egg.egg3_X=1600;
    }
////////////////////////////////////////////////第二处鸡窝的鸡蛋
    if(egg.egg4_life==5){//如果生命值为5
        egg.egg4_change(egg.egg_5);//换为5个鸡蛋的图片
        egg.egg4_X=1027;
    }
    else if(egg.egg4_life==4){
        egg.egg4_change(egg.egg_4);
        egg.egg4_X=1027;
    }
    else if(egg.egg4_life==3){
        egg.egg4_change(egg.egg_3);
        egg.egg4_X=1027;
    }
    else if(egg.egg4_life==2){
        egg.egg4_change(egg.egg_2);
        egg.egg4_X=1027;
    }
    else if(egg.egg4_life==1){
        egg.egg4_change(egg.egg_1);
        egg.egg4_X=1027;
    }
    else{
        egg.egg4_X=1600;
    }
}

void battle3::eggreborn()//鸡蛋生产
{
/////////////////////////////////////////////第一处鸡

    if(hen.hen1_Y>450&&egg.egg1_life<5){
            egg.egg1_life+=1;
            eggdrop->play();
    }
/////////////////////////////////////////////第二处鸡
    if(hen.hen2_Y>450&&egg.egg2_life<5){
            egg.egg2_life+=1;
            eggdrop->play();
    }
/////////////////////////////////////////////第三处鸡
    if(hen.hen3_Y>450&&egg.egg3_life<5){
            egg.egg3_life+=1;
            eggdrop->play();
    }
/////////////////////////////////////////////第四处鸡
    if(hen.hen4_Y>450&&egg.egg4_life<5){
            egg.egg4_life+=1;
            eggdrop->play();
    }
}



void battle3::paintEvent(QPaintEvent *)// 绘图事件
{
    QPainter painter(this);
    QPixmap battle3;
    battle3.load(":/res/battle3");

    //绘制天空
    painter.drawPixmap(sky.sky_x,0,1600,900,sky.day_init);
    //绘制天空物件
    painter.drawPixmap(sun.sun_x,sun.sun_y,400,400,sun.sun_init);
    //绘制围栏
    painter.drawPixmap(0,-35,1600,900,doge.fence);

    painter.drawPixmap(0,0,1600,900,battle3);//绘制场景

    painter.drawPixmap(egg.egg_X,500,170,95,egg.egg1_init);//绘制鸡蛋
    painter.drawPixmap(egg.egg2_X,500,170,95,egg.egg2_init);
    painter.drawPixmap(egg.egg3_X,500,170,95,egg.egg3_init);
    painter.drawPixmap(egg.egg4_X,500,170,95,egg.egg4_init);

    painter.drawPixmap(415,hen.hen1_Y,160,150,hen.hen1_init);//绘制鸡
    painter.drawPixmap(625,hen.hen2_Y,160,150,hen.hen2_init);//绘制鸡
    painter.drawPixmap(833,hen.hen3_Y,160,150,hen.hen3_init);//绘制鸡
    painter.drawPixmap(1042,hen.hen4_Y,160,150,hen.hen4_init);//绘制鸡

    painter.drawPixmap(340,503,300,120,henhouse.henhouse114);//绘制鸡窝
    painter.drawPixmap(549,503,300,120,henhouse.henhouse114);
    painter.drawPixmap(758,503,300,120,henhouse.henhouse114);
    painter.drawPixmap(967,503,300,120,henhouse.henhouse114);

    //绘制库存图标
    painter.drawPixmap(-20,2,70,45,wheat.wheatinstock);//小麦
    painter.drawPixmap(0,30,60,70,fruit.fruit_init);//果实
    painter.drawPixmap(-78,75,200,100,egg.egg_1);//鸡蛋

    painter.drawPixmap(doge.doge_X,532,120,120,doge.doge_0);//绘制初始狗头


}
///显示库存数量的实现
void battle3::inthestock3()
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
void battle3::theaim3()
{
        //目标小麦数量
        wheat_aim_label->setParent(this);
        QString wheat_aim_string = QString::number(wheat.wheat_aim);
        QFont aimfont("黑体",25,25,1);
        wheat_aim_label->setText("目标:"+wheat_aim_string);
        wheat_aim_label->setFont(aimfont);
        wheat_aim_label->move(160,-25);
        wheat_aim_label->setFixedSize(400,100);

        //目标果实d数量
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
void battle3::keyPressEvent(QKeyEvent * event)//键盘按下事件
{
    switch (event->key()) {
        case Qt::Key_A://左移
        case Qt::Key_D://右移
            keyrepeat3.append(event->key());
            break;
        case Qt::Key_J:eggharvest();
            break;
        }
}

void battle3::keyReleaseEvent(QKeyEvent *event)//键盘松开
{
        if(keyrepeat3.contains(event->key())){
            keyrepeat3.removeOne(event->key());
        }
}

