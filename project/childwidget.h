#ifndef CHILDWIDGET_H
#define CHILDWIDGET_H

#include <QWidget>

class ChildWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChildWidget(QWidget *parent = 0);
    virtual void setContent(){}

signals:
    void change_widget(int widget_id);
};

#endif // CHILDWIDGET_H
