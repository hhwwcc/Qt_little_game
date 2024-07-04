#include "battle.h"

#include<QPushButton>
#include <QKeyEvent>
#include<stdio.h>



battle::battle(QWidget *parent)
    : QWidget{parent}
{
    //设置战斗场景大小
    this->setFixedSize(1600,900);
    this->setWindowTitle("战斗");
    this->setWindowIcon(QIcon(":res/wheat_not_harvested.png"));
    //创建手动收获按钮
    QPushButton* handharvest=new QPushButton;
    handharvest->setIconSize(QSize(150,150));
    handharvest->setParent(this);
    handharvest->setText("手动收获");
    handharvest->move(5000,700);
    handharvest->setFixedSize(150,150);

//    //手动收获
//    connect(handharvest,&QPushButton::clicked,[=](){
//        for(int i=0;i<10;i++){//一个for循环十次相当于单次自动收获的十倍收益
//            dotheharvest();//进行一次收获动作
//        }
//    });

    //设置背景音乐
    backgroundmusic->setSource(QUrl::fromLocalFile(":res/sound/backgroundmusic.wav"));
    backgroundmusic->setLoopCount(QSoundEffect::Infinite);
    backgroundmusic->setVolume(100);

    //设置收获音效
    harvestsound->setSource(QUrl::fromLocalFile(":res/sound/harvestsound.wav"));//收获小麦
    harvestsound->setVolume(200);
    harvestsound->setLoopCount(1);

    //设置走路音效
    movesound->setSource(QUrl::fromLocalFile(":res/sound/move2.wav"));
    backgroundmusic->setVolume(50);
    movesound->setLoopCount(1);

    //设置农药音效
    insect_killer_sound->setSource(QUrl::fromLocalFile(":res/sound/insect_killer.wav"));
    insect_killer_sound->setLoopCount(1);

    //蝗虫音效
    locust_come->setSource(QUrl::fromLocalFile(":res/sound/locust.wav"));
    locust_die->setSource((QUrl::fromLocalFile(":res/sound/locust_die.wav")));
    locust_come->setLoopCount(1);
    locust_die->setLoopCount(1);

    //连接battle2传来的信号
    connect(this->battlescene2,&battle2::backtobattlefrombattle2,[=](){
        this->btbfb2();
    });

    //连接battle3传来的信号
    connect(this->battlescene3,&battle3::backtobattlefrombattle3,[=](){
        this->btbfb3();
    });

}

void battle::battlescene2_init()//初始化场景2
{
    battlescene2->init2();
}

//初始化游戏的实现
void battle::Initbattlescene(){

    //天空初始值
    sky_switch=1;
    sky.sky_change(sky.day_change);
    sun.sun_move(doge.sun_change_figure);
    sun_to_moon=0;//天空变化值
    locust_action=0;//蝗虫动画值
//    doge.locust_life=16;//初始蝗虫生命值
    doge.locust_Y=-200;

    sun.sun_x=1600;
    sun.sun_y=700;




    //初始化狗头
    doge.doge_X = 200;
    //初始化小麦生命值
     wheat.life1 = 25;
     wheat.life2 = 25;
     wheat.life3 = 25;
     wheat.life4 = 25;
     wheat.life5 = 25;

    //初始化恢复累加值的初始值
     wheat.toreborn1 = 0;
     wheat.toreborn2 = 0;
     wheat.toreborn3 = 0;
     wheat.toreborn4 = 0;
     wheat.toreborn5 = 0;

    //初始化库存
     wheat.wheat_stock = 0;
     tree.fruit_stock = 0;
     egg.egg_stock = 0;
    //初始化目标
     wheat.wheat_aim = 12;
     tree.fruit_aim = 45;
     egg.egg_aim = 3;
    //初始化倒计时
     wheat.time_remain = 20;
     qDebug()<<"初始化";
     //初始化关卡等级
     wheat.current_level = 0;

     //初始化小麦图片
     wheat.wheat_change1(wheat.wheat_not_harvested);
     wheat.wheat_change2(wheat.wheat_not_harvested);
     wheat.wheat_change3(wheat.wheat_not_harvested);
     wheat.wheat_change4(wheat.wheat_not_harvested);
     wheat.wheat_change5(wheat.wheat_not_harvested);

     //初始化移动按键链表
     KeyRepeat.clear();
     //初始化自动收获按键链表
     wheatgotoharvest.clear();

     //初始化背景音
     backgroundsound->setSource(QUrl::fromLocalFile(":res/sound/backgroundsound.wav"));//设置本地资源
     backgroundsound->setLoopCount(QSoundEffect::Infinite);//播放次数为无限制循环
     backgroundsound->play();//开始播放

     //初始化背景音乐
     backgroundmusic->play();
}

