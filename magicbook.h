#ifndef MAGICBOOK_H
#define MAGICBOOK_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QDebug>
namespace Ui {
class MagicBook;
}

class MagicBook : public QMainWindow
{
    Q_OBJECT
    QVector<QString>Magic;
    QVector<QString>Icon;
public:
    explicit MagicBook(QWidget *parent = nullptr);
    ~MagicBook();
    QString MagicSelected;
    void AllMagic();
protected:
    virtual bool eventFilter ( QObject * watched, QEvent * event );
private:
    Ui::MagicBook *ui;
signals:
    void MagicIsSelected();
};

#endif // MAGICBOOK_H
