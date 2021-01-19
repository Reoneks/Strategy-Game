#include "magicbook.h"
#include "ui_magicbook.h"

MagicBook::MagicBook(QWidget *parent):QMainWindow(parent),ui(new Ui::MagicBook){
    ui->setupUi(this);
    QPalette pal;
    QPixmap map;
    map.load(":/new/prefix1/Scroll.png");
    map=map.scaled(700,470,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
    ui->centralwidget->setPalette(pal);
    ui->centralwidget->setAutoFillBackground(true);


    ui->Scroll->setStyleSheet("QTableWidget{background-color:transparent;border:none;}");
    ui->Scroll->horizontalHeader()->hide();
    ui->Scroll->verticalHeader()->hide();
    ui->Scroll->verticalHeader()->resizeSections(QHeaderView::Stretch);
    ui->Scroll->horizontalHeader()->setStretchLastSection(true);
    ui->Scroll->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Scroll->insertColumn(ui->Scroll->columnCount());
    ui->Scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    ui->Icons->setStyleSheet("QTableWidget{background-color:transparent;border:none;}");
    ui->Icons->horizontalHeader()->hide();
    ui->Icons->verticalHeader()->hide();
    ui->Icons->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Icons->insertColumn(ui->Icons->columnCount());
    ui->Icons->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Icons->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    ui->Scroll->viewport()->installEventFilter(this);
    Magic<<"Защита"<<"Огненная стрела";
    Icon<<":/new/prefix1/MagicShield.png"<<":/new/prefix1/FlameArrow.png";
}



MagicBook::~MagicBook(){
    delete ui;
}




bool MagicBook::eventFilter(QObject *object, QEvent *event){
    if(object==ui->Scroll->viewport()){
            if(event->type() == QEvent::MouseButtonDblClick){
                QMouseEvent *ms = static_cast<QMouseEvent *>(event);
                if(ms->buttons() & Qt::LeftButton){
                    QItemSelectionModel *select=ui->Scroll->selectionModel();
                    QModelIndex index=ui->Scroll->model()->index(select->currentIndex().row(), 0, QModelIndex());
                    MagicSelected=ui->Scroll->model()->data(index).toString();
                    for(int i=0;i<Magic.length();++i){
                        ui->Icons->removeRow(i);
                        ui->Scroll->removeRow(i);
                    }
                    emit MagicIsSelected();
                    close();
                }
            }
    }
    return QObject::eventFilter(object, event);
}



void MagicBook::AllMagic(){
    QBrush brush[2];
    QVector<QTableWidgetItem*>item;
    for(int i=0;i<Magic.length();++i){
        if(ui->Scroll->rowCount()<Magic.length()){
            ui->Scroll->insertRow(ui->Scroll->rowCount());
            ui->Icons->insertRow(ui->Icons->rowCount());
        }
        item.append(new QTableWidgetItem());
        brush[i].setTextureImage(QImage(Icon[i]));
        item[i]->setBackground(brush[i]);
        ui->Icons->setItem(i,0,item[i]);
        ui->Scroll->setItem(i,0,new QTableWidgetItem(Magic[i]));
        ui->Scroll->setRowHeight(i,84);
        ui->Icons->setRowHeight(i,84);
        ui->Icons->item(i,0)->setFlags(Qt::ItemIsSelectable);
    }
    ui->Scroll->setShowGrid(false);
    ui->Icons->setShowGrid(false);
    ui->Icons->setColumnWidth(0,149);
}
