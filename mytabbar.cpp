#include "mytabbar.h"

MyTabBar::MyTabBar(QWidget *parent):QTabBar(parent)
{

}
void MyTabBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragStartPosition = event->pos();
    }
    QTabBar::mousePressEvent(event);
}

void MyTabBar::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - dragStartPosition).manhattanLength()< QApplication::startDragDistance())
        return;
    emit startDragging();
}

