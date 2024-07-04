#ifndef TREE_H
#define TREE_H

#include<QPixmap>

class tree
{
public:
    tree();

    void tree1_change(QPixmap x);
    void tree2_change(QPixmap x);
    void tree3_change(QPixmap x);



    //设置果树声明值
    int tree1_life;
    int tree2_life;
    int tree3_life;

    //设置果树回复值
    int tree1_reborn;
    int tree2_reborn;
    int tree3_reborn;

    //果实库存
    int fruit_stock;

    //设置每年的目标
    int fruit_aim;

    //绘制未被收获的果树
    QPixmap tree_not_harvested;

    //绘制正在被收获的果树
    QPixmap tree_under_harvest1;
    QPixmap tree_under_harvest2;

    //绘制已被收获的果树
    QPixmap tree_harvested;

    //绘制果树中间值
    QPixmap tree1_init;
    QPixmap tree2_init;
    QPixmap tree3_init;
};

#endif // TREE_H
