#ifndef SAVELOAD_H
#define SAVELOAD_H
#include <QMainWindow>
#include <QEvent>
#include <QMouseEvent>
#include <QTableWidget>
#include <QTextStream>
#include <QLabel>
#include <QGridLayout>
#include <QModelIndex>
#include <QDate>
#include <QDir>
#include <QDebug>
#include <QTime>
namespace Ui{
class SaveLoad;
}
class SaveLoad : public QMainWindow{
    Q_OBJECT
    int SaveLoadColumn,SaveLoadRow;
    Ui::SaveLoad *ui;
    int Counter;
    QString WhatToDo;
public:
    QString File;
    explicit SaveLoad(QWidget *parent = nullptr);
    ~SaveLoad();
    void setComplete(QString WhatToDo);
protected:
    virtual bool eventFilter ( QObject * watched, QEvent * event );
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
signals:
    void SaveLoadChange();
};
#endif // SAVELOAD_H
