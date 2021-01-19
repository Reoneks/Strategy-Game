#ifndef MAGIC_H
#define MAGIC_H
#include "cheats.h"
#include <QString>
#include <QVector>
#include <QDebug>
#include <qrandom.h>
class Magic:public Cheats{
public:
    Magic();
    /********************************************
     * Массив для благословлений/проклятий      *
     *------------------------------------------*
     *  0) Id благословления/проклятья          *
     *  1) Id юнита                             *
     *  2) Количество ходов                     *
     *  3) Сила эффекта                         *
     ********************************************/
    QVector<QVector<int>>BufsOrDebufs;
    int WhatMagic(int magic);
    QString WhatMagicName(int magic);
    QString WhatType(int magic);
    QVector<QString>Defence(int id);
    QVector<QString>FireArrow(int id);
};
#endif // MAGIC_H