//绘图事件
void battle::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap scene;
    scene.load(":/res/battle");

    //绘制天空
    painter.drawPixmap(sky.sky_x,0,1600,900,sky.day_init);

    //绘制天空物件
    painter.drawPixmap(sun.sun_x,sun.sun_y,400,400,sun.sun_init);//太阳

    //绘制初始小麦
    painter.drawPixmap(320,449,300,200,wheat.wheat_1_0);
    painter.drawPixmap(570,449,300,200,wheat.wheat_2_0);
    painter.drawPixmap(820,449,300,200,wheat.wheat_3_0);
    painter.drawPixmap(1070,449,300,200,wheat.wheat_4_0);
    painter.drawPixmap(1320,449,300,200,wheat.wheat_5_0);

    //绘制蝗虫
    painter.drawPixmap(doge.locust_X,doge.locust_Y,120,120,doge.locust_init);

    //注意图层的顺序，先运行的代码会先绘制
    painter.drawPixmap(0,0,1600,900,scene);//绘制场景

    //绘制库存图标
    painter.drawPixmap(-20,2,70,45,wheat.wheatinstock);//小麦
    painter.drawPixmap(0,30,60,70,fruit.fruit_init);//果实
    painter.drawPixmap(-78,75,200,100,egg.egg_1);//鸡蛋


    painter.drawPixmap(doge.insect_killer_X,400,350,350,doge.insect_killer);//绘制初始狗头
    painter.drawPixmap(doge.doge_X,532,120,120,doge.doge_0);//绘制初始狗头

}

