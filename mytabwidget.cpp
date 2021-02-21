#include "mytabwidget.h"
#include "mytabbar.h"
QMap<int,tabInfo> MyTabWidget::dragInfo;
int MyTabWidget::keyValue=0;
MyTabWidget::MyTabWidget(QWidget *parent):QTabWidget(parent)
{
   resize(640,480);
   MyTabBar *newTabBar = new MyTabBar(this);
   connect(newTabBar,SIGNAL(startDragging()),this,SLOT(startDragging()));
   setTabBar(newTabBar);
   setAcceptDrops(true);
   setAttribute(Qt::WA_DeleteOnClose);
   connect(this,&QTabWidget::currentChanged,this,[this](int idx){
       if(idx==-1) close();
   });
   setTabsClosable(true);
   connect(this,&QTabWidget::tabCloseRequested,this,[this](int idx) {
       QWidget *w = widget(idx);
       removeTab(idx);
       delete w;
       if(count()==0) close();
   });
}
void MyTabWidget::startDragging()
{
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    int key=keyValue++;
    dragInfo.insert(key,{tabBar()->tabText(currentIndex()),currentWidget()});
    mimeData->setData(msi_mimetype,QByteArray::number(key));
    QPixmap pixmap = currentWidget()->grab();
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    Qt::DropAction action = drag->exec(Qt::CopyAction | Qt::MoveAction);
    if(action == Qt::IgnoreAction) {
        if(count()==1) return;
        MyTabWidget *tabWidget = new MyTabWidget;
        tabWidget->addTab(currentWidget(),tabText(currentIndex()));
        tabWidget->show();
    }
}
void MyTabWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat(msi_mimetype))
        event->acceptProposedAction();
}
void MyTabWidget::dropEvent(QDropEvent *event)
{
    int key = event->mimeData()->data(msi_mimetype).toInt();
    auto it = dragInfo.find(key);
    if(it==dragInfo.end())
        return;
    tabInfo info = it.value();
    dragInfo.erase(it);
    int idx =tabBar()->tabAt(event->pos());
    if(idx<count()&&idx>=0) {
        insertTab(idx,info.widget,info.name);
        setCurrentIndex(idx);
    }
    else {
        addTab(info.widget,info.name);
        setCurrentIndex(count()-1);
    }
    event->acceptProposedAction();
}
