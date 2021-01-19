#include "cheats.h"
#include "game.h"
Cheats::Cheats(){
    CheatIsAllowed=false;
}
void Cheats::Heal(int id){
    if(CheatIsAllowed){
        Stats[id][1]=Stats[id][2];
    }
}
void Cheats::MaxHealthUp(int id,int Health){
    if(CheatIsAllowed){
        Stats[id][2]=Health;
        Stats[id][1]=Health;
    }
}
void Cheats::DamageBoost(int id,int Damage){
    if(CheatIsAllowed){
        Stats[id][3]=Damage;
    }
}
void Cheats::DefenseBoost(int id, int Defense){
    if(CheatIsAllowed){
        Stats[id][4]=Defense;
    }
}
void Cheats::ComplexBoost(int id){
    if(CheatIsAllowed){
        Stats[id][1]=10000;
        Stats[id][2]=10000;
        Stats[id][3]=10000;
        Stats[id][4]=10000;
    }
}
void Cheats::Kill(int id){
    if(CheatIsAllowed){
        Stats[id][0]=0;
        Stats[id][1]=0;
        Stats[id][2]=0;
        Stats[id][3]=0;
        Stats[id][4]=0;
        Stats[id][5]=0;
        Stats[id][6]=0;
    }
}
void Cheats::DebuffAll(int id){
    if(CheatIsAllowed){
        Stats[id][1]=1;
        Stats[id][2]=1;
        Stats[id][3]=0;
        Stats[id][4]=0;
        Stats[id][5]=1;
        Stats[id][6]=1;
    }
}
QString Cheats::WhatCheatIsIt(QString arr){
    QString Return=" ";
    QString NameOfCheat;
    NameOfCheat=arr.split(" ")[0];
    if(arr=="Start New Game 1"||arr=="Start New Game 0"){
        StartNewGame(arr.split(" ")[3].toInt());
        return  Return;
    }
    if(NameOfCheat=="Admin"||NameOfCheat=="admin")Return=EnableCheats(arr.split(" ")[1]);
    else if(NameOfCheat=="Heal"||NameOfCheat=="heal")Heal(arr.split(" ")[1].toInt());
    else if(NameOfCheat=="Kill"||NameOfCheat=="kill")Kill(arr.split(" ")[1].toInt());
    else if(NameOfCheat=="DebuffAll"||NameOfCheat=="debuffAll"||NameOfCheat=="Debuffall"||NameOfCheat=="debuffall")DebuffAll(arr.split(" ")[1].toInt());
    else if(NameOfCheat=="ComplexBoost"||NameOfCheat=="complexBoost"||NameOfCheat=="complexboost"||NameOfCheat=="Complexboost")ComplexBoost(arr.split(" ")[1].toInt());
    else if(NameOfCheat=="MaxHealthUp"||NameOfCheat=="maxHealthUp"||NameOfCheat=="maxhealthUp"||NameOfCheat=="maxhealthup"||NameOfCheat=="maxHealthup"||NameOfCheat=="Maxhealthup"||NameOfCheat=="MaxHealthup"||NameOfCheat=="MaxhealthUp")MaxHealthUp(arr.split(" ")[1].toInt(),arr.split(" ")[2].toInt());
    else if(NameOfCheat=="DamageBoost"||NameOfCheat=="damageBoost"||NameOfCheat=="damageboost"||NameOfCheat=="Damageboost")DamageBoost(arr.split(" ")[1].toInt(),arr.split(" ")[2].toInt());
    else if(NameOfCheat=="DefenseBoost"||NameOfCheat=="defenseBoost"||NameOfCheat=="defenseboost"||NameOfCheat=="Defenseboost")DefenseBoost(arr.split(" ")[1].toInt(),arr.split(" ")[2].toInt());
    else return "Данной команды не найдено";
    return Return;
}
QString Cheats::EnableCheats(QString password){
    if(password=="toor"){
        CheatIsAllowed=true;
        return "Доступ разрешён";
    }
    return "Неправильно введённый пароль!!";
}
void Cheats::StartNewGame(int GameMode){
    InitiativeStack.clear();
    MovesLeft=0;
    if(GameMode==0)NewGame();
    else if(GameMode==1)NewGame1();
}
