#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cheats.h"
#include "saveload.h"
#include "magicbook.h"
#include "magic.h"
#include "buttonhoverwatcher.h"
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    GameMode=0;
    vecnext=0;
    PreGameMode=0;
    MagicActivated=0;
    SkillActivated=0;
    MagicBookRollback=0;
    WidgetTable<<"Id"<<"Имя"<<"Текущее количество очков здоровья"<<"Полное количество очков здоровья"<<"Урон"<<"Защита"<<"Количество ходов"<<"Дальность атаки"<<"Координата x"<<"Координата y";
    WidgetTable1<<"Id"<<"Имя"<<"Текущее количество очков здоровья"<<"Полное количество очков здоровья"<<"Урон"<<"Защита"<<"Количество ходов"<<"Дальность атаки"<<"Координата x"<<"Координата y"<<"Количество";
    connect(ui->ExitButton,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(ui->NewGameButton,SIGNAL(clicked()),this,SLOT(NewGame()));
    connect(ui->UnitShop,SIGNAL(clicked()),this,SLOT(WorkInProgress()));
    connect(ui->HeroHouse,SIGNAL(clicked()),this,SLOT(WorkInProgress()));
    connect(ui->FirstAbility,SIGNAL(clicked()),this,SLOT(UnitAbilities()));
    connect(ui->SecondAbility,SIGNAL(clicked()),this,SLOT(UnitAbilities()));
    connect(ui->ThirdAbility,SIGNAL(clicked()),this,SLOT(UnitAbilities()));
    ui->FirstAbility->setStyleSheet("QPushButton{background: none; border:none; outline: none; color: transparent;}");
    ui->SecondAbility->setStyleSheet("QPushButton{background: none; border:none; outline: none; color: transparent;}");
    ui->ThirdAbility->setStyleSheet("QPushButton{background: none; border:none; outline: none; color: transparent;}");
    for(int i=0;i<3;++i){
        WidgetBorder[i]=0;
    }
    QPalette pal;
    QPixmap map;
    map.load(":/new/prefix1/2.png");
    map=map.scaled(900,550,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->page_2->backgroundRole(),QBrush(map));
    ui->page_2->setPalette(pal);
    ui->page_2->setAutoFillBackground(true);
    ui->Shield->setText("");
    ui->HourGlasses->setText("");
    ui->Shield->setStyleSheet("#Shield{border-image:url(:/new/prefix1/Shield.png);}");
    ui->Shield->setToolTip("Пропустить ход");
    ui->HourGlasses->setToolTip("Ждать");
    ui->HourGlasses->setStyleSheet("#HourGlasses{border-image:url(:/new/prefix1/Hourglasses.png);}");
    ui->CloseButton->setStyleSheet("#CloseButton{border-image:url(:/new/prefix1/cross.png);}");
    ui->MagicBook->setStyleSheet("#MagicBook{border-image:url(:/new/prefix1/MagicBook.png);color:white;font-size:18pt;}");
    ui->MagicBook->setText("");
    map.load(":/new/prefix1/1-floren.png");
    map=map.scaled(900,550,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->page->backgroundRole(),QBrush(map));
    ui->page->setPalette(pal);
    ui->page->setAutoFillBackground(true);
    pal.setBrush(ui->page_3->backgroundRole(),QBrush(map));
    ui->page_3->setPalette(pal);
    ui->page_3->setAutoFillBackground(true);
    map.load(":/new/prefix1/images.png");
    map=map.scaled(90,20,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->Text->backgroundRole(),QBrush(map));
    ui->Text->setPalette(pal);
    ui->Text->setAutoFillBackground(true);
    pal.setBrush(ui->Text1->backgroundRole(),QBrush(map));
    ui->Text1->setPalette(pal);
    ui->Text1->setAutoFillBackground(true);
    pal.setBrush(ui->Text1->backgroundRole(),QBrush(map));
    ui->Text2->setPalette(pal);
    ui->Text2->setAutoFillBackground(true);
    ui->Text->setStyleSheet(QString::fromUtf8("text-align: top center;"));
    ui->label_3->setToolTip("   ");
    ui->label_3->setStyleSheet("#label_3{color:white;} QToolTip{background-image: url(:/new/prefix1/Common.PNG);border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;min-width:833;min-height:550;}");
    ui->label_4->setToolTip("   ");
    ui->label_4->setStyleSheet("#label_4{color:white;} QToolTip{background-image: url(:/new/prefix1/New.PNG);border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;min-width:833;min-height:550;}");
    ButtonHoverWatcher * watcher = new ButtonHoverWatcher(this);
    ui->NewGameButton->installEventFilter(watcher);
    ui->UnitShop->installEventFilter(watcher);
    ui->HeroHouse->installEventFilter(watcher);
    ui->NewGameButton->setStyleSheet("QPushButton{background: none; border:none; outline: none; color: transparent;}");
    ui->UnitShop->setStyleSheet("QPushButton{background: none; border:none; outline: none; color: transparent;}");
    ui->HeroHouse->setStyleSheet("QPushButton{background: none; border:none; outline: none; color: transparent;}");
    pactSave->setText("Сохранить");
    pactSave->setShortcut(QKeySequence("CTRL+S"));
    pactSave1->setText("Загрузить");
    pactSave1->setShortcut(QKeySequence("CTRL+L"));
    pactSave2->setText("Выход");
    pactSave2->setShortcut(QKeySequence("Alt+F4"));
    pactSave3->setText("Вернутся на главный экран");
    pactSave3->setShortcut(QKeySequence("Escape"));
    pactSave->setVisible(false);
    pactSave1->setVisible(false);
    pactSave3->setVisible(false);
    connect(pactSave, SIGNAL(triggered()), SLOT(SaveLoad()));
    connect(pactSave1, SIGNAL(triggered()), SLOT(SaveLoad()));
    connect(pactSave2,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(pactSave3,SIGNAL(triggered()),SLOT(OnFirstScreen()));
    QMenu* pmnuFile = new QMenu("Файл");
    pmnuFile->addAction(pactSave);
    pmnuFile->addAction(pactSave1);
    pmnuFile->addAction(pactSave2);
    pmnuFile->addAction(pactSave3);
    ui->menuBar->addMenu(pmnuFile);
    ui->horizontalSlider->setRange(0,1);
    ui->Battlefield->viewport()->installEventFilter(this);
    ui->lineEdit->installEventFilter(this);
    connect(ui->Shield,SIGNAL(clicked()),this,SLOT(Skip()));
    connect(ui->HourGlasses,SIGNAL(clicked()),this,SLOT(Wait()));
    ui->Battlefield->verticalHeader()->resizeSections(QHeaderView::Stretch);
    ui->Battlefield->horizontalHeader()->resizeSections(QHeaderView::Stretch);
    ui->Battlefield->horizontalHeader()->hide();
    ui->Battlefield->verticalHeader()->hide();
    ui->Battlefield->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->FirstAbility->setText("");
    ui->SecondAbility->setText("");
    ui->ThirdAbility->setText("");
    for (int i=0; i<5; i++){
        for(int j=0;j<9;j++){
            QTableWidgetItem *t = new QTableWidgetItem("");
            ui->Battlefield->setItem(i,j,t);
        }
    }
    SkillsArray[6]="Огненная стрела";
    game=new Magic();
    beta=new class MagicBook();
    connect(beta,SIGNAL(MagicIsSelected()),this,SLOT(ActivateMagic()));
    GameHasStarted=false;
    game->BufsOrDebufs.resize(4);
    CannotSave<<"Сохранено"<<"Ошибка записи"<<"Успешно загружено!"<<"Не удалось загрузить файл"<<"Доступ разрешён"<<"Неправильно введённый пароль!!"<<"";
}




void MainWindow::Skip(){
    game->BufsOrDebufs[0]<<1;
    game->BufsOrDebufs[1]<<game->unitid;
    game->BufsOrDebufs[2]<<1;
    game->BufsOrDebufs[3]<<10;
    game->Stats[game->unitid][4]+=10;
    if(GameMode==0)NextUnit();
    else if(GameMode==1)NextUnit1();
}




void MainWindow::Wait(){
    vec<<game->unitid;
    if(GameMode==0)NextUnit();
    else if(GameMode==1)NextUnit1();
}




MainWindow::~MainWindow(){
    delete ui;
    delete game;
    delete beta;
    delete pactSave;
    delete pactSave1;
    delete pactSave2;
    delete pactSave3;
}




void MainWindow::ConsoleLog(QString TextInConsole){
    ui->Console->append(TextInConsole);
}




void MainWindow::UpdateBoard(){
    for(int i=0;i<9;++i){
        for(int u=0;u<5;++u){
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText("~");
            ui->Battlefield->setItem(i,u,item);
            game->GameBoard[i][u]="~";
        }
    }
    for(int i=0;i<20;++i){
        QTableWidgetItem *item = new QTableWidgetItem;
        if(game->Stats[i][0]!=0){
            item->setText(game->CheckName(game->Stats[i][0])+"\nHP: "+QString::number(game->Stats[i][1])+"/"+QString::number(game->Stats[i][2])+"\nMP: "+QString::number(game->Stats[i][11])+"/"+QString::number(game->Stats[i][12]));
            game->GameBoard[game->Stats[i][8]][game->Stats[i][7]]=game->CheckName(game->Stats[i][0]);
            ui->Battlefield->setItem(game->Stats[i][8],game->Stats[i][7],item);
            if(i==game->unitid)ui->Battlefield->setCurrentItem(item);
            if(game->Stats[i][9]==1)ui->Battlefield->item(game->Stats[i][8],game->Stats[i][7])->setTextColor(Qt::blue);
            else if(game->Stats[i][9]==2)ui->Battlefield->item(game->Stats[i][8],game->Stats[i][7])->setTextColor(Qt::red);
        }
    }
}




void MainWindow::UpdateBoard1(){
    for(int i=0;i<9;++i){
        for(int u=0;u<5;++u){
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText("~");
            ui->Battlefield->setItem(i,u,item);
            game->GameBoard[i][u]="~";
        }
    }
    for(int i=0;i<6;++i){
        QTableWidgetItem *item = new QTableWidgetItem;
        if(game->Stats1[i][0]!=0){
            item->setText(game->CheckName(game->Stats1[i][0])+"("+QString::number(game->Stats1[i][13])+")\nHP: "+QString::number(game->Stats1[i][1])+"/"+QString::number(game->Stats1[i][2])+"\nMP: "+QString::number(game->Stats1[i][11])+"/"+QString::number(game->Stats1[i][12]));
            game->GameBoard[game->Stats1[i][8]][game->Stats1[i][7]]=game->CheckName(game->Stats1[i][0]);
            ui->Battlefield->setItem(game->Stats1[i][8],game->Stats1[i][7],item);
            if(i==game->unitid)ui->Battlefield->setCurrentItem(item);
            if(game->Stats1[i][9]==1)ui->Battlefield->item(game->Stats1[i][8],game->Stats1[i][7])->setTextColor(Qt::blue);
            else if(game->Stats1[i][9]==2)ui->Battlefield->item(game->Stats1[i][8],game->Stats1[i][7])->setTextColor(Qt::red);
        }
    }
}




void MainWindow::AttackUnit(QString arr){
    QString *ResultOfWorking1;
    if(GameMode==0)ResultOfWorking1=game->CheckDamage(arr.split(" ")[0].toInt(),arr.split(" ")[1].toInt());
    else ResultOfWorking1=game->CheckDamage1(arr.split(" ")[0].toInt(),arr.split(" ")[1].toInt());
    if(ResultOfWorking1[1]!=" ")ConsoleLog(ResultOfWorking1[1]);
    if(ResultOfWorking1[2]!=" ")ConsoleLog(ResultOfWorking1[2]);
    if(ResultOfWorking1[3]!=" ")ConsoleLog(ResultOfWorking1[3]);
    game->MovesLeft=0;
    game->MovesLeft+=ResultOfWorking1[0].toInt();
    if(game->MovesLeft==0){
        if(GameMode==0)NextUnit();
        else if(GameMode==1)NextUnit1();
    }
    return;
}




void MainWindow::NextUnit(){
    if(nextunit==-1){
        if(vecnext!=vec.length()){
            game->unitid=vec[vecnext];
            if(game->Stats[game->unitid][0]==3){
                ui->FirstAbility->setStyleSheet("#FirstAbility{border-image:url(:/new/prefix1/FlameArrow.png);}");
            }else{
                ui->FirstAbility->setStyleSheet("QPushButton{background: none; border:none; outline: none; color: transparent;}");
                ui->SecondAbility->setStyleSheet("QPushButton{background: none; border:none; outline: none; color: transparent;}");
                ui->ThirdAbility->setStyleSheet("QPushButton{background: none; border:none; outline: none; color: transparent;}");
            }
            ++vecnext;
            game->MovesLeft=game->Stats[game->unitid][5];
            UpdateBoard();
            return;
        }else{
            ++round;
            vec.clear();
            vecnext=0;
            nextunit=game->InitiativeStack.size()-1;
            ConsoleLog("Раунд "+QString::number(round));
            if(MagicBookRollback!=0){
                --MagicBookRollback;
                if(MagicBookRollback==0){
                    ui->MagicBook->setDisabled(false);
                    ui->MagicBook->setText("");
                }else{
                    ui->MagicBook->setText(QString::number(MagicBookRollback));
                }
            }
            for(int i=0;i<game->BufsOrDebufs[0].length();++i){
                if(game->BufsOrDebufs[2][i]>=0)--game->BufsOrDebufs[2][i];
                if(game->BufsOrDebufs[2][i]>0){
                    QString Result;
                    Result=game->WhatType(game->BufsOrDebufs[0][i]);
                    if(Result=="Урон"){
                        game->Stats[game->BufsOrDebufs[1][i]][1]-=game->BufsOrDebufs[3][i];
                        if(game->Stats[game->BufsOrDebufs[1][i]][1]<=0){
                            ConsoleLog("Враг был убит!");
                            for (int in=0;in<10;++in){
                                game->Stats[game->BufsOrDebufs[1][i]][in]=0;
                            }
                        }
                    }
                }else if(game->BufsOrDebufs[2][i]==0){
                    QString Result;
                    Result=game->WhatType(game->BufsOrDebufs[0][i]);
                    if(Result!="Урон"){
                        int result;
                        result=game->WhatMagic(game->BufsOrDebufs[0][i]);
                        if(result>=0){
                            if(game->BufsOrDebufs[3][i]>=0){
                                game->Stats[game->BufsOrDebufs[1][i]][result]-=game->BufsOrDebufs[3][i];
                            }else{
                                game->Stats[game->BufsOrDebufs[1][i]][result]+=abs(game->BufsOrDebufs[3][i]);
                            }
                        }else ConsoleLog("Произошла ошибка в массиве эффектов!!!!!!");
                    }
                    game->BufsOrDebufs[2][i]=-999;
                }
            }
        }
    }
    for(;;){
        if(nextunit==-1){
            if(vecnext!=vec.length()){
                game->unitid=vec[vecnext];
                if(game->Stats[game->unitid][0]==3){
                    ui->FirstAbility->setStyleSheet("#FirstAbility{border-image:url(:/new/prefix1/FlameArrow.png);}");
                }else{
                    ui->FirstAbility->setStyleSheet("QPushButton{background: none; border:none; outline: none; color: transparent;}");
                    ui->SecondAbility->setStyleSheet("QPushButton{background: none; border:none; outline: none; color: transparent;}");
                    ui->ThirdAbility->setStyleSheet("QPushButton{background: none; border:none; outline: none; color: transparent;}");
                }
                ++vecnext;
                game->MovesLeft=game->Stats[game->unitid][5];
                UpdateBoard();
                return;
            }else {
                ++round;
                vec.clear();
                vecnext=0;
                nextunit=game->InitiativeStack.size()-1;
                ConsoleLog("Раунд "+QString::number(round));
                for(int i=0;i<game->BufsOrDebufs[0].length();++i){
                    if(game->BufsOrDebufs[2][i]>=0)--game->BufsOrDebufs[2][i];
                    if(game->BufsOrDebufs[2][i]>0){
                        QString Result;
                        Result=game->WhatType(game->BufsOrDebufs[0][i]);
                        if(Result=="Урон"){
                            game->Stats[game->BufsOrDebufs[1][i]][1]-=game->BufsOrDebufs[3][i];
                            if(game->Stats[game->BufsOrDebufs[1][i]][1]<=0){
                                ConsoleLog("Враг был убит!");
                                for (int in=0;in<10;++in){
                                    game->Stats[game->BufsOrDebufs[1][i]][in]=0;
                                }
                            }
                        }
                    }else if(game->BufsOrDebufs[2][i]==0){
                        QString Result;
                        Result=game->WhatType(game->BufsOrDebufs[0][i]);
                        if(Result!="Урон"){
                            int result;
                            result=game->WhatMagic(game->BufsOrDebufs[0][i]);
                            if(result>=0){
                                if(game->BufsOrDebufs[3][i]>=0){
                                    game->Stats[game->BufsOrDebufs[1][i]][result]-=game->BufsOrDebufs[3][i];
                                }else{
                                    game->Stats[game->BufsOrDebufs[1][i]][result]+=abs(game->BufsOrDebufs[3][i]);
                                }
                            }else ConsoleLog("Произошла ошибка в массиве эффектов!!!!!!");
                        }
                        game->BufsOrDebufs[2][i]=-999;
                    }
                }
            }
        }
        game->unitid=game->InitiativeStack[nextunit];
        if(game->Stats[game->unitid][0]==3){
            ui->FirstAbility->setStyleSheet("#FirstAbility{border-image:url(:/new/prefix1/FlameArrow.png);}");
        }else{
            ui->FirstAbility->setStyleSheet("QPushButton{background: none; border:none; outline: none; color: transparent;}");
            ui->SecondAbility->setStyleSheet("QPushButton{background: none; border:none; outline: none; color: transparent;}");
            ui->ThirdAbility->setStyleSheet("QPushButton{background: none; border:none; outline: none; color: transparent;}");
        }
        game->MovesLeft=game->Stats[game->unitid][5];
        if(game->Stats[game->unitid][0]!=0)break;
        else --nextunit;
    }
    UpdateBoard();
    --nextunit;
}




void MainWindow::NextUnit1(){
    if(nextunit==-1){
        if(vecnext!=vec.length()){
            game->unitid=vec[vecnext];
            ++vecnext;
            game->MovesLeft=game->Stats1[game->unitid][5];
            UpdateBoard1();
            return;
        }else{
            ++round;
            vec.clear();
            vecnext=0;
            nextunit=game->InitiativeStack.size()-1;
            ConsoleLog("Раунд "+QString::number(round));
            for(int i=0;i<game->BufsOrDebufs[0].length();++i){
                if(game->BufsOrDebufs[2][i]>=0)--game->BufsOrDebufs[2][i];
                if(game->BufsOrDebufs[2][i]>0){
                    QString Result;
                    Result=game->WhatType(game->BufsOrDebufs[0][i]);
                    if(Result=="Урон"){
                        game->Stats1[game->BufsOrDebufs[1][i]][1]-=game->BufsOrDebufs[3][i];
                        if(game->Stats1[game->BufsOrDebufs[1][i]][1]<=0){
                            ConsoleLog("Враг был убит!");
                            for (int in=0;in<10;++in){
                                game->Stats1[game->BufsOrDebufs[1][i]][in]=0;
                            }
                        }
                    }
                }else if(game->BufsOrDebufs[2][i]==0){
                    QString Result;
                    Result=game->WhatType(game->BufsOrDebufs[0][i]);
                    if(Result!="Урон"){
                        int result;
                        result=game->WhatMagic(game->BufsOrDebufs[0][i]);
                        if(result>=0){
                            if(game->BufsOrDebufs[3][i]>=0){
                                game->Stats1[game->BufsOrDebufs[1][i]][result]-=game->BufsOrDebufs[3][i];
                            }else{
                                game->Stats1[game->BufsOrDebufs[1][i]][result]+=abs(game->BufsOrDebufs[3][i]);
                            }
                        }else ConsoleLog("Произошла ошибка в массиве эффектов!!!!!!");
                    }
                    game->BufsOrDebufs[2][i]=-999;
                }
            }
        }
    }
    for(;;){
        if(nextunit==-1){
            if(vecnext!=vec.length()){
                game->unitid=vec[vecnext];
                ++vecnext;
                game->MovesLeft=game->Stats1[game->unitid][5];
                UpdateBoard1();
                return;
            }else {
                ++round;
                vec.clear();
                vecnext=0;
                nextunit=game->InitiativeStack.size()-1;
                ConsoleLog("Раунд "+QString::number(round));
                for(int i=0;i<game->BufsOrDebufs[0].length();++i){
                    if(game->BufsOrDebufs[2][i]>=0)--game->BufsOrDebufs[2][i];
                    if(game->BufsOrDebufs[2][i]>0){
                        QString Result;
                        Result=game->WhatType(game->BufsOrDebufs[0][i]);
                        if(Result=="Урон"){
                            game->Stats1[game->BufsOrDebufs[1][i]][1]-=game->BufsOrDebufs[3][i];
                            if(game->Stats1[game->BufsOrDebufs[1][i]][1]<=0){
                                ConsoleLog("Враг был убит!");
                                for (int in=0;in<10;++in){
                                    game->Stats1[game->BufsOrDebufs[1][i]][in]=0;
                                }
                            }
                        }
                    }else if(game->BufsOrDebufs[2][i]==0){
                        QString Result;
                        Result=game->WhatType(game->BufsOrDebufs[0][i]);
                        if(Result!="Урон"){
                            int result;
                            result=game->WhatMagic(game->BufsOrDebufs[0][i]);
                            if(result>=0){
                                if(game->BufsOrDebufs[3][i]>=0){
                                    game->Stats1[game->BufsOrDebufs[1][i]][result]-=game->BufsOrDebufs[3][i];
                                }else{
                                    game->Stats1[game->BufsOrDebufs[1][i]][result]+=abs(game->BufsOrDebufs[3][i]);
                                }
                            }else ConsoleLog("Произошла ошибка в массиве эффектов!!!!!!");
                        }
                        game->BufsOrDebufs[2][i]=-999;
                    }
                }
            }
        }
        game->unitid=game->InitiativeStack[nextunit];
        game->MovesLeft=game->Stats1[game->unitid][5];
        if(game->Stats1[game->unitid][0]!=0)break;
        else --nextunit;
    }
    UpdateBoard1();
    --nextunit;
}




bool MainWindow::eventFilter(QObject *object, QEvent *event){
    if (object == this->ui->Battlefield->viewport()){
        if(event->type() == QEvent::MouseButtonPress){
            QMouseEvent *ms = static_cast<QMouseEvent *>(event);
            if(ms->buttons() & Qt::RightButton){
                if(MagicActivated==1){
                    beta->AllMagic();
                    beta->show();
                    MagicActivated=0;
                }else if(SkillActivated==1){
                    ConsoleLog("Сброс");
                    SkillActivated=0;
                }else{
                    QItemSelectionModel *select=ui->Battlefield->selectionModel();
                    int row=select->currentIndex().row();
                    select->selectedColumns();
                    int column=select->currentIndex().column();
                    int id=0;
                    if(GameMode==0){
                        for(int i=0;i<20;++i){
                            if(game->Stats[i][7]==column&&game->Stats[i][8]==row){
                                   id=i;
                                   break;
                            }
                        }
                    }else if(GameMode==1){
                        for(int i=0;i<6;++i){
                            if(game->Stats1[i][7]==column&&game->Stats1[i][8]==row){
                                   id=i;
                                   break;
                            }
                        }
                    }
                    QGridLayout *hlayout=new QGridLayout;
                    QLabel *label,*label1;
                    QWidget *mainWindow = new QWidget;
                    int WidgetTableNumber=0;
                    if(GameMode==0){
                        WidgetTableNumber=WidgetTable.length();
                        for(int i=0;i<WidgetTable.length();++i){
                            label=new QLabel(WidgetTable[i]);
                            if(i==0)label1=new QLabel(QString::number(id));
                            else if(i==1) label1=new QLabel(game->CheckName(game->Stats[id][i-1]));
                            else label1=new QLabel(QString::number(game->Stats[id][i-1]));
                            hlayout->addWidget(label,i,0);
                            hlayout->addWidget(label1,i,1);
                        }
                    }else if(GameMode==1){
                        WidgetTableNumber=WidgetTable1.length();
                        for(int i=0;i<WidgetTable1.length();++i){
                            label=new QLabel(WidgetTable1[i]);
                            if(i==0)label1=new QLabel(QString::number(id));
                            else if(i==1) label1=new QLabel(game->CheckName(game->Stats1[id][i-1]));
                            else label1=new QLabel(QString::number(game->Stats1[id][i-1]));
                            hlayout->addWidget(label,i,0);
                            hlayout->addWidget(label1,i,1);
                        }
                    }
                    int us=0;
                    for(int i=0;i<game->BufsOrDebufs[0].length();++i){
                        if(game->BufsOrDebufs[1][i]==id){
                            if(game->BufsOrDebufs[2][i]>0){
                                if(us==0){
                                    label=new QLabel("Эффекты: ");
                                    label1=new QLabel("");
                                    hlayout->addWidget(label,WidgetTableNumber,0);
                                    hlayout->addWidget(label1,WidgetTableNumber,1);
                                    ++WidgetTableNumber;
                                    ++us;
                                }
                                label=new QLabel(game->WhatMagicName(game->BufsOrDebufs[0][i]));
                                label1=new QLabel(QString::number(game->BufsOrDebufs[2][i])+" Ходов");
                                hlayout->addWidget(label,WidgetTableNumber,0);
                                hlayout->addWidget(label1,WidgetTableNumber,1);
                                ++WidgetTableNumber;
                            }
                        }
                    }
                    mainWindow->setLayout(hlayout);
                    mainWindow->show();
                    if(GameMode==0)UpdateBoard();
                    else if(GameMode==1)UpdateBoard1();
                }
            }
        }
        else if(event->type() == QEvent::MouseButtonDblClick){
            QMouseEvent *ms = static_cast<QMouseEvent *>(event);
            if(ms->buttons() & Qt::LeftButton){
                QItemSelectionModel *select=ui->Battlefield->selectionModel();
                int row=select->currentIndex().row();
                select->selectedColumns();
                int column=select->currentIndex().column();
                if(game->GameBoard[row][column]!="~"){
                    if(SkillActivated==1){
                        QVector<QString>Result;
                        bool WhatPlayer=true;
                        int id=0;
                        if(GameMode==0){
                            for(int i=0;i<20;++i){
                                if(game->Stats[i][7]==column&&game->Stats[i][8]==row){
                                    id=i;
                                    break;
                                }
                            }
                            if(SkillsArray[SkillsArrayId]=="Огненная стрела"){
                                if(game->Stats[id][9]!=game->Stats[game->unitid][9]){
                                    Result=game->FireArrow(id);
                                    game->Stats[game->unitid][11]-=40;
                                }else{
                                    ConsoleLog("Ошибка! Вы не можете атаковать своих же");
                                    WhatPlayer=false;
                                }
                            }
                        }
                        SkillActivated=0;
                        for(int i=0;i<Result.length();++i){
                            ConsoleLog(Result[i]);
                        }
                        if(WhatPlayer)NextUnit();
                    }else if(MagicActivated==1){
                        int id=0;
                        QVector<QString>Log;
                        if(GameMode==0){
                            for(int i=0;i<20;++i){
                                if(game->Stats[i][7]==column&&game->Stats[i][8]==row){
                                    id=i;
                                    break;
                                }
                            }
                            if(beta->MagicSelected=="Защита"){
                                if(game->Stats[id][9]==game->Stats[game->unitid][9]){
                                    Log=game->Defence(id);
                                    MagicBookRollback=2;
                                }else ConsoleLog("Вы не можете накладывать баффы на персонажей другого игрока!!!");
                            }else if(beta->MagicSelected=="Огненная стрела"){
                                if(game->Stats[id][9]!=game->Stats[game->unitid][9]){
                                    Log=game->FireArrow(id);
                                    MagicBookRollback=2;
                                }else ConsoleLog("Ошибка! Вы не можете атаковать своих же");
                            }
                            if(MagicBookRollback!=0){
                                ui->MagicBook->setDisabled(true);
                                ui->MagicBook->setText(QString::number(MagicBookRollback));
                            }
                        }
                        for(int i=0;i<Log.length();++i){
                            ConsoleLog(Log[i]);
                        }
                        MagicActivated=0;
                    }else{
                        AttackUnit(QString::number(column)+" "+QString::number(row));
                    }
                    if(GameMode==0)UpdateBoard();
                    else if(GameMode==1)UpdateBoard1();
                    int redplayer=0,blueplayer=0;
                    if(GameMode==0){
                        for(int i=0;i<20;++i){
                            if(game->Stats[i][0]!=0){
                                if(game->Stats[i][9]==1)++blueplayer;
                                else ++redplayer;
                            }
                        }
                    }else if(GameMode==1){
                        for(int i=0;i<6;++i){
                            if(game->Stats1[i][0]!=0){
                                if(game->Stats1[i][9]==1)++blueplayer;
                                else ++redplayer;
                            }
                        }
                    }
                    if(redplayer==0||blueplayer==0){
                        QGridLayout *hlayout=new QGridLayout;
                        QLabel *label=new QLabel("Ничья");
                        if(redplayer==0)label=new QLabel("Выиграл синий игрок");
                        if(blueplayer==0)label = new QLabel("Выиграл красный игрок");
                        QWidget *mainWindow = new QWidget;
                        hlayout->addWidget(label);
                        mainWindow->setLayout(hlayout);
                        mainWindow->show();
                        ui->Text->setText("<html><head/><body><p align=\"center\">Новая Игра</p></body></html>");
                        ui->stackedWidget->setCurrentIndex(0);
                        pactSave->setVisible(false);
                        pactSave1->setVisible(false);
                        pactSave3->setVisible(false);
                    }
                }else{
                    if(MagicActivated==1||SkillActivated==1){
                        ConsoleLog("Вы не можете атаковать пустую клетку!");
                    }else{
                        int redplayer=0,blueplayer=0;
                        if(GameMode==0){
                            for(int i=0;i<20;++i){
                                if(game->Stats[i][0]!=0){
                                    if(game->Stats[i][9]==1)++blueplayer;
                                    else ++redplayer;
                                }
                            }
                        }else if(GameMode==1){
                            for(int i=0;i<6;++i){
                                if(game->Stats1[i][0]!=0){
                                    if(game->Stats1[i][9]==1)++blueplayer;
                                    else ++redplayer;
                                }
                            }
                        }
                        if(redplayer==0||blueplayer==0){
                            QGridLayout *hlayout=new QGridLayout;
                            QLabel *label=new QLabel("Ничья");
                            if(redplayer==0)label=new QLabel("Выиграл синий игрок");
                            if(blueplayer==0)label = new QLabel("Выиграл красный игрок");
                            QWidget *mainWindow = new QWidget;
                            hlayout->addWidget(label);
                            mainWindow->setLayout(hlayout);
                            mainWindow->show();
                            ui->Text->setText("<html><head/><body><p align=\"center\">Новая Игра</p></body></html>");
                            ui->stackedWidget->setCurrentIndex(0);
                            pactSave->setVisible(false);
                            pactSave1->setVisible(false);
                            pactSave3->setVisible(false);
                        }
                        QString *ResultOfWorking;
                        if(GameMode==0){
                            if(game->MovesLeft>=(abs(column-game->Stats[game->unitid][7])+abs(row-game->Stats[game->unitid][8]))){
                                int precolumn=game->Stats[game->unitid][7],prerow=game->Stats[game->unitid][8];
                                ResultOfWorking=game->CheckMove(column-game->Stats[game->unitid][7],row-game->Stats[game->unitid][8]);
                                game->MovesLeft=game->MovesLeft-abs(column-precolumn)-abs(row-prerow);
                                if(ResultOfWorking[1]!=" ")ConsoleLog(ResultOfWorking[1]);
                                if(game->MovesLeft<=0)NextUnit();
                            }else ConsoleLog("Слишком далеко!");
                            UpdateBoard();
                        }else if(GameMode==1){
                            if(game->MovesLeft>=(abs(column-game->Stats1[game->unitid][7])+abs(row-game->Stats1[game->unitid][8]))){
                                int precolumn=game->Stats1[game->unitid][7],prerow=game->Stats1[game->unitid][8];
                                ResultOfWorking=game->CheckMove1(column-game->Stats1[game->unitid][7],row-game->Stats1[game->unitid][8]);
                                game->MovesLeft=game->MovesLeft-abs(column-precolumn)-abs(row-prerow);
                                if(ResultOfWorking[1]!=" ")ConsoleLog(ResultOfWorking[1]);
                                if(game->MovesLeft<=0)NextUnit1();
                            }else ConsoleLog("Слишком далеко!");
                            UpdateBoard1();
                        }
                    }
                }
            }
        }
    }else if(object==ui->lineEdit){
        if(event->type() == QEvent::KeyPress){
            QKeyEvent *e = static_cast<QKeyEvent*>(event);
            if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter){
                QString command=ui->lineEdit->text();
                ui->lineEdit->setText("");
                if(command=="Start New Game"){
                    command=command+" "+QString::number(GameMode);
                }
                QString Result=game->WhatCheatIsIt(command);
                if(Result!=" ")ConsoleLog(Result);
                if(command==("Start New Game "+QString::number(GameMode))){
                    round=1;
                    vec.clear();
                    vecnext=0;
                    ui->Console->setText("");
                    ConsoleLog("Раунд "+QString::number(round));
                    nextunit=game->InitiativeStack.size()-1;
                    if(GameMode==0)NextUnit();
                    else if(GameMode==1)NextUnit1();
                }
                if(GameMode==0){
                    if(game->Stats[game->unitid][0]==0)NextUnit();
                }
                else if(GameMode==1){
                    if(game->Stats1[game->unitid][0]==0)NextUnit1();
                }
                if(GameMode==0)UpdateBoard();
                else if(GameMode==1)UpdateBoard1();
            }
        }
    }
    return QObject::eventFilter(object, event);
}




