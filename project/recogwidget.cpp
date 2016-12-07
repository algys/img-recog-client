#include "recogwidget.h"

QImage RecogWidget::cvMatToQImage(const cv::Mat &inMat){
    QImage image( inMat.data,
                  inMat.cols, inMat.rows,
                  static_cast<int>(inMat.step),
                  QImage::Format_RGB888 );

    return image.rgbSwapped();
}

RecogWidget::RecogWidget(ChildWidget *parent, MainWindow *_mainwindow):
    ChildWidget(parent), mainwindow(_mainwindow)
{
    img_label = new QLabel("Img label");
    set_button = new QPushButton("Start Recognition");
    img_timer = new QTimer(this);
    img_timer->setInterval(30);
    v_layout = new QVBoxLayout;
    h_layout_1 = new QHBoxLayout;
    h_layout_2 = new QHBoxLayout;

    h_layout_1->addWidget(img_label);
    h_layout_2->addWidget(set_button);
    v_layout->addLayout(h_layout_1);
    v_layout->addLayout(h_layout_2);
    this->setLayout(v_layout);

    connect(img_timer, SIGNAL(timeout()), SLOT(start_stream()));
    connect(set_button, SIGNAL(clicked(bool)), SLOT(set_recog()));

    recognition = false;
    set_recog();
}

RecogWidget::~RecogWidget(){
    delete v_layout;
}

void RecogWidget::set_recog(){
    if(recognition){
        img_timer->stop();
        recognition = false;
        set_button->setText("Start Recognition");
    }
    else{
        img_timer->start();
        recognition = true;
        set_button->setText("Stop Recognition");
    }
}

void RecogWidget::setContent(){
    recognition = false;
    set_recog();
}

void RecogWidget::start_stream(){
    Mat frame, curr;
    mainwindow->cam->operator >>(frame);

    if(recognition){
        cvtColor(frame, curr, CV_RGB2GRAY);
        Recog recog(mainwindow->catalog->get_captures(), curr);
        int id = -1;
        if((id = recog.tryrecog())!=-1){
            Object obj(recog.get_object());
            line( frame, (obj.get_points())[0] , (obj.get_points())[1] , Scalar( 0, 255, 0), 2 );
            line( frame, (obj.get_points())[1] , (obj.get_points())[2] , Scalar( 0, 255, 0), 2 );
            line( frame, (obj.get_points())[2] , (obj.get_points())[3] , Scalar( 0, 255, 0), 2 );
            line( frame, (obj.get_points())[3] , (obj.get_points())[0] , Scalar( 0, 255, 0), 2 );
            set_recog();
            mainwindow->last_recognized->push_back(id);
            emit change_widget(1);
            return;
        }
    }

    QImage qframe = cvMatToQImage(frame);
    img_label->setPixmap(QPixmap::fromImage(qframe));
}

