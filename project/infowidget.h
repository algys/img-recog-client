#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include <QTextBrowser>
#include <QScrollArea>

#include "core.h"
#include <list>

#include "mainwindow.h"
#include "childwidget.h"


class InfoWidget : public ChildWidget
{
    Q_OBJECT
public:
    explicit InfoWidget(ChildWidget *parent = 0, class MainWindow *_mainwindow = 0);
    ~InfoWidget();
    void setContent();

private slots:
    void back_to_recog();

private:
    class MainWindow *mainwindow;

    QLabel *img_label;
    QVBoxLayout *v_layout_1;
    QVBoxLayout *v_layout_2;
    QHBoxLayout *h_layout_1;

    QTextBrowser *text_1;
    QTextBrowser *text_2;

    QPushButton *back_button;
};

#endif // INFOWIDGET_H