//计时器的实现
void battle::playGame()
{
    //检测场景变化的定时器
    m_Timer.start(1);//场景刷新为每毫秒一次
    //监听定时器发送的信号
    connect(&m_Timer , &QTimer::timeout,[=](){

        //定时器实时更新元素
        update();
        //更新库存
        /////////////////小麦的库存
        battlescene2->wheat.wheat_stock=wheat.wheat_stock;//场景二的小麦库存由中间场景同步过来
        battlescene3->wheat.wheat_stock=wheat.wheat_stock;//场景三的小麦库存由中间场景同步过来
        ////////////////果实的库存
        tree.fruit_stock=battlescene2->tree.fruit_stock;//果实库存由场景二同步到中间场景
        battlescene3->tree.fruit_stock=battlescene2->tree.fruit_stock;//果实库存由场景二同步到场景三
        ////////////////鸡蛋的库存
        egg.egg_stock=battlescene3->egg.egg_stock;//鸡蛋库存由场景三同步到中间场景
        battlescene2->egg.egg_stock=battlescene3->egg.egg_stock;//鸡蛋库存由场景三同步到场景二

        //更新目标
        /////////////小麦的目标
        battlescene2->wheat.wheat_aim=wheat.wheat_aim;//场景二的小麦目标由中间场景同步过来
        battlescene3->wheat.wheat_aim=wheat.wheat_aim;//场景三的小麦目标由中间场景同步过来
        ////////////果实的目标
        tree.fruit_aim=battlescene2->tree.fruit_aim;//果实目标由场景二同步到中间场景
        battlescene3->tree.fruit_aim=battlescene2->tree.fruit_aim;//果实目标由场景二同步到场景三
        ///////////鸡蛋的目标
        egg.egg_aim=battlescene3->egg.egg_aim;//鸡蛋目标由场景三同步到中间场景
        battlescene2->egg.egg_aim=battlescene3->egg.egg_aim;//鸡蛋目标由场景三同步到场景二


        //同步天空
        battlescene2->sky.day_init=sky.day_init;//中间场景天空同步到场景二天空
        battlescene3->sky.day_init=sky.day_init;//中间场景天空同步到场景三天空

        //同步天空物件
        battlescene2->sun.sun_x=sun.sun_x;//同步太阳
        battlescene2->sun.sun_y=sun.sun_y;
        battlescene3->sun.sun_x=sun.sun_x;
        battlescene3->sun.sun_y=sun.sun_y;

        battlescene2->sun.sun_init=sun.sun_init;
        battlescene3->sun.sun_init=sun.sun_init;//同步月亮

        //同步时间值
        battlescene2->sky_switch=sky_switch;

////////////////////////////左边场景基本刷新
        battlescene2->update();//刷新场景
        battlescene2->inthestock2();//库存
        battlescene2->theaim2();//目标
        battlescene2->nextlevel2();//下一目标

        battlescene2->fruitdrop();//果实坠落
        ////////////////////////游戏外限制猴子移动，停止开关被打开，猴子被锁定在-200的位置
            if(monkey_stop==0){
                battlescene2->invader();//左边场景入侵者
            }
            else{
                battlescene2->doge.monkey_X=-200;//停止开关关闭，猴子开始移动
            }

        battlescene2->fruitdrop_invader();//入侵者的果实坠落
        battlescene2->bark();//驱赶入侵者动画


        battlescene2->bark_voice_hide();//监听音效的图片

        ///////////////////中间场景动画
        locust_show_up();//蝗虫
        insect_killer_hide();//农药停留时间


    });

    //检测狗头移动的定时器
    key_timer = new QTimer(this);
    key_timer->start(6);//狗头移动的速度为每6毫秒变化一次位置
    connect(key_timer,&QTimer::timeout,[=](){
        /////////中间场景
        DogeMove();
        dogemovesound();
        //////////左边场景
        battlescene2->dogemove2();//移动
        battlescene2->dogemovesound2();//移动音效
        battlescene2->dogebounce2();//碰撞
    });


    //检测自动收获动作的定时器
    wheat_gotoharvest = new QTimer(this);
    wheat_gotoharvest->start(20);//按住收获键J自动收获频率为20ms
    connect(wheat_gotoharvest,&QTimer::timeout,[=](){
        autoharvest();//自动收获

        ///////////左边场景定时器
        battlescene2->invader_harvest_judge();//入侵者收获速度
        /////////////////果树收获
        battlescene2->keyfruitharvest();//收获

    });

    //重新长出的定时器
    wheat_Timer = new QTimer(this);
    wheat_Timer->start(1000);//检测的频率为小麦每1秒恢复1点生命
    connect(wheat_Timer,&QTimer::timeout,[=](){
        reborn();//重新长出小麦
        locust_harvest();//判定蝗虫收获小麦
        battlescene2->treereborn();//重新长出果实
//        qDebug()<<battlescene2->doge.monkey_X;
//        qDebug()<<monkey_stop;
    });

    //刷新库存的定时器
    stock_Timer = new QTimer(this);
    stock_Timer->start(10);
    connect(stock_Timer,&QTimer::timeout,[=](){
        inthestock();//库存数量
        theaim();//目标
        currentlevel();//当前关卡等级
        sun_change();//太阳


    });

    //关卡等级倒计时刷新的定时器
    level_Timer = new QTimer(this);
    level_Timer->start(1000);//每秒刷新一次倒计时
    connect(level_Timer,&QTimer::timeout,[=](){
        nextlevel();//下一等级关卡
        sky_change_1();//昼夜交替

    });

}

