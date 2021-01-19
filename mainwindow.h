#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <iostream>
#include <QString>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <math.h>
#include <QMouseEvent>
#include <QVector>
#include <QAction>
#include <QToolBar>
#include <QMenu>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QEvent>
#include <QTextCodec>
#include <QTableWidget>
namespace Ui {
    class MainWindow;
}
class SaveLoad;
class MagicBook;
class Magic;
class MainWindow : public QMainWindow{
    Q_OBJECT
    Magic *game;
    SaveLoad *alfa;
    MagicBook *beta;
    QAction *pactSave=new QAction(),*pactSave1=new QAction(),*pactSave2=new QAction(),*pactSave3=new QAction();
    ///Следующий юнит в списке ожидания
    int vecnext;
    ///Список ожидания
    QVector<int>vec;
    ///Фразы которые не будут вносится в список сохранений
    QVector<QString>CannotSave;
    ///Номер ячейки с id следующего юнита
    int nextunit;
    ///Есть ли граница у виджета на первом окне (0 - границы нет; 1 - граница есть)
    int WidgetBorder[3];
    ///Началась ли игра (true - да; false - нет)
    bool GameHasStarted;
    ///Лидерство героев (WIP)
    int Leadership[2];
    ///Переменные в которых хранится текущий игровой режим и превидущий игровой режим
    int GameMode,PreGameMode;
    ///Переменная демонстрирующая активирована ли магия
    int MagicActivated;
    int SkillActivated;
    ///Хранилища текстовых данных для вывода характеристик
    QVector<QString>WidgetTable;
    QVector<QString>WidgetTable1;
    ///Переменная в которой хранится номер текущего раунда
    int round;
    ///Переменная хранящая количества ходов до возможности повторного применения книги заклинаний
    int MagicBookRollback;
    ///Массив для наименований скилов
    QString SkillsArray[9];
    ///Переменная для обращения к конкретному скиллу
    int SkillsArrayId;
public:
        Ui::MainWindow *ui;
        explicit MainWindow(QWidget *parent = nullptr);
        ///Функция для вывода сообщений на экран игры
        void ConsoleLog(QString TextInConsole);
        ///Функции для отрисовки текущего расположения персонажей и их здоровья.
        void UpdateBoard();
        void UpdateBoard1();
        ///Функции для определения следующего юнита который будет ходить
        void NextUnit();
        void NextUnit1();
        ///Функция для вызова проверки нанесённого урона
        void AttackUnit(QString arr);
        ~MainWindow();
protected:
        virtual bool eventFilter ( QObject * watched, QEvent * event );
private slots:
        ///Функции для сохранения в файл или извлечения из файла информации
        void SaveGame();
        void LoadGame();
        void SaveLoad();
        ///Функция для пропуска хода
        void Skip();
        ///Функция начала новой игры или продолжения старой
        void NewGame();
        ///Функция которая помещает id юнитов в массив vec тем самым откладывая их ход
        void Wait();
        ///Функции длязадания виджетам границы при наведении на них
        void on_widget_3_destroyed();
        void on_widget_4_destroyed();
        void on_widget_5_destroyed();
        ///Функция возвращения на начальный экран
        void OnFirstScreen();
        ///Функция для извещения о том, что работы над данным функционалом всё ещё ведутся
        void WorkInProgress();
        ///Функция для изменения игрового режима
        void on_horizontalSlider_valueChanged(int value);
        ///Функции для выхода/перехода из/в меню настроек
        void on_CloseButton_clicked();
        void on_Settings_clicked();
        ///Функция обработки особых способностей юнитов
        void UnitAbilities();
        ///Слот для открытия магической книги
        void on_MagicBook_clicked();
        ///Слот для активации режима Магии
        void ActivateMagic();
};
#endif // MAINWINDOW_H
