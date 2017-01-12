#ifndef RECOGWIDGET_H
#define RECOGWIDGET_H

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

#include "reciever.h"

#include "mainwindow.h"
#include "childwidget.h"

class RecogWidget: public ChildWidget
{
    Q_OBJECT

public:
    explicit RecogWidget(ChildWidget *parent = 0, class MainWindow *_mainwindow = 0);
    ~RecogWidget();

    void setContent();

//signals:
  //  void recognized(int id);

private:
    QLabel *img_label;
    QVBoxLayout *v_layout;
    QHBoxLayout *h_layout_1;
    QHBoxLayout *h_layout_2;
    QPushButton *set_button;
    QTimer *img_timer;
    bool recognition;
    class MainWindow *mainwindow;

    QImage cvMatToQImage(const cv::Mat &inMat);

private slots:
    void start_stream();
    void set_recog();
};

#endif // RECOGWIDGET_H