//自动收获的实现
void battle::autoharvest()
{

        for(int KeyCode : wheatgotoharvest){
            switch (KeyCode) {
                case Qt::Key_J:
//                for(int i=0; i<5; i++){
                    dotheharvest();//进行一次收获动作
//                    }

                    break;
//                case Qt::Key_K:
//                dotheharvest();//键盘K键执行手动收获动作
//                    break;
                }
        }


}

//小麦重新长出的实现
void battle::reborn()
{
        //第一处小麦
        if(wheat.life1==0&&wheat.toreborn1<10){//此时小麦生命值为0，累加值toreborn1小于10
                wheat.toreborn1+=1;//则累加1
        }
        else if(wheat.toreborn1==10){//当累加到10的时候
                wheat.life1=25;//恢复小麦生命值为25
                wheat.wheat_change1(wheat.wheat_not_harvested);//变成未收获的小麦的图片
                wheat.toreborn1=0;//重置累加为0
        }
        //第二处小麦
        if(wheat.life2==0&&wheat.toreborn2<10){//此时小麦生命值为0，累加值toreborn2小于10
                wheat.toreborn2+=1;//则累加1
        }
        else if(wheat.toreborn2==10){//当累加到10的时候
                wheat.life2=25;//恢复小麦生命值为25
                wheat.wheat_change2(wheat.wheat_not_harvested);
                wheat.toreborn2=0;//重置累加为0
        }
        //第三处小麦
        if(wheat.life3==0&&wheat.toreborn3<10){//此时小麦生命值为0，累加值toreborn3小于10
                wheat.toreborn3+=1;//则累加1
        }
        else if(wheat.toreborn3==10){//当累加到10的时候
                wheat.life3=25;//恢复小麦生命值为25
                wheat.wheat_change3(wheat.wheat_not_harvested);
                wheat.toreborn3=0;//重置累加为0
        }
        //第四处小麦
        if(wheat.life4==0&&wheat.toreborn4<10){//此时小麦生命值为0，累加值toreborn4小于10
                wheat.toreborn4+=1;//则累加1
        }
        else if(wheat.toreborn4==10){//当累加到10的时候
                wheat.life4=25;//恢复小麦生命值为25
                wheat.wheat_change4(wheat.wheat_not_harvested);
                wheat.toreborn4=0;//重置累加为0
        }
        //第五处小麦
        if(wheat.life5==0&&wheat.toreborn5<10){//此时小麦生命值为0，累加值toreborn5小于10
                wheat.toreborn5+=1;//则累加1
        }
        else if(wheat.toreborn5==10){//当累加到10的时候
                wheat.life5=25;//恢复小麦生命值为25
                wheat.wheat_change5(wheat.wheat_not_harvested);
                wheat.toreborn5=0;//重置累加为0
        }
}

///显示库存数量的实现
void battle::inthestock()
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
void battle::theaim()
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

///当前关卡等级的实现
void battle::currentlevel()
{
        currentL->setParent(this);
        QString CL = QString::number(wheat.current_level);
        QFont CLFont("黑体",50,50,1);
        currentL->setText("第"+CL+"年");
        currentL->setFont(CLFont);
        currentL->move(1200,-10);
        currentL->setFixedSize(400,100);

}