void MainWindow::SaveGame(){
    try{
        QFile inputFile(QCoreApplication::applicationDirPath()+"\\Saves\\"+alfa->File);
        if (!inputFile.open(QIODevice::WriteOnly))throw 1;
        QTextStream Input(&inputFile);
        for(int i=0;i<9;++i){
            for(int u=0;u<5;++u){
                Input<<game->GameBoard[i][u]<<" ";
            }
            Input<<"\r\n";
        }
        Input<<QString::number(GameMode)<<"\r\n";
        if(GameMode==0){
            for(int i=0;i<20;++i){
                for(int u=0;u<11;++u){
                    Input<<QString::number(game->Stats[i][u])<<" ";
                }
                Input<<"\r\n";
            }
        }else if(GameMode==1){
            for(int i=0;i<6;++i){
                for(int u=0;u<12;++u){
                    Input<<QString::number(game->Stats1[i][u])<<" ";
                }
                Input<<"\r\n";
            }
        }
        for(int i=0;i<game->InitiativeStack.length();++i){
            Input<<QString::number(game->InitiativeStack[i])<<" ";
        }
        Input<<"\r\n";
        for(int i=0;i<vec.length();++i){
            Input<<QString::number(vec[i])<<" ";
        }
        Input<<"\r\n"<<QString::number(game->unitid)<<"\r\n"<<QString::number(game->MovesLeft)<<"\r\n"<<QString::number(vecnext)<<"\r\n"<<QString::number(nextunit)<<"\r\n"<<QString::number(round)<<"\r\n";
        QStringList lines = ui->Console->toPlainText().split('\n');
        bool CanSave=true;
        for(int i=0;i<lines.size();++i){
            for(int u=0;u<CannotSave.size();++u){
                if(lines.at(i)==CannotSave[u]){
                    CanSave=false;
                    break;
                }
            }
            if(CanSave)Input<<lines.at(i)<<"\r\n";
            CanSave=true;
        }
        inputFile.close();
        ConsoleLog("Сохранено");
    }catch (...){
        ConsoleLog("Ошибка записи");
    }
}




