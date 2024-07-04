#ifndef CHANGESCENE_H
#define CHANGESCENE_H

#include <QWidget>
#include "battle.h"
#include "battle2.h"
class changescene : public QWidget
{
    Q_OBJECT
public:
    explicit changescene(QWidget *parent = nullptr);


    battle* gotobattlefrombattle2 = new battle(NULL);
signals:

};

#endif // CHANGESCENE_H
