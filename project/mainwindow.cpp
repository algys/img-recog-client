#include "mainwindow.h"
/*
class WidgetContainer{
    WidgetContainer(RecogWidget* _first, InfoWidget* _second):
        first(_first), second(_second){
    RecogWidget *first;
    InfoWidget *second;
}
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setGeometry(30,30,960,540);

    cam = new VideoCapture(0);
    if(!(cam->isOpened())){
    }

    catalog = new Catalog();
    if(!(catalog->isOpened())){
    }

    widgets = new std::map<int, ChildWidget* >;
    widgets->operator [](0) = recog_widget;
    widgets->operator [](1) = info_widget;

    last_recognized = new std::list<Data>;
//    connect(recog_widget, SIGNAL(change_widget(int)), SLOT(set_centr_widget(int)));
//    connect(info_widget, SIGNAL(change_widget(int)), SLOT(set_centr_widget(int)));

    current_widget = 0;
    set_centr_widget(0);
}

MainWindow::~MainWindow(){
    delete current_widget;
}

void MainWindow::set_centr_widget(int widget_id){
    if(current_widget){
        disconnect(current_widget, SIGNAL(change_widget(int)), this, SLOT(set_centr_widget(int)));
        delete current_widget;
        current_widget = 0;
    }
    if(widget_id == 0) {
        current_widget = new RecogWidget(0, this);
    } else
    if(widget_id == 1) {
        current_widget = new InfoWidget(0, this);
    }
    current_widget->setContent();
    connect(current_widget, SIGNAL(change_widget(int)), SLOT(set_centr_widget(int)));
    setCentralWidget(current_widget);
}
