#include "infowidget.h"

InfoWidget::InfoWidget(ChildWidget *parent, class MainWindow *_mainwindow):
    ChildWidget(parent), mainwindow(_mainwindow)
{
    img_label = new QLabel("Img label");
    img_label->setFixedSize(480, 300);
    img_label->setAlignment(Qt::AlignCenter);

    back_button = new QPushButton("Back To Recognition");

    v_layout_1 = new QVBoxLayout;
    v_layout_2 = new QVBoxLayout;
    h_layout_1 = new QHBoxLayout;

    text_1 = new QTextBrowser;
    text_2 = new QTextBrowser;

    v_layout_1->addWidget(img_label);
    v_layout_1->addWidget(text_1);

    v_layout_2->addWidget(text_2);
    v_layout_2->addWidget(back_button);
    connect(back_button, SIGNAL(clicked(bool)), SLOT(back_to_recog()));

    h_layout_1->addLayout(v_layout_1);
    h_layout_1->addLayout(v_layout_2);
    this->setLayout(h_layout_1);
}

void InfoWidget::setContent(){
    int img_id = mainwindow->last_recognized->back();
    QString text1;
    QString text2;

    DictData dictdata = (mainwindow->catalog->get_data());
    Data data = dictdata[img_id];

    QImage img = QImage(QString::fromStdString(data.path));
    img = img.scaledToHeight(300,Qt::SmoothTransformation);

    text1 = QString::fromStdString("Автор: ") + QString::fromStdString(data.author) + QString::fromStdString("\n");
    text1 += QString::fromStdString("Год создания: ") + QString::fromStdString(data.year) + QString::fromStdString("\n");
    text2 = QString::fromStdString(data.info) + QString::fromStdString("\n");
    text_1->setText(text1);
    text_2->setText(text2);
    img_label->setPixmap(QPixmap::fromImage(img));
}

void InfoWidget::back_to_recog(){
    emit change_widget(0);
}

InfoWidget::~InfoWidget(){
    delete img_label;
    delete back_button;
    delete text_1;
    delete text_2;
    delete v_layout_1;
    delete v_layout_2;
    delete h_layout_1;
}
