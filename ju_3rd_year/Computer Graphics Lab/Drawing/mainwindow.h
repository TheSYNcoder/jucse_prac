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
    QPoint mpoint;


    std::vector<QPoint> points;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void colourPixel( QImage* , QPoint);
    void mousePressEvent( QMouseEvent *event) override;
    void mouseMoveEvent( QMouseEvent *event) override;





    virtual void paintEvent(QPaintEvent *event);

private slots:
    void on_spinBox_valueChanged(int arg1);

//    void on_spinBox_textChanged(const QString &arg1);



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