///进入下一关卡等级倒计时的实现
void battle::nextlevel()
{
        time_remain->setParent(this);
        QString timeremain = QString::number(wheat.time_remain);
        QFont font("黑体",50,50,1);
        time_remain->setText("下一年:"+timeremain);
        time_remain->setFont(font);
        time_remain->move(530,-10);
        time_remain->setFixedSize(400,100);
        if(wheat.time_remain>=0){//如果剩余时间大于等于0
                wheat.time_remain-=1;//则计时器减少一秒
        }
        if(wheat.time_remain<0&&wheat.wheat_stock>=wheat.wheat_aim&&tree.fruit_stock>=tree.fruit_aim&&egg.egg_stock>=egg.egg_aim){//如果剩余时间为0且库存大于等于目标

            //则库存减去目标，游戏继续
            wheat.wheat_stock-=wheat.wheat_aim;
            battlescene2->tree.fruit_stock-=tree.fruit_aim;//场景2更新的的数据同步到中间场景
            battlescene3->egg.egg_stock-=egg.egg_aim;//场景3更新的的数据同步到中间场景



            //刷新蝗虫
            if(doge.locust_life<=0){//蝗虫死亡后才会刷新
                invader_locust();
            }
            //时间重置为20秒
            wheat.time_remain=20;

            //下一级关卡等级目标提高
            wheat.wheat_aim+=20;
            battlescene2->tree.fruit_aim+=30;
            battlescene3->egg.egg_aim+=3;

            //累加一年
            wheat.current_level+=1;
        }
        if(wheat.time_remain<0&&wheat.wheat_stock<wheat.wheat_aim){//如果剩余时间为0且小麦库存小于目标
            end();
            wheat.time_remain=9999;
        }
        if(wheat.time_remain<0&&tree.fruit_stock<tree.fruit_aim){//如果剩余时间为0且果实库存小于目标
            end();
            wheat.time_remain=9999;
        }
        if(wheat.time_remain<0&&egg.egg_stock<egg.egg_aim){//如果剩余时间为0且果实库存小于目标
            end();
            wheat.time_remain=9999;
        }
}

//背景天空的变化
void battle::sky_change_1()
{
    if(wheat.time_remain==20){
        if(sky_switch==1){
            sky.sky_change(sky.day_change);//日出
            //重置太阳位置
            sun.sun_move(doge.sun_change_figure);
            sun.sun_x=1600;
            sun.sun_y=700;
        }
        else{
            sky.sky_change(sky.night_change);//夜出
            //重置太阳位置
            sun.sun_move(moon.moon_init);
            sun.sun_x=1600;
            sun.sun_y=700;

        }
    }
    if(wheat.time_remain==17){
        if(sky_switch==1){
            sky.sky_change(sky.day);//白天
        }
        else{
            sky.sky_change(sky.night);//夜晚
        }
    }
    if(wheat.time_remain==2){
        if(sky_switch==1){
            sky.sky_change(sky.day_change);//日落
            sky_switch=2;

        }
        else{
            sky.sky_change(sky.night_change);//夜落
            sky_switch=1;
        }
    }

}

//太阳/月亮移动
void battle::sun_change()
{
    ///////////////太阳月亮移动逻辑
    if(sun.sun_x<=1600&&sun.sun_x>600){
        sun.sun_x-=1;
        double num = sqrt((1000*1000)-((sun.sun_x-600)*(sun.sun_x-600)));
        sun.sun_y=900-num;
    }
    if(sun.sun_x<=600&&sun.sun_x>-400){
        sun.sun_x-=1;
        double num = sqrt((1000*1000)-((600-sun.sun_x)*(600-sun.sun_x)));
        sun.sun_y=900-num;
    }
}

void battle::invader_locust()//蝗虫出现
{
        //////////////刷新蝗虫
        locust_come->play();
        doge.locust_life=16;
        doge.locust_Y=-200;
        place = qrand()%4;
//        qDebug()<<place;
        if(place==0){//如果位置值为0则分配到第一处小麦
            doge.locust_X=360;
        }
        if(place==1){
            doge.locust_X=610;
        }
        if(place==2){
            doge.locust_X=860;
        }
        if(place==3){
            doge.locust_X=1110;
        }
        if(place==4){
            doge.locust_X=1360;
        }
}

