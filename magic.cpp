#include "magic.h"
Magic::Magic(){

}
int Magic::WhatMagic(int magic){
    switch(magic){
        case 1:return 4;
        case 2:return 1;
    }
    return -999;
}
QString Magic::WhatType(int magic){
    switch(magic){
        case 1:return "Поддержка";
        case 2:return "Урон";
    }
    return "ERROR";
}
QString Magic::WhatMagicName(int magic){
    switch(magic){
        case 1:return "Защита";
        case 2:return "Возгорание";
    }
    return "ERROR";
}



QVector<QString> Magic::Defence(int id){
    QVector<QString>Log;//Вектор для записи логов
    BufsOrDebufs[0]<<1;//ИД эффекта
    BufsOrDebufs[1]<<id;//ИД юнита
    BufsOrDebufs[2]<<2;//Длительность эффекта
    BufsOrDebufs[3]<<15;//Сила эффекта
    Stats[id][4]+=15;
    Log<<"Вы увеличили защиту юнита на 15 единиц";
    return Log;
}



QVector<QString> Magic::FireArrow(int id){
    QVector<QString>Log;//Вектор для записи логов
    Stats[id][1]-=40;
    Log<<"Вы нанесли 40 единиц урона";
    if(Stats[id][1]<=0){
        Log<<"Враг был убит!";
        for (int i=0;i<10;++i){
            Stats[id][i]=0;
        }
        return Log;
    }
    srand(time(nullptr));
    int chance=(rand()%100+1);
    if(chance<=30){
        BufsOrDebufs[0]<<2;//ИД эффекта
        BufsOrDebufs[1]<<id;//ИД юнита
        BufsOrDebufs[2]<<3;//Длительность эффекта
        BufsOrDebufs[3]<<10;//Сила эффекта
        Log<<"Вы повесили на врага эффект возгорания";
    }
    return Log;
}
