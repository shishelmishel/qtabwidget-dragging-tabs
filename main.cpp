#include <QApplication>
#include <QLabel>
#include "mytabwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyTabWidget *tabWidget = new MyTabWidget;
    for(int i=1;i<11;i++) {
        QString tabText=QString("tabText_%1").arg(i);
        QString tabName=QString("t_%1").arg(i);
        tabWidget->addTab(new QLabel(tabText),tabName);
    }
    tabWidget->show();


    return a.exec();
}
