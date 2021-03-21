#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    mpoint.setX(0);
    mpoint.setY(0);
    drawline=false;
    drawlineBesh=false;
    times=0;
    cnt=0;
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

void MainWindow::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


QPoint MainWindow::convertHelper(QPoint point){
    int row = (point.rx() -10) / width_between_axes;
    int col = (point.ry() -10) / width_between_axes;
    row *= width_between_axes;
    col *= width_between_axes;
    row += width_between_axes;
    col += width_between_axes;
    return QPoint(row,col);
}



void MainWindow::drawByDDA(QImage *background ){

    // convert to relative scale
//    QPoint p1 = convertHelper(point1);
//    QPoint p2 = convertHelper(point2);

    QTime time;

    time.start();

    // simulating 10000 times for error
    for ( int i = 0; i < 10000 ; i++ ){

        int x1 = point1.x() / width_between_axes;
        int y1 = point1.y() / width_between_axes;

        int x2 = point2.x() / width_between_axes;
        int y2 = point2.y() / width_between_axes;


        /*
         *  |m| < 1 -> next point ( xk , yk ) - > ( xk +1, yk + m )
         *  |m| > 1 -> next point ( xk , yk ) - > ( xk + 1/m , yk + 1)
         *  |m| = 1 -> next point ( xk , yk ) - > ( xk + 1 , yk +1 )
         *
         */



        int dx = x1 - x2;
        int dy = y1 - y2;

        int steps = 0; // number of steps to put pixels

        if(abs(dx)>abs(dy))
                steps=abs(dx);
            else
                steps=abs(dy);

        double Xinc=(double)dx/(double)steps;
        double Yinc=(double)dy/(double)steps;

        double x = x1 * width_between_axes + width_between_axes / 2;
        double y = y1 * width_between_axes + width_between_axes / 2;

        for ( int step = 0 ; step < steps; step++){
            x = x - Xinc * width_between_axes;
            y = y - Yinc * width_between_axes;
            colourPixel(background , QPoint((int)(x) , (int)(y)));
        }

    }

//    times.push_back(time.elapsed());

//    double sum = std::accumulate( times.begin() , times.end() , 0.0);
//    double mean = sum / times.size();
    times += time.elapsed();
    cnt++;
    double mean = (double) times / cnt;

    qDebug() << "DDA Line DRAWING TIME TAKEN : " << time.elapsed() << " AVG TIME : " << time.elapsed() / 1000 ;
    ui->label_8->setText("DDA TIME TAKEN : " + QString::number(time.elapsed()));
    ui->label_9->setText("AVG TIME TAKEN : " + QString::number(mean));

}


void MainWindow::drawByBress(QImage *background){

    QTime time;

    time.start();

    // simulating 10000 times for error
    for ( int i = 0; i < 10000 ; i++ ){

        int x1 = point1.x();
        int y1 = point1.y();

        int x2 = point2.x();
        int y2 = point2.y();

        int dx = x2 - x1;
        int dy = y2 - y1;


        // adjustting the scales according to the pixel size
        x1 = (x1 / width_between_axes) * width_between_axes + width_between_axes / 2;
        y1 = (y1 / width_between_axes) * width_between_axes + width_between_axes / 2;

        x2 = (x2 / width_between_axes) * width_between_axes + width_between_axes / 2;
        y2 = (y2 / width_between_axes) * width_between_axes + width_between_axes / 2;

        // adjusting the pixel value according to the pixel size
        int xinc = ( dx > 0 ) ? width_between_axes : -width_between_axes;
        int yinc = ( dy > 0 ) ? width_between_axes : -width_between_axes;

        dx = abs(dx);
        dy = abs(dy);

        // precalculating to decrease multiplication overhead
        int m_lt_1_incp_gt_0 = 2*dy - 2*dx;
        int m_lt_1_incp_lt_0 = 2*dy;
        int m_gt_1_incp_gt_0 = 2*dx - 2*dy;
        int m_gt_1_incp_lt_0 = 2*dx;

        /*
         * pk = dx.( d1 - d2 )
         * Recursion pk+1 = pk + 2.dy.xk - 2yk.dx + c
         *  p -> decision value
         *  |m| < 1
         *  p >=0 next point -> ( xk+1 , yk +1 ) , pk+1 = pk + 2.dy - 2.dx
         *  else next point -> ( xk +1 , yk ),
         *
         *
         */

        // Case for gentle slope ( m < 1 )
        if ( dx > dy ){
            int p = 2* dy - dx;  //p0
            int y = y1;
            for ( int x = x1; x!= x2; x+=xinc){
                colourPixel(background , QPoint(x,y));
                if ( p >= 0){
                    y += yinc;
                    p += m_lt_1_incp_gt_0;
                }
                else{
                    p += m_lt_1_incp_lt_0;
                }
//                p+= 2*dy;
            }
        }
        // Case for steep slope ( m >= 1 )
        else{
            int p = 2* dx - dy;   // p0
            int x = x1;
            for ( int y = y1; y!= y2; y+=yinc){
                colourPixel(background , QPoint(x,y));
                if ( p >= 0){
                    x += xinc;
//                    p -= 2*dy;
                    p += m_gt_1_incp_gt_0;
                }
//                p+= 2*dx;
                else{
                    p += m_gt_1_incp_lt_0;
                }
            }
        }
    }

//    times.push_back(time.elapsed());

//    double sum = std::accumulate( times.begin() , times.end() , 0.0);
//    double mean = sum / times.size();

    times += time.elapsed();
    cnt++;
    double mean = (double) times / cnt;

    qDebug() << "BRESS Line DRAWING TIME TAKEN : " << time.elapsed() << " AVG TIME : " << time.elapsed() / 1000 ;
    ui->label_8->setText("BRESS TIME TAKEN : " + QString::number(time.elapsed()));
    ui->label_9->setText("AVG TIME TAKEN : " + QString::number(mean));
}

