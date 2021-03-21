#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(0,0,900,1200);
    setMouseTracking(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::colourPixel(QImage *background , QPoint p){

    int row = (p.rx() -10) / width_between_axes;
    int col = (p.ry() -10) / width_between_axes;

    QRgb gray;


    gray = qRgb(255,255,255);

    row *= width_between_axes;
    col *= width_between_axes;
    row += width_between_axes;
    col += width_between_axes;
    for ( int i =  row ; i < row + width_between_axes ; i++){
        for ( int j = col ; j < col + width_between_axes ; j++){
            background->setPixel(i , j , gray);
        }
    }

}

void MainWindow::paintEvent(QPaintEvent *event)
{

    QTime time;
    time.start();
    QImage background( size() ,QImage::Format_RGB32	 );
    QRgb gray = qRgb(255,255,255);

     background.fill(0);
    // fills with white
//    int width_between_axes= 9;
//    // draw horizontal
    for( int i = width_between_axes; i < 800 ; i+=width_between_axes){
        for( int j = width_between_axes;  j < 800;  j++){
            if ( i != width_between_axes)
            background.setPixel(i , j , gray);
        }
    }

//    //draw vertical
    for( int i = width_between_axes; i < 800 ; i+=width_between_axes){
        for( int j = width_between_axes;  j < 800;  j++){
            if ( i != width_between_axes)
            background.setPixel(j , i , gray);
        }
    }

    int mid_axe = 400 - 400 % width_between_axes;
    // draw horizontal thicker
    for ( int col = mid_axe; col <= mid_axe + width_between_axes; col++ ){
        for ( int row = width_between_axes ; row < 800; row ++ ){
            background.setPixel(row, col, gray);
        }
    }

    // draw vertical thicker
    for ( int col = mid_axe ; col <= mid_axe + width_between_axes; col++ ){
        for ( int row = width_between_axes ; row < 800; row ++ ){
            background.setPixel(col, row, gray);
        }
    }


    /*
     * Pixel data information
     * start_x or start_y : 2 * width_between_axes
     * number of pixels  : ((800 - width_between_axes) / width_between_axes)^2
     *
     *
     *
     */

    for ( QPoint mpoint : points )
        colourPixel(&background, mpoint);

    qDebug() << "time elapsed : " << time.elapsed();

    QPainter paint(this);
    paint.drawImage(0 , 0, background);

}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    width_between_axes = arg1;
    points.clear();
    this->update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    mpoint = event -> pos();
    int center = 400 - 400 % width_between_axes;

    ui->label_4->setText(QString::number((mpoint.x() - center) / width_between_axes));
    ui->label_5->setText(QString::number((center - mpoint.y()) / width_between_axes ));

    this->update();
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    mpoint = event -> pos();
    int center = 400 - 400 % width_between_axes;
    ui->label_4->setText(QString::number( (mpoint.x() - center) / width_between_axes ));
    ui->label_5->setText(QString::number((center - mpoint.y()) / width_between_axes ));
    if ( ((mpoint.x() - 10) % width_between_axes !=0) ||  ((mpoint.y() - 10) % width_between_axes !=0) )
        points.push_back(mpoint);
    this->update();
}




