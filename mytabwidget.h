#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H
#include <QTabWidget>
#include <QDrag>
#include <QMimeData>
#include <QMap>
constexpr const char * const  msi_mimetype = "application/x-tabwidget.index";
struct tabInfo{
    tabInfo(const QString &_name,QWidget *_widget):name(_name),widget(_widget) {}
    QWidget *widget;
    QString name;
};
class MyTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    MyTabWidget(QWidget *parent = 0);
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
public slots:
    void startDragging();
private:
    static QMap<int,tabInfo> dragInfo;
    static int keyValue;
};

#endif // MYTABWIDGET_H