void MainWindow::LoadGame(){
    if(alfa->File!="NoFile"){
        QFile outputFile(QCoreApplication::applicationDirPath()+"\\Saves\\"+alfa->File);
        QString rem;
        try {
            if (!outputFile.open(QIODevice::ReadOnly))throw 1;
            QStringList lst;
            for(int i=0;i<9;++i){
                rem=outputFile.readLine();
                lst=rem.split(" ");
                for(int u=0;u<5;++u){
                    game->GameBoard[i][u]=lst.at(u);
                }
            }
            rem=outputFile.readLine();
            GameMode=rem.toInt();
            if(GameMode==0){
                for(int i=0;i<20;++i){
                    rem=outputFile.readLine();
                    lst=rem.split(" ");
                    for(int u=0;u<11;++u){
                        game->Stats[i][u]=lst.at(u).toInt();
                    }
                }
            }else if(GameMode==1){
                for(int i=0;i<6;++i){
                    rem=outputFile.readLine();
                    lst=rem.split(" ");
                    for(int u=0;u<12;++u){
                        game->Stats1[i][u]=lst.at(u).toInt();
                    }
                }
            }
            rem=outputFile.readLine();
            lst=rem.split(" ");
            game->InitiativeStack.clear();
            for(int i=0;i<lst.size()-1;++i){
                game->InitiativeStack<<lst.at(i).toInt();
            }
            rem=outputFile.readLine();
            lst=rem.split(" ");
            vec.clear();
            for(int i=0;i<lst.size()-1;++i){
                vec<<lst.at(i).toInt();
            }
            rem=outputFile.readLine();
            game->unitid=rem.toInt();
            rem=outputFile.readLine();
            game->MovesLeft=rem.toInt();
            rem=outputFile.readLine();
            vecnext=rem.toInt();
            rem=outputFile.readLine();
            nextunit=rem.toInt();
            rem=outputFile.readLine();
            round=rem.toInt();
            ui->Console->clear();
            while(!outputFile.atEnd()){
                QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
                rem=codec->toUnicode(outputFile.readLine());
                if(rem!=""){
                    rem=rem.split("\r\n")[0];
                    ConsoleLog(rem);
                }
            }
            outputFile.close();
            if(GameMode==0)UpdateBoard();
            if(GameMode==1)UpdateBoard1();
            ConsoleLog("Успешно загружено!");
        } catch (...) {
            ConsoleLog("Ошибка чтения");
        }
    }else ConsoleLog("Не удалось загрузить файл");
}




