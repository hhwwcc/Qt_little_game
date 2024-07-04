#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSql/QSqlDatabase>
#include<QtSql/QSqlError>
#include<QtSql/QSqlQuery>

#include<QPainter>
#include<QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


//    qDebug() << QSqlDatabase::drivers();//可以打印出当前qt支持的数据库环境，("QSQLITE", "QODBC", "QODBC3", "QPSQL", "QPSQL7")
//    其中QSQLITE是内置的数据库，不需要安装驱动，其他的都要安装驱动
    battlescene->playGame();

    ui->setupUi(this);
    //设置窗口大小
    this->setFixedSize(1600,900);
    this->setWindowTitle("主选单");
    this->setWindowIcon(QIcon(":/res/wheat_not_harvested.png"));

    //创建开始按钮
    start->setFocusPolicy(Qt::NoFocus);//这样该按钮就无法接收键盘事件了
    start->setParent(this);
    start->setText("开 始");
    start->setFixedSize(230,70);
    start->move(100,600);
    QFont font("黑体",40,20,1);
    start->setFont(font);

    //创建帮助按钮
    help_button->setFocusPolicy(Qt::NoFocus);//这样该按钮就无法接收键盘事件了
    help_button->setParent(this);
    help_button->setText("帮 助");
    help_button->setFixedSize(230,70);
    help_button->move(100,700);
    help_button->setFont(font);

    //创建返回按钮
    back_button->setFocusPolicy(Qt::NoFocus);//这样该按钮就无法接收键盘事件了
    back_button->setParent(this);
    back_button->setText("返 回");
    back_button->setFixedSize(200,70);
    back_button->move(1400,0);
    back_button->setFont(font);
    back_button->hide();

//    //创建排行榜按钮
//    rankinglist_button->setFocusPolicy(Qt::NoFocus);//这样该按钮就无法接收键盘事件了
//    rankinglist_button->setParent(this);
//    rankinglist_button->setText("排行榜");
//    rankinglist_button->setFixedSize(230,70);
//    rankinglist_button->move(100,800);
//    rankinglist_button->setFont(font);

    //帮助按钮显示帮助画面
    connect(help_button,&QPushButton::clicked,[=](){
        help_show();
        record->hide();

    });
    //排行榜按钮显示排行榜
    connect(rankinglist_button,&QPushButton::clicked,[=](){

    });

    //返回按钮回到主菜单
    connect(back_button,&QPushButton::clicked,[=](){
        record->show();
        start->show();
        help_button->show();
        rankinglist_button->show();
        back_button->hide();
        help->hide();
    });

    //开始按钮进入场景
    connect(start,&QPushButton::clicked,[=](){
        this->hide();
        battlescene->show();//显示战斗场景
        battlescene->Initbattlescene();//初始化游戏数据
        battlescene->invader_locust();
        battlescene->battlescene2_init();
        battlescene->monkey_stop=0;
    });


    //连接battle传来的信号
    connect(this->battlescene,&battle::BackToTitle,[=](){
        this->btt();
    });

    //帮助文本
    help->setParent(this);
    help->setFixedSize(1600,900);
    help->setText("   操作方式:  向左走:按A  向右走:按D  收获:靠近农作物按J  驱赶入侵者:按K\n"
                  "   游戏规则:在限定时间内收获足够目标的农作物即可继续游戏，一直到收获的农作物满足\n"
                  "不了今年的目标为止。\n"
                  "   贴士:果树和小麦只有在被收获完的状态才会开始生长，鸡蛋只有在鸡没有被拿起来的时\n"
                  "候才会生产,果园和麦田固定时间内会出现入侵者，他们会减少农作物的产量，所以需要尽\n"
                  "快赶走。在果园和麦田的驱赶方式不一样，当前场景只会触发当前场景的驱赶动作。\n"
                  "   游戏结束:记录生活的年数。\n"
                  "   设定: 在天界的一只小狗打算到凡间体验当农民的生活。他利用天上一日，地上一年\n"
                  "的规律很快就能等到凡间农作物成熟收获的时机，他日日夜夜地辛勤劳作，在体验完一次凡\n"
                  "间农场经营的兴衰以后，便会回到天界记下自己经营了多久的农场，总结经验，并再次回到\n"
                  "凡间重新开始经营。");
    QFont helpfont("黑体",15,15,0);
    help->setFont(helpfont);
    help->move(330,-265);
    help->hide();




//    //最高记录的计时器
//    record_timer = new QTimer(this);//通过 new 关键字来得到一个 QTimer 类的实例指针
//    record_timer->start(10);
//    connect(record_timer,&QTimer::timeout,[=](){