void battle::locust_show_up()//蝗虫动画
{
    if(doge.locust_Y>=-200&&doge.locust_Y<=532){
        doge.locust_Y+=1;
        if(locust_action==0){
            locust_action=1;
            doge.locust_X+=10;
//            qDebug()<<"move";
        }
        else if(locust_action==1){
            locust_action=0;
            doge.locust_X-=10;
//            qDebug()<<"move2";
        }

    }
    if(doge.locust_life==0){//若生命为0则移出蝗虫
        doge.locust_life-=5;
        doge.locust_Y=1000;
        locust_die->play();
    }
}

void battle::locust_harvest()//蝗虫收获判定
{
    /////////////刷新蝗虫之前先进行一次判定是否可以窃取小麦
    if(place==0&&doge.locust_life>0){//蝗虫存活
        if(wheat.life1>0){//如果有剩余的小麦则窃取
            wheat.life1-=1;
        }
        else if(wheat.life1==0){//如果无剩余则收获完毕
            wheat.life1-=1;
//            qDebug()<<"finish";
            wheat.wheat_change1(wheat.wheat_harvested);
        }
    }
    if(place==1&&doge.locust_life>0){
        if(wheat.life2>0){
            wheat.life2-=1;
//            qDebug()<<"finish";
        }
        else if(wheat.life2==0){//如果无剩余则收获完毕
//            qDebug()<<"finish";
            wheat.life2-=1;
            wheat.wheat_change2(wheat.wheat_harvested);
        }
    }
    if(place==2&&doge.locust_life>0){
        if(wheat.life3>0){
            wheat.life3-=1;
        }
       else if(wheat.life3==0){//如果无剩余则收获完毕
            wheat.life3-=1;
//            qDebug()<<"finish";
            wheat.wheat_change3(wheat.wheat_harvested);
        }
    }
    if(place==3&&doge.locust_life>0){
        if(wheat.life4>0){
            wheat.life4-=1;
        }
        else if(wheat.life4==0){//如果无剩余则收获完毕
                wheat.life4-=1;
//                qDebug()<<"finish";
                wheat.wheat_change4(wheat.wheat_harvested);
        }
    }
    if(place==4&&doge.locust_life>0){
        if(wheat.life5>0){
            wheat.life5-=1;
        }
        else if(wheat.life5==0){//如果无剩余则收获完毕
            wheat.life5-=1;
//            qDebug()<<"finish";
            wheat.wheat_change5(wheat.wheat_harvested);
        }

    }
}

void battle::insect_killer_show_up()//显示农药
{
    doge.insect_killer_X=doge.doge_X-100;
    insect_killer_left=0;
}

void battle::insect_killer_hide()//隐藏农药
{

    if(insect_killer_left<15){//15毫秒后移出农药
        insect_killer_left+=1;
    }
    else{
        doge.insect_killer_X=1600;
        insect_killer_left=0;
    }
}

//从场景2回到场景1的实现
void battle::btbfb2()
{
        this->show();
}
//从场景3回到场景1的实现
void battle::btbfb3()
{
    this->show();
}

void battle::end()//结束游戏
{
    //猴子停止移动
    monkey_stop=1;
   battlescene2->KeyRepeat2.clear();
   battlescene2->HarvestRepeat.clear();
   KeyRepeat.clear();
   wheatgotoharvest.clear();
   battlescene3->keyrepeat3.clear();


    backgroundsound->stop();//停止背景音
    backgroundmusic->stop();//停止音乐
    this->close();
    battlescene2->hide();//关闭所有场景
    battlescene3->hide();

    battlescene3->key_Timer3->stop();
    battlescene3->egg_timer->stop();
    battlescene3->m3_Timer.stop();

    battlescene2->playgame2();//初始化所有场景
    battlescene3->playgame3();
    //回到主菜单
    BackToTitle();

}