void MainWindow::NewGame(){
    if(ui->Text->text()=="<html><head/><body><p align=\"center\">Новая Игра</p></body></html>"){
        ui->Console->setText("");
        ui->stackedWidget->setCurrentIndex(1);
        pactSave->setVisible(true);
        pactSave1->setVisible(true);
        pactSave3->setVisible(true);
        round=1;
        ConsoleLog("Раунд "+QString::number(round));
        if(GameMode==0){
            game->NewGame();
            nextunit=game->InitiativeStack.size()-1;
            NextUnit();
            UpdateBoard();
        }else if(GameMode==1){
            game->NewGame1();
            nextunit=game->InitiativeStack.size()-1;
            NextUnit1();
            UpdateBoard1();
        }
        ui->Text->setText("<html><head/><body><p align=\"center\">Продолжить игру</p></body></html>");
        GameHasStarted=true;
    }else if(ui->Text->text()=="<html><head/><body><p align=\"center\">Продолжить игру</p></body></html>"){
        ui->stackedWidget->setCurrentIndex(1);
        pactSave->setVisible(true);
        pactSave1->setVisible(true);
        pactSave3->setVisible(true);
    }
}




void MainWindow::on_widget_3_destroyed(){
    if(WidgetBorder[0]==0){
        ui->widget_3->setStyleSheet(QString::fromUtf8("#widget_3{border: 2px solid yellow; border-radius: 4px; padding: 2px;}"));
        WidgetBorder[0]=1;
    }else if(WidgetBorder[0]==1){
        ui->widget_3->setStyleSheet(QString::fromUtf8(""));
        WidgetBorder[0]=0;
    }
}




