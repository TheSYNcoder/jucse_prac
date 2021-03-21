#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QTime>
#include <QMouseEvent>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    int width_between_axes=9;
    QPoint mpoint, point1, point2;
    bool drawline, drawlineBesh;



    std::vector<QPoint> points;
    int times;
    int cnt;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void delay();
    void colourPixel( QImage* , QPoint);
    void simulateClick( QImage* , QPoint);
    QPoint convertHelper(QPoint);

    void drawByDDA(QImage *);

    void drawByBress(QImage *);

    void mousePressEvent( QMouseEvent *event) override;
    void mouseMoveEvent( QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_pressed();

    void on_pushButton_2_pressed();



    void on_spinBox_valueChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