//    });

    ////////////////////暂时解决程序启动三次定时器的办法
//    battlescene2->m2_Timer.stop();
//    battlescene2->m2_Timer.stop();
//    qDebug()<<"sdtop";
//    battlescene2->key_Timer2->stop();battlescene2->key_Timer2->stop();
//    battlescene2->tree_harvest_timer->stop();battlescene2->tree_harvest_timer->stop();
//    battlescene2->tree_reborn_timer->stop();battlescene2->tree_reborn_timer->stop();
//    battlescene2->fruit_fall_timer->stop();battlescene2->fruit_fall_timer->stop();
//    battlescene3->m3_Timer.stop();battlescene3->m3_Timer.stop();
//    battlescene3->key_Timer3->stop();battlescene3->key_Timer3->stop();
//    battlescene3->egg_timer->stop();battlescene3->egg_timer->stop();


//////////////////////////连接到SQLite数据库应用程序启动时，连接到SQLite数据库。
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("game_records.db"); // 数据库文件名

        if (!db.open()) {
            qDebug() << "Error connecting to database:" << db.lastError().text();
        }
        else{
            qDebug()<<"连接到数据库";
        }
}

void MainWindow::paintEvent(QPaintEvent *){//绘图事件
    QPainter painter(this);
    TitlePage.load(":/res/title");
    painter.drawPixmap(0,0,1600,900,TitlePage);
}

void MainWindow::rankinglist_declare()
{
////////////////////////游戏历史记录的数据库
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS rank ("
                   "player_name TEXT NOT NULL,"
                   "score INTEGER NOT NULL,"
                   "completion_date TEXT NOT NULL)");


/////////////////////////插入新的游戏得分记录,每次玩家获得新的得分时，将记录插入到数据库中：
        QString playerName = "puppy"; // 从游戏逻辑中获取玩家名字
        int score = therecord; // 从游戏逻辑中获取得分
        QDateTime now = QDateTime::currentDateTime(); // 获取当前日期和时间
        // 使用自定义格式字符串
        QString format = "yyyy年MM月dd日hh时mm分ss秒";
        QString completionDate = now.toString(format);
        QSqlQuery insertQuery;

        insertQuery.prepare("INSERT INTO rank (player_name, score, completion_date) VALUES (:name, :score, :date)");
        insertQuery.bindValue(":name", playerName);
        insertQuery.bindValue(":score", score);
        insertQuery.bindValue(":date", completionDate);

        // 执行插入查询
        if (!insertQuery.exec()) {
            // 处理错误
            qDebug() << "插入错误: " << insertQuery.lastError().text();
        } else {
            qDebug() << "插入成功";
        }


/////////////////////////检索并列出所有游戏得分记录要检索并列出所有游戏得分记录：
        query.exec("SELECT * FROM rank");
        while (query.next()) {
            QString playerName = query.value(0).toString();
            int score = query.value(1).toInt();
            QString completionDate = query.value(2).toString();
            qDebug()  << "Player:" << playerName << "Score:" << score << "Complete date:"<< completionDate;
        }
            qDebug()<<"//////////////////\n";
        // 执行 SQL 查询以获取行数
            if (!query.exec("SELECT COUNT(*) FROM rank")) {
                qDebug() << "查询失败:" << query.lastError().text();
            }
        // 获取查询结果的第一行第一列（即 COUNT(*) 的结果）
            if (query.next()) {
                rowCount = query.value(0).toInt();
                qDebug() << "rank 表的行数量是:" << rowCount-1;

            }

}

//实现backtotitle的btt槽函数
void MainWindow::btt(){

    therecord = battlescene->wheat.current_level;//本局记录
    rankinglist_declare();//添加记录到数据库中
    //最高记录
    record->setParent(this);
    QString highestrecord =QString::number(therecord);
    record->setText("生活了"+highestrecord+"年");
    QFont HR("黑体",50,50,1);
    record->setFont(HR);
    record->setFixedSize(8000,800);
    record->move(700,100);

    this->show();
    record->show();
}

void MainWindow::help_show()//显示帮助
{
    QSqlQuery query;
//    query.exec("DELETE FROM rank WHERE score = (SELECT MIN(score) FROM rank)");
    query.exec("SELECT * FROM rank");
    while (query.next()) {
        QString playerName = query.value(0).toString();
        int score = query.value(1).toInt();
        QString completionDate = query.value(2).toString();
        qDebug()  << "Player:" << playerName << "Score:" << score << "Complete date:"<< completionDate;
    }
    record->hide();
    start->hide();
    help_button->hide();
    back_button->show();
    rankinglist_button->hide();
    help->show();
}



MainWindow::~MainWindow()
{
    delete ui;
}


