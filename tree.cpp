#include "tree.h"

tree::tree()
{
    //加载未被收获的果树
    tree_not_harvested.load(":/res/tree_full");

    //加载初始果树
    tree1_init.load(":/res/tree_full");
    tree2_init.load(":/res/tree_full");
    tree3_init.load(":/res/tree_full");

    //加载正在收获的果树
    tree_under_harvest1.load(":res/tree_full_under_harvest");
    tree_under_harvest2.load(":res/tree_full_under_harvest2");

    //加载收获完的果树
    tree_harvested.load(":res/tree");

}

void tree::tree1_change(QPixmap x)
{
    tree1_init = x;
}

void tree::tree2_change(QPixmap x)
{
    tree2_init = x;
}

void tree::tree3_change(QPixmap x)
{
    tree3_init = x;
}
