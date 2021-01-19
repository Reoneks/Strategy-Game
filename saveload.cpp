#include "saveload.h"
#include "ui_saveload.h"
SaveLoad::SaveLoad(QWidget *parent):QMainWindow(parent),ui(new Ui::SaveLoad){
    ui->setupUi(this);
    File="NoFile";
    Counter=0;
    ui->SaveLoadTable->horizontalHeader()->hide();
    ui->SaveLoadTable->verticalHeader()->hide();
    ui->SaveLoadTable->verticalHeader()->resizeSections(QHeaderView::Stretch);
    ui->SaveLoadTable->horizontalHeader()->setStretchLastSection(true);
    ui->SaveLoadTable->viewport()->installEventFilter(this);
    ui->SaveLoadTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_3->setVisible(true);
}
SaveLoad::~SaveLoad(){
    delete ui;
}
bool SaveLoad::eventFilter(QObject *object, QEvent *event){
    if(object==ui->SaveLoadTable->viewport()){
            if(event->type() == QEvent::MouseButtonDblClick){
                QMouseEvent *ms = static_cast<QMouseEvent *>(event);
                if(ms->buttons() & Qt::LeftButton){
                    QItemSelectionModel *select=ui->SaveLoadTable->selectionModel();
                    SaveLoadRow=select->currentIndex().row();
                    SaveLoadColumn=select->currentIndex().column();
                    QModelIndex index=ui->SaveLoadTable->model()->index(SaveLoadRow, SaveLoadColumn, QModelIndex());
                    if(ui->SaveLoadTable->model()->data(index).toString()!="Новое Сохранение")ui->pushButton_3->setDisabled(false);
                    else ui->pushButton_3->setDisabled(true);
                }
            }
    }
    return QObject::eventFilter(object, event);
}
void SaveLoad::setComplete(QString WhatToDo){
    this->WhatToDo=WhatToDo;
    if(WhatToDo=="Save"){
        ui->SaveLoadTable->insertRow(ui->SaveLoadTable->rowCount());
        ui->SaveLoadTable->setItem(ui->SaveLoadTable->rowCount()-1,0,new QTableWidgetItem("Новое Сохранение"));
        QString rem,rem1,rem2;
        QDir dir(QCoreApplication::applicationDirPath()+"\\Saves");
        if (dir.exists()){
            dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
            dir.setSorting(QDir::Name);
            QFileInfoList list=dir.entryInfoList();
            for (int i = 0; i < list.size(); ++i){
                QFileInfo fileInfo=list.at(i);
                rem=fileInfo.fileName();
                rem2=rem.split(" ")[2];
                rem1=rem.split(" ")[1];
                rem=rem.split(" ")[0];
                ui->SaveLoadTable->insertRow(ui->SaveLoadTable->rowCount());
                ui->SaveLoadTable->setItem(ui->SaveLoadTable->rowCount()-1,0,new QTableWidgetItem(rem+" \n"+"Дата: "+rem1+" \n"+"Время: "+rem2.split(".t")[0]));
            }
            ui->SaveLoadTable->resizeRowsToContents();
        }else{
            QGridLayout *hlayout=new QGridLayout;
            QLabel *label = new QLabel("Что-то пошло не так");
            QWidget *mainWindow = new QWidget;
            hlayout->addWidget(label);
            mainWindow->setLayout(hlayout);
            mainWindow->show();
            ui->SaveLoadTable->setDisabled(true);
            ui->pushButton->setDisabled(true);
            ui->pushButton_3->setDisabled(true);
            ui->SaveLoadTable->viewport()->removeEventFilter(this);
        }
    }else if(WhatToDo=="Load"){
        QString rem,rem1,rem2;
        QDir dir(QCoreApplication::applicationDirPath()+"\\Saves");
        if (dir.exists()){
            dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
            dir.setSorting(QDir::Name);
            QFileInfoList list=dir.entryInfoList();
            if(list.size()==0){
                QGridLayout *hlayout=new QGridLayout;
                QLabel *label = new QLabel("Сохранений не найдено");
                QWidget *mainWindow = new QWidget;
                hlayout->addWidget(label);
                mainWindow->setLayout(hlayout);
                mainWindow->show();
                ui->SaveLoadTable->setDisabled(true);
                ui->pushButton->setDisabled(true);
                ui->pushButton_3->setDisabled(true);
                ui->SaveLoadTable->viewport()->removeEventFilter(this);
            }else{
                for (int i = 0; i < list.size(); ++i){
                    QFileInfo fileInfo=list.at(i);
                    rem=fileInfo.fileName();
                    rem2=rem.split(" ")[2];
                    rem1=rem.split(" ")[1];
                    rem=rem.split(" ")[0];
                    ui->SaveLoadTable->insertRow(ui->SaveLoadTable->rowCount());
                    ui->SaveLoadTable->setItem(ui->SaveLoadTable->rowCount()-1,0,new QTableWidgetItem(rem+" \n"+"Дата: "+rem1+" \n"+"Время: "+rem2.split(".t")[0]));
                }
                ui->SaveLoadTable->resizeRowsToContents();
            }
        }else{
            QGridLayout *hlayout=new QGridLayout;
            QLabel *label = new QLabel("Что-то пошло не так");
            QWidget *mainWindow = new QWidget;
            hlayout->addWidget(label);
            mainWindow->setLayout(hlayout);
            mainWindow->show();
            ui->SaveLoadTable->setDisabled(true);
            ui->pushButton->setDisabled(true);
            ui->pushButton_3->setDisabled(true);
            ui->SaveLoadTable->viewport()->removeEventFilter(this);
        }
    }
}
void SaveLoad::on_pushButton_clicked(){
    File=ui->SaveLoadTable->takeItem(SaveLoadRow,SaveLoadColumn)->text();
    if(File=="Новое Сохранение"){
        QDate dateToday=QDate::currentDate();
        QTime timeNow=QTime::currentTime();
        File="Save "+dateToday.toString("dd.MM.yyyy")+" "+timeNow.toString("hh.mm.ss");
    }else File=File.split(" ")[0]+" "+File.split(" ")[2]+" "+File.split(" ")[4];
    File+=".txt";
    emit SaveLoadChange();
    close();
}
void SaveLoad::on_pushButton_2_clicked(){
    close();
}
void SaveLoad::on_pushButton_3_clicked(){
    File=ui->SaveLoadTable->takeItem(SaveLoadRow,SaveLoadColumn)->text();
    if(File!="Новое Сохранение"){
        File=File.split(" ")[0]+" "+File.split(" ")[2]+" "+File.split(" ")[4];
        QFile(QCoreApplication::applicationDirPath()+"\\Saves\\"+File+".txt").remove();
        QDir dir(QCoreApplication::applicationDirPath()+"\\Saves");
        if (dir.exists()){
            dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
            dir.setSorting(QDir::Name);
            QFileInfoList list=dir.entryInfoList();
            if(list.size()==0&&WhatToDo=="Load"){
                QGridLayout *hlayout=new QGridLayout;
                QLabel *label = new QLabel("Сохранений не найдено");
                QWidget *mainWindow = new QWidget;
                hlayout->addWidget(label);
                mainWindow->setLayout(hlayout);
                mainWindow->show();
                ui->SaveLoadTable->setDisabled(true);
                ui->pushButton->setDisabled(true);
                ui->pushButton_3->setDisabled(true);
                ui->SaveLoadTable->viewport()->removeEventFilter(this);
            }
        }else{
            QGridLayout *hlayout=new QGridLayout;
            QLabel *label = new QLabel("Что-то пошло не так");
            QWidget *mainWindow = new QWidget;
            hlayout->addWidget(label);
            mainWindow->setLayout(hlayout);
            mainWindow->show();
            ui->SaveLoadTable->setDisabled(true);
            ui->pushButton->setDisabled(true);
            ui->pushButton_3->setDisabled(true);
            ui->SaveLoadTable->viewport()->removeEventFilter(this);
        }
        ui->SaveLoadTable->removeRow(SaveLoadRow);
        SaveLoadRow=0;
        SaveLoadColumn=0;
    }
}
