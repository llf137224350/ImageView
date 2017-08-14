#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "imageview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private :
    QWidget *mainWidget;
    ImageView *imageView;
    ImageView *imageView1;
    ImageView *imageView2;
    ImageView *imageView3;
    ImageView *imageView4;
};

#endif // MAINWINDOW_H