//收获动作的实现
void battle::dotheharvest()
{
        //第一处小麦
        if(doge.doge_X<=510&&doge.doge_X>=260){
                if(wheat.life1<=25&&wheat.life1>1){//如果该处小麦大于1点生命则减少小麦1点生命
                    wheat.life1 -= 1;
                    wheat.wheat_stock +=1;//此时库存增添1单位的小麦
                    harvestsound->play();//播放一次收获音效
                    if(wheat.life1%3==0){
                        wheat.wheat_change1(wheat.wheat_under_harvest1);//被3整除余0更换问正在收获的小麦图片1

                    }
                    else if(wheat.life1%3==2){
                        wheat.wheat_change1(wheat.wheat_under_harvest2);//被3整除余2更换问正在收获的小麦图片2

                    }
                    else if(wheat.life1%3==1){
                        wheat.wheat_change1(wheat.wheat_under_harvest3);//被3整除余1更换问正在收获的小麦图片3，如此循环可表现动态收获
                    }
                }
                else if(wheat.life1==1){//如果该处小麦只剩1点生命则减少1点生命并换成收获完毕的图片
                    harvestsound->play();
                    wheat.life1 -= 1;
                    wheat.wheat_change1(wheat.wheat_harvested);
                }
        }
        //第二处小麦
        if(doge.doge_X<=760&&doge.doge_X>=510){

                if(wheat.life2<=25&&wheat.life2>1){//如果该处小麦大于1点生命则减少小麦1点生命
                    harvestsound->play();
                    wheat.life2 -= 1;
                                        wheat.wheat_stock +=1;//此时库存增添1单位的小麦
                    if(wheat.life2%3==0){
                        wheat.wheat_change2(wheat.wheat_under_harvest1);//被3整除余0更换问正在收获的小麦图片1

                    }
                    else if(wheat.life2%3==2){
                        wheat.wheat_change2(wheat.wheat_under_harvest2);//被3整除余2更换问正在收获的小麦图片2

                    }
                    else if(wheat.life2%3==1){
                        wheat.wheat_change2(wheat.wheat_under_harvest3);//被3整除余1更换问正在收获的小麦图片3，如此循环可表现动态收获
                    }
                }
                else if(wheat.life2==1){
                    harvestsound->play();
                    wheat.life2 -= 1;

                    wheat.wheat_change2(wheat.wheat_harvested);
                }
        }
        //第三处小麦
        if(doge.doge_X<=1010&&doge.doge_X>=760){

                if(wheat.life3<=25&&wheat.life3>1){//如果该处小麦大于1点生命则减少小麦1点生命
                    harvestsound->play();
                    wheat.life3 -= 1;
                                        wheat.wheat_stock +=1;//此时库存增添1单位的小麦
                    if(wheat.life3%3==0){
                        wheat.wheat_change3(wheat.wheat_under_harvest1);//被3整除余0更换问正在收获的小麦图片1

                    }
                    else if(wheat.life3%3==2){
                        wheat.wheat_change3(wheat.wheat_under_harvest2);//被3整除余2更换问正在收获的小麦图片2

                    }
                    else if(wheat.life3%3==1){
                        wheat.wheat_change3(wheat.wheat_under_harvest3);//被3整除余1更换问正在收获的小麦图片3，如此循环可表现动态收获
                    }
                }
                else if(wheat.life3==1){
                    harvestsound->play();
                    wheat.life3 -= 1;

                    wheat.wheat_change3(wheat.wheat_harvested);
                }
        }
        //第四处小麦
        if(doge.doge_X<=1260&&doge.doge_X>=1010){

                if(wheat.life4<=25&&wheat.life4>1){//如果该处小麦大于1点生命则减少小麦1点生命
                    harvestsound->play();
                    wheat.life4 -= 1;
                                        wheat.wheat_stock +=1;//此时库存增添1单位的小麦
                    if(wheat.life4%3==0){
                        wheat.wheat_change4(wheat.wheat_under_harvest1);//被3整除余0更换问正在收获的小麦图片1

                    }
                    else if(wheat.life4%3==2){
                        wheat.wheat_change4(wheat.wheat_under_harvest2);//被3整除余2更换问正在收获的小麦图片2

                    }
                    else if(wheat.life4%3==1){
                        wheat.wheat_change4(wheat.wheat_under_harvest3);//被3整除余1更换问正在收获的小麦图片3，如此循环可表现动态收获
                    }
                }
                else if(wheat.life4==1){
                    harvestsound->play();
                    wheat.life4 -= 1;

                    wheat.wheat_change4(wheat.wheat_harvested);
                }
        }
        //第五处小麦
        if(doge.doge_X<=1510&&doge.doge_X>=1260){

                if(wheat.life5<=25&&wheat.life5>1){//如果该处小麦大于1点生命则减少小麦1点生命
                    harvestsound->play();
                    wheat.life5 -= 1;
                    wheat.wheat_stock +=1;//此时库存增添1单位的小麦
                    if(wheat.life5%3==0){
                        wheat.wheat_change5(wheat.wheat_under_harvest1);//被3整除余0更换问正在收获的小麦图片1

                    }
                    else if(wheat.life5%3==2){
                        wheat.wheat_change5(wheat.wheat_under_harvest2);//被3整除余2更换问正在收获的小麦图片2

                    }
                    else if(wheat.life5%3==1){
                        wheat.wheat_change5(wheat.wheat_under_harvest3);//被3整除余1更换问正在收获的小麦图片3，如此循环可表现动态收获
                    }
                }
                else if(wheat.life5==1){
                    harvestsound->play();
                    wheat.life5 -= 1;
                    wheat.wheat_change5(wheat.wheat_harvested);
                }
        }
}

