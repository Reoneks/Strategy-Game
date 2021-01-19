#include "game.h"
#include "mainwindow.h"
Game::Game(){
    MovesLeft=5;
    NewGame();
}
QString Game::CheckName(int name){
    QString ClassName;
    switch (name) {
        case 1:{ClassName="Воин";break;}
        case 2:{ClassName="Лучник";break;}
        case 3:{ClassName="Маг";break;}
    }
    return ClassName;
}
void Game::InitialiseStats(){
    for(int i=0;i<20;++i){
        switch(Stats[i][0]){
            case 1:{
                Stats[i][1]=100;
                Stats[i][2]=100;
                Stats[i][3]=50;
                Stats[i][4]=10;
                Stats[i][5]=3;
                Stats[i][6]=1;
                Stats[i][10]=3;
                Stats[i][11]=100;
                Stats[i][12]=100;
                break;
            }
            case 2:{
                Stats[i][1]=80;
                Stats[i][2]=80;
                Stats[i][3]=40;
                Stats[i][4]=5;
                Stats[i][5]=2;
                Stats[i][6]=4;
                Stats[i][10]=2;
                Stats[i][11]=100;
                Stats[i][12]=100;
                break;
            }
            case 3:{
                Stats[i][1]=50;
                Stats[i][2]=50;
                Stats[i][3]=60;
                Stats[i][4]=0;
                Stats[i][5]=3;
                Stats[i][6]=3;
                Stats[i][10]=1;
                Stats[i][11]=100;
                Stats[i][12]=100;
                break;
            }
        }
    }
}
void Game::InitialiseStats1(){
    for(int i=0;i<6;++i){
        switch(Stats1[i][0]){
            case 1:{
                Stats1[i][1]=100;
                Stats1[i][2]=100;
                Stats1[i][3]=50;
                Stats1[i][4]=10;
                Stats1[i][5]=3;
                Stats1[i][6]=1;
                Stats1[i][10]=3;
                Stats1[i][11]=100;
                Stats1[i][12]=100;
                break;
            }
            case 2:{
                Stats1[i][1]=80;
                Stats1[i][2]=80;
                Stats1[i][3]=40;
                Stats1[i][4]=5;
                Stats1[i][5]=2;
                Stats1[i][6]=4;
                Stats1[i][10]=2;
                Stats1[i][11]=100;
                Stats1[i][12]=100;
                break;
            }
            case 3:{
                Stats1[i][1]=50;
                Stats1[i][2]=50;
                Stats1[i][3]=60;
                Stats1[i][4]=0;
                Stats1[i][5]=3;
                Stats1[i][6]=3;
                Stats1[i][10]=1;
                Stats1[i][11]=100;
                Stats1[i][12]=100;
                break;
            }
        }
    }
}
void Game::NewGame(){
    for(int i=0,u=0;i<20;++i){
        if(i<5){
            Stats[i][0]=1;
            Stats[i][8]=1;
            Stats[i][7]=u;
            Stats[i][9]=1;
            ++u;
            if(u==5){
                u=0;
            }
        }
        if(i<10&&i>=5){
            Stats[i][0]=1;
            Stats[i][8]=7;
            Stats[i][7]=u;
            Stats[i][9]=2;
            ++u;
            if(u==5){
                u=0;
            }
        }
        else if(i<14&&i>=10){
            Stats[i][0]=2;
            Stats[i][8]=0;
            Stats[i][7]=u;
            Stats[i][9]=1;
            ++u;
            if(u==2){
                ++u;
            }else if(u==5){
                u=0;
            }
        }
        else if(i<18&&i>=14){
            Stats[i][0]=2;
            Stats[i][8]=8;
            Stats[i][7]=u;
            Stats[i][9]=2;
            ++u;
            if(u==2){
                ++u;
            }
        }
        else if(i==18){
            Stats[i][0]=3;
            Stats[i][8]=0;
            Stats[i][7]=2;
            Stats[i][9]=1;
        }
        else if(i==19){
            Stats[i][0]=3;
            Stats[i][8]=8;
            Stats[i][7]=2;
            Stats[i][9]=2;
        }
    }
    InitialiseStats();
    UnitStack();
}
void Game::NewGame1(){
    Stats1[0][0]=1;
    Stats1[0][8]=0;
    Stats1[0][7]=2;
    Stats1[0][9]=1;
    Stats1[0][13]=5;

    Stats1[1][0]=1;
    Stats1[1][8]=8;
    Stats1[1][7]=2;
    Stats1[1][9]=2;
    Stats1[1][13]=5;

    Stats1[2][0]=2;
    Stats1[2][8]=0;
    Stats1[2][7]=1;
    Stats1[2][9]=1;
    Stats1[2][13]=4;

    Stats1[3][0]=2;
    Stats1[3][8]=8;
    Stats1[3][7]=1;
    Stats1[3][9]=2;
    Stats1[3][13]=4;

    Stats1[4][0]=3;
    Stats1[4][8]=0;
    Stats1[4][7]=3;
    Stats1[4][9]=1;
    Stats1[4][13]=1;

    Stats1[5][0]=3;
    Stats1[5][8]=8;
    Stats1[5][7]=3;
    Stats1[5][9]=2;
    Stats1[5][13]=1;
    InitialiseStats1();
    UnitStack1();
}
QString* Game::CheckMove(int xam,int yam){
    arr[0]="0";
    arr[1]=" ";
    arr[2]=" ";
    arr[3]=" ";
    //Перемещение юнита
    if(GameBoard[Stats[unitid][8]+yam][Stats[unitid][7]+xam]=="~"){
        Stats[unitid][7]+=xam;
        Stats[unitid][8]+=yam;
    }
    else{
        arr[0]="1";
        arr[1]="Ход невозможен. На пути находится препятствие.";
    }
    return arr;
}
QString* Game::CheckMove1(int xam,int yam){
    arr[0]="0";
    arr[1]=" ";
    arr[2]=" ";
    arr[3]=" ";
    //Перемещение юнита
    if(GameBoard[Stats1[unitid][8]+yam][Stats1[unitid][7]+xam]=="~"){
        Stats1[unitid][7]+=xam;
        Stats1[unitid][8]+=yam;
    }
    else{
        arr[0]="1";
        arr[1]="Ход невозможен. На пути находится препятствие.";
    }
    return arr;
}
QString* Game::CheckDamage(int targx, int targy){
    arr[0]="0";
    arr[1]=" ";
    arr[2]=" ";
    arr[3]=" ";
    int id1=0;//Номер юнита которого атакуют
    //Поиск номера юнита
    for(int i=0;i<20;++i){
        if(Stats[i][7]==targx&&Stats[i][8]==targy){
            if(Stats[unitid][9]!=Stats[i][9]){
                id1=i;
                break;
            }else{
                arr[0]=QString::number(MovesLeft);
                arr[1]="Нельзя атаковать союзников!!!";
                return arr;
            }
        }
    }
    if(Stats[unitid][6]>=(abs(targx-Stats[unitid][7])+abs(targy-Stats[unitid][8]))){
        if((Stats[id1][4]-Stats[unitid][3])<0){
            Stats[id1][1]=Stats[id1][1]-Stats[unitid][3]+Stats[id1][4];
            QString Text="Вы нанесли "+QString::number(Stats[unitid][3]-Stats[id1][4])+" урона.";
            arr[1]=Text;
            if(Stats[id1][1]<=0){
                arr[2]="Враг был убит!";
                for (int i=0;i<10;++i){
                    Stats[id1][i]=0;
                }
            }
        }else{
            arr[1]="Атака провалена. У врага слишком сильная защита.";
            return arr;
        }
    }else{
        arr[0]=QString::number(MovesLeft);
        arr[1]="Атака невозможна. Враг слишком далеко.";
        return arr;
    }
    return arr;
}
QString* Game::CheckDamage1(int targx, int targy){
    arr[0]="0";
    arr[1]=" ";
    arr[2]=" ";
    arr[3]=" ";
    int id1=0;//Номер юнита которого атакуют
    //Поиск номера юнита
    for(int i=0;i<6;++i){
        if(Stats1[i][7]==targx&&Stats1[i][8]==targy){
            if(Stats1[unitid][9]!=Stats1[i][9]){
                id1=i;
                break;
            }else{
                arr[0]=QString::number(MovesLeft);
                arr[1]="Нельзя атаковать союзников!!!";
                return arr;
            }
        }
    }
    if(Stats1[unitid][6]>=(abs(targx-Stats1[unitid][7])+abs(targy-Stats1[unitid][8]))){
        if((Stats1[id1][4]-Stats1[unitid][3])<0){
            Stats1[id1][1]=Stats1[id1][1]-Stats1[unitid][3]+Stats1[id1][4];
            QString Text="Вы нанесли "+QString::number(Stats1[unitid][3]-Stats1[id1][4])+" урона.";
            arr[1]=Text;
            if(Stats1[id1][1]<=0){
                int HP=Stats1[id1][1];
                arr[2]="Враг понес потери!";
                --Stats1[id1][13];
                Stats1[id1][1]=Stats1[id1][2]+HP;
                if(Stats1[id1][13]==0){
                    arr[3]="Враг был убит";
                    for (int i=0;i<13;++i){
                        Stats1[id1][i]=0;
                    }
                }
            }
        }else{
            arr[1]="Атака провалена. У врага слишком сильная защита.";
            return arr;
        }
    }else{
        arr[0]=QString::number(MovesLeft);
        arr[1]="Атака невозможна. Враг слишком далеко.";
        return arr;
    }
    return arr;
}
void Game::UnitStack(){
    int minvalue=10000;
    int minvaluecount=0;
    int perem=0;
    int AlredyUsed[20];
    int MassivOfUnits[20];
    for(int i=0;i<20;++i)AlredyUsed[i]=0;
    for(int i=0;i<20;++i)MassivOfUnits[i]=0;
    InitiativeStack.clear();
    for (;;){
        perem=0;
        minvaluecount=0;
        minvalue=10000;
        for(int i=0;i<20;++i){
            if(AlredyUsed[i]==1)++perem;
        }
        if(perem==20)break;
        for(int i=0;i<20;++i){
            if(AlredyUsed[i]!=1){
                if(Stats[i][10]<minvalue)minvalue=Stats[i][10];
            }
        }
        for(int i=0;i<20;++i){
            if(Stats[i][10]==minvalue){
                MassivOfUnits[minvaluecount]=i;
                ++minvaluecount;
            }
        }
        qsrand(time(nullptr));
        for (int i=0;i<minvaluecount; ++i)std::swap(MassivOfUnits[i], MassivOfUnits[qrand() % minvaluecount]);
        for(int i=0;i<minvaluecount;++i){
            AlredyUsed[MassivOfUnits[i]]=1;
            InitiativeStack<<MassivOfUnits[i];
        }
    }
}
void Game::UnitStack1(){
    int minvalue=10000;
    int minvaluecount=0;
    int perem=0;
    int AlredyUsed[6];
    int MassivOfUnits[6];
    for(int i=0;i<6;++i)AlredyUsed[i]=0;
    for(int i=0;i<6;++i)MassivOfUnits[i]=0;
    InitiativeStack.clear();
    for (;;){
        perem=0;
        minvaluecount=0;
        minvalue=10000;
        for(int i=0;i<6;++i){
            if(AlredyUsed[i]==1)++perem;
        }
        if(perem==6)break;
        for(int i=0;i<6;++i){
            if(AlredyUsed[i]!=1){
                if(Stats1[i][10]<minvalue)minvalue=Stats1[i][10];
            }
        }
        for(int i=0;i<6;++i){
            if(Stats1[i][10]==minvalue){
                MassivOfUnits[minvaluecount]=i;
                ++minvaluecount;
            }
        }
        qsrand(time(nullptr));
        for (int i=0;i<minvaluecount; ++i)std::swap(MassivOfUnits[i], MassivOfUnits[qrand() % minvaluecount]);
        for(int i=0;i<minvaluecount;++i){
            AlredyUsed[MassivOfUnits[i]]=1;
            InitiativeStack<<MassivOfUnits[i];
        }
    }
}
