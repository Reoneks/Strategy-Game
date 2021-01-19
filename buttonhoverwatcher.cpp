#include "buttonhoverwatcher.h"
ButtonHoverWatcher::ButtonHoverWatcher(QObject * parent):QObject(parent){}
bool ButtonHoverWatcher::eventFilter(QObject * watched, QEvent * event){
    QPushButton *button=qobject_cast<QPushButton*>(watched);
    if (!button)return false;
    if (event->type() == QEvent::Enter||event->type() == QEvent::Leave){
        button->parent()->destroyed();
        return true;
    }
    return false;
}