void MainWindow::on_widget_4_destroyed(){
    if(WidgetBorder[1]==0){
        ui->widget_4->setStyleSheet(QString::fromUtf8("#widget_4{border: 2px solid yellow; border-radius: 4px; padding: 2px;}"));
        WidgetBorder[1]=1;
    }else if(WidgetBorder[1]==1){
        ui->widget_4->setStyleSheet(QString::fromUtf8(""));
        WidgetBorder[1]=0;
    }
}




void MainWindow::OnFirstScreen(){
    ui->stackedWidget->setCurrentIndex(0);
    pactSave->setVisible(false);
    pactSave1->setVisible(false);
    pactSave3->setVisible(false);
}




void MainWindow::WorkInProgress(){
    QGridLayout *hlayout=new QGridLayout;
    QLabel *label = new QLabel("Данная функция находится в разработке(WIP)");
    QWidget *mainWindow = new QWidget;
    hlayout->addWidget(label);
    mainWindow->setLayout(hlayout);
    mainWindow->show();
}




void MainWindow::on_widget_5_destroyed(){
    if(WidgetBorder[2]==0){
        ui->widget_5->setStyleSheet(QString::fromUtf8("#widget_5{border: 2px solid yellow; border-radius: 4px; padding: 2px;}"));
        WidgetBorder[2]=1;
    }else if(WidgetBorder[2]==1){
        ui->widget_5->setStyleSheet(QString::fromUtf8(""));
        WidgetBorder[2]=0;
    }
}




