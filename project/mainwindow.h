#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <QHash>

#include "core.h"
//#include "recog.h"
#include "catalog.h"
#include <list>
#include "recogwidget.h"
#include "infowidget.h"
#include "childwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Catalog *catalog;
    VideoCapture *cam;
    std::list<Data> *last_recognized;

private slots:
    void set_centr_widget(int widget_id);

private:
    class ChildWidget *current_widget;

    class RecogWidget *recog_widget;
    class InfoWidget *info_widget;

    std::map<int, ChildWidget* > *widgets;


};

#endif // MAINWINDOW_H
