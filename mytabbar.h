#ifndef MYTABBAR_H
#define MYTABBAR_H
#include <QTabBar>
#include <QMouseEvent>
#include <QApplication>
class MyTabBar : public QTabBar
{
    Q_OBJECT
public:
    MyTabBar(QWidget *parent=nullptr);
signals:
    void startDragging();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:
   QPoint dragStartPosition;
};

#endif // MYTABBAR_H
