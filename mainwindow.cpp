#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setMinimumHeight(600);
    this->setMinimumWidth(800);
    mainWidget = new QWidget;

    //初始化ImageView
    imageView = new ImageView(mainWidget);
    imageView->setGeometry(50,50,200,200);
    imageView->setDisplayStyle(imageView->STYLE::contain);//
    imageView->setLoadingPixmap(QPixmap(":/images/image_home_item_default.png"));
    imageView->setFailedPixmap(QPixmap(":/images/image_error_page.png"));
    imageView->setUrl("http://img.bss.csdn.net/201708102057303085.jpg");

    imageView1 = new ImageView(mainWidget);
    imageView1->setGeometry(600,50,200,200);
    imageView1->setLoadingPixmap(QPixmap(":/images/image_home_item_default.png"));
    imageView1->setFailedPixmap(QPixmap(":/images/image_error_page.png"));
    imageView1->setUrl(":/images/2.png");

    imageView2 = new ImageView(mainWidget);
    imageView2->setGeometry(300,50,200,300);
    imageView2->setDisplayStyle(imageView->STYLE::contain);
    imageView2->setLoadingPixmap(QPixmap(":/images/image_home_item_default.png"));
    imageView2->setFailedPixmap(QPixmap(":/images/image_error_page.png"));
//    imageView2->setUrl("https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1502693818433&di=a69ff3920cab95d21304839a26c88150&imgtype=0&src=http%3A%2F%2Fimg1.ph.126.net%2FX4ar4bAt08omFakxCycESg%3D%3D%2F1575696919644252610.jpg");
    imageView2->setUrl(":/images/1.png");

    imageView3 = new ImageView(mainWidget);
    imageView3->setGeometry(50,300,200,200);
    imageView3->setDisplayStyle(imageView->STYLE::cover);
    imageView3->setLoadingPixmap(QPixmap(":/images/image_home_item_default.png"));
    imageView3->setFailedPixmap(QPixmap(":/images/image_error_page.png"));
    imageView3->setUrl("http://img.bss.csdn.net/201708102057303085.jpg");
//    imageView3->setUrl(":/images/2.png");

    imageView4 = new ImageView(mainWidget);
    imageView4->setGeometry(300,400,200,200);
    imageView4->setDisplayStyle(imageView->STYLE::cover);
    imageView4->setLoadingPixmap(QPixmap(":/images/image_home_item_default.png"));
    imageView4->setFailedPixmap(QPixmap(":/images/image_error_page.png"));
    imageView4->setUrl("https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1502693818433&di=a69ff3920cab95d21304839a26c88150&imgtype=0&src=http%3A%2F%2Fimg1.ph.126.net%2FX4ar4bAt08omFakxCycESg%3D%3D%2F1575696919644252610.jpg");
//    imageView4->setUrl(":/images/1.png");

    this->setCentralWidget(mainWidget);

}

MainWindow::~MainWindow()
{

}