//狗头的移动的实现
void battle::DogeMove()
{

    for(int KeyCode : KeyRepeat)//遍历链表内所有的按键
    {
        switch(KeyCode)
        {
        case Qt::Key_A:
            doge.move(-5);//每次变化位置的距离为每像素
            doge.change(doge.doge_1);
            if(doge.doge_X<=-120){//为防止狗头冲破场景设置了狗头完全离开场景后回调位置
                        KeyRepeat.clear();
                        wheatgotoharvest.clear();
                        this->hide();
                        battlescene2->show();//进入左边场景
            }
            break;
        case Qt::Key_D:
            doge.move(5);
            doge.change(doge.doge_2);
            if(doge.doge_X>=1600){
                        KeyRepeat.clear();
                        wheatgotoharvest.clear();
                        this->hide();
                        battlescene3->show();//进入右边场景
            }
            break;
        }

    }
}
//行走音效的实现
void battle::dogemovesound()
{
    if(doge.doge_X==100){
        movesound->play();
    }
    if(doge.doge_X==600){
        movesound->play();
    }
    if(doge.doge_X==1000){
        movesound->play();
    }
    if(doge.doge_X==1400){
        movesound->play();
    }
}
//键盘按下事件
void battle::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
        case Qt::Key_A://键盘A键向左走
        case Qt::Key_D://键盘B键向右走
            KeyRepeat.append(event->key());//用append函数能让按键后面再加一个按键，并存储到链表keyRepeat内
        break;

        case Qt::Key_J://键盘J键执行自动收获动作
            wheatgotoharvest.append(event->key());
        break;

        case Qt::Key_K:
            insect_killer_show_up();
            doge.locust_life-=1;
            insect_killer_sound->play();
            break;
    }
        if(KeyRepeat.contains(Qt::Key_A)){


    }
}
//键盘松开事件
void battle::keyReleaseEvent(QKeyEvent *event){
    if(KeyRepeat.contains(event->key()))
    {//keyRepeat是个布尔值，有或者无
            KeyRepeat.removeOne(event->key());//松开按键的时候移除链表内对应的按键组合
    }

    if(wheatgotoharvest.contains(event->key())){
            wheatgotoharvest.removeOne(event->key());
    }
}
