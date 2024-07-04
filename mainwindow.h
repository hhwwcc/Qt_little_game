#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPixmap>
#include<QLabel>
#include<QTimer>
#include<QPushButton>
#include"battle.h"

#include <QAbstractTableModel>
#include <QList>
#include <QDateTime>
#include <QTableView>

#include <QListWidget>
#include <QApplication>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    battle initbattle;


    //声明接收返回按钮的信号的函数
    void btt();
    void show_rank();

    int therecord;//存储最高记录
    int rowCount;//排行榜行数量
    void bt2_timer();//场景二的定时器

    void help_show();//显示帮助菜单
    QTimer* record_timer;//声明最高记录的定时器

    void paintEvent(QPaintEvent *);

    void rankinglist_declare();//声明排行榜


private:
    Ui::MainWindow *ui;
    //声明战斗场景
    battle* battlescene = new battle(NULL);
    //声明第二个场景
    battle2* battlescene2 = new battle2(NULL);
    //声明第三个场景
    battle3* battlescene3 = new battle3(NULL);

    QPixmap TitlePage;//主菜单背景图

    //开始按钮
    QPushButton * start = new QPushButton;
    //帮助按钮
    QPushButton * help_button = new QPushButton;
    //返回按钮
    QPushButton * back_button = new QPushButton;
    //排行榜按钮
    QPushButton * rankinglist_button = new QPushButton;

    //一个说明书的标签
    QLabel *help = new QLabel(this);
    //一个最高记录的标签
    QLabel *record = new QLabel(this);
    //一个排行榜的书签
    QLabel *rank_label = new QLabel(this);
};
#endif // MAINWINDOW_H