void MainWindow::SaveLoad(){
    auto obj=QObject::sender();
    alfa=new class SaveLoad();
    if(obj==pactSave){
        alfa->setComplete("Save");
        connect(alfa,SIGNAL(SaveLoadChange()),this,SLOT(SaveGame()));
    }
    else if(obj==pactSave1){
        alfa->setComplete("Load");
        connect(alfa,SIGNAL(SaveLoadChange()),this,SLOT(LoadGame()));
    }
    alfa->show();
}




void MainWindow::on_horizontalSlider_valueChanged(int value){
    GameMode=value;
}




void MainWindow::on_CloseButton_clicked(){
    if(GameMode!=PreGameMode){
        PreGameMode=GameMode;
        ui->Text->setText("<html><head/><body><p align=\"center\">Новая Игра</p></body></html>");
    }
    ui->stackedWidget->setCurrentIndex(0);
}




void MainWindow::on_Settings_clicked(){
    ui->stackedWidget->setCurrentIndex(2);
}




void MainWindow::UnitAbilities(){
    auto obj=QObject::sender();
    switch (game->Stats[game->unitid][0]){
        case 1:{
            if(obj==ui->FirstAbility){
                WorkInProgress();
                return;
            }
            else if(obj==ui->SecondAbility){
                WorkInProgress();
                return;
            }
            else if(obj==ui->ThirdAbility){
                WorkInProgress();
                return;
            }
            break;
        }
        case 2:{
            if(obj==ui->FirstAbility){
                WorkInProgress();
                return;
            }
            else if(obj==ui->SecondAbility){
                WorkInProgress();
                return;
            }
            else if(obj==ui->ThirdAbility){
                WorkInProgress();
                return;
            }
            break;
        }
        case 3:{
            if(obj==ui->FirstAbility){
                SkillsArrayId=6;
            }
            else if(obj==ui->SecondAbility){
                WorkInProgress();
                return;
            }
            else if(obj==ui->ThirdAbility){
                WorkInProgress();
                return;
            }
            break;
        }
    }
    SkillActivated=1;
    if(SkillsArray[SkillsArrayId]=="Огненная стрела"){
        if((game->Stats[game->unitid][11]-40)<0){
            SkillActivated=0;
            ConsoleLog("У вас не хватает манны для применения данного заклинания!!!");
        }else ConsoleLog("Выберите юнита");
    }
}



void MainWindow::on_MagicBook_clicked(){
    beta->AllMagic();
    beta->show();
}



void MainWindow::ActivateMagic(){
    ConsoleLog("Выберите юнита");
    MagicActivated=1;
}