void MainWindow::simulateClick(QImage *background, QPoint p){
    int row = (p.rx() -10) / width_between_axes;
    int col = (p.ry() -10) / width_between_axes;

    row *= width_between_axes;
    col *= width_between_axes;
    row += width_between_axes;
    col += width_between_axes;

    QRgb white, black;
    white = qRgb(255,255,255);
    black = qRgb(0,0,0);
    for ( int i =  row ; i < row + width_between_axes ; i++){
        for ( int j = col ; j < col + width_between_axes ; j++){
            background->setPixel(i , j , white);
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

    if ( drawline){
        drawByDDA(&background);
    }

    if ( drawlineBesh ){
        drawByBress(&background);
    }





      if ( mpoint.x() != 0 && mpoint.y() != 0 ){
          simulateClick(&background ,mpoint);
      }
//    for ( QPoint poit : points )
//        colourPixel(&background, poit);

    qDebug() << "time elapsed : " << time.elapsed();

    QPainter paint(this);
    paint.drawImage(0 , 0, background);

}


void MainWindow::mouseMoveEvent(QMouseEvent *event){
    mpoint = event -> pos();
    int center = 400 - 400 % width_between_axes;

//    ui->label_4->setText(QString::number((mpoint.x() - center) / width_between_axes));
//    ui->label_5->setText(QString::number((center - mpoint.y()) / width_between_axes ));

    this->update();
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    mpoint = event -> pos();
    int center = 400 - 400 % width_between_axes;
//    ui->label_4->setText(QString::number( (mpoint.x() - center) / width_between_axes ));
//    ui->label_5->setText(QString::number((center - mpoint.y()) / width_between_axes ));

    ui->label_7->setText(QString::number((mpoint.x() - center) / width_between_axes ) +","+QString::number((center - mpoint.y()) / width_between_axes ) );;
//    if ( ((mpoint.x() - 10) % width_between_axes !=0) ||  ((mpoint.y() - 10) % width_between_axes !=0) )
//        points.push_back(mpoint);

    this->update();
}



void MainWindow::on_pushButton_pressed()
{
    int center = 400 - 400 % width_between_axes;
    point1.setX(mpoint.x());
    point1.setY(mpoint.y());
    ui->label_3->setText(QString::number((mpoint.x() - center) / width_between_axes ) +","+QString::number((center - mpoint.y()) / width_between_axes ) );;

}

void MainWindow::on_pushButton_2_pressed()
{
    int center = 400 - 400 % width_between_axes;
    point2.setX(mpoint.x());
    point2.setY(mpoint.y());
    ui->label_4->setText(QString::number((mpoint.x() - center) / width_between_axes ) +","+QString::number((center - mpoint.y()) / width_between_axes ) );;
}



void MainWindow::on_spinBox_valueChanged(int arg1)
{
    width_between_axes = arg1;
    points.clear();
    this->update();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (  drawlineBesh == true){
        ui->checkBox->setChecked(false);
        arg1=0;

    }
   if ( arg1 == 2){

       drawline = true;
       drawlineBesh=false;
   }
   else{

       drawline=false;
   }
//   times.clear();
   times =0;
   cnt= 0;
   this->update();
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if ( drawline == true){
        ui->checkBox_2->setChecked(false);
        arg1=0;
    }
    if ( arg1 == 2){
        drawlineBesh =true;
        drawline=false;
    }
    else{
        drawlineBesh=false;
    }
//    times.clear();
    times =0;
    cnt =0 ;
    this->update();
}


