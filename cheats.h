#ifndef CHEATS_H
#define CHEATS_H
#include "game.h"
#include <QStringList>
class Cheats:public Game{
    void Heal(int id);
    void MaxHealthUp(int id,int Health);
    void DamageBoost(int id,int Damage);
    void DefenseBoost(int id, int Defense);
    void ComplexBoost(int id);
    void Kill(int id);
    void DebuffAll(int id);
    void StartNewGame(int GameMode);
    QString EnableCheats(QString password);
public:
    QString WhatCheatIsIt(QString arr);
    Cheats();
};

#endif // CHEATS_H
