#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QWheelEvent>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QTime>

#define DidianNumber 51
#define GuanjiandianNumber 105
#define DistdianNumber 5
#define EdgeNumber 223
#define XinxiNumber  64

//需要设置信息的点

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void wheelEvent(QWheelEvent *e);
    void didianzuobiao();
    void guanjiandianzuobiao();
    void biandejianli();
    void julijuzheng();
    void jisuanZuiduanLujing(int s);
    void lujingjisuan(int e,int s);
    void huaxian();
    void xinxijianli();
    void xinxizuobiao();
    void xinxitooltip();
    void sleep(unsigned int msec);
//  void createButton_1();

private slots:
    void on_label_linkActivated(const QString &link);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void onMenu_1_Triggered(QAction *action);

    void on_comboBox_activated(const QString &arg1);
    void huituClicked();

    void on_comboBox_2_activated(const QString &arg1);

    void on_lujing_button_clicked();

    void on_comboBox_4_activated(const QString &arg1);
    void edgeClicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QPoint last;
    QMenu *menu_s;
    QMenu *menu_e;

    QAction *action_s_nanjiao;
    QAction *action_s_tushuguan;

    QAction *action_e_nanjiao;
    QAction *action_e_tushuguan;

    double ditu_width;
    double ditu_height;
    int  ditu_x;
    int  ditu_y;
    struct Didian{
        double x,y;
    }didian[DidianNumber];
    struct Guanjiandian{
        double x,y;
        int duiyingjianzhu=-1;
    }guanjiandian[GuanjiandianNumber];
    struct Distdian{
        int x,y;
    }distdian[DistdianNumber];

    struct Edge{
        int start,end;
    }edge[EdgeNumber];

    int juli[GuanjiandianNumber][GuanjiandianNumber];
    double beishu=1;//当前倍数

    QPushButton *huitu_button[500];
    int huitu_button_cnt;
    QPushButton *edge_huitu[200];
    int edge_huitu_flag=0;
    int e_s=-1,e_e=-1; //边的绘制 临时用
    int edge_cnt=185;//绘制边时计数 临时用

    int mouse_flag=0;
    int s=23,e=24;//默认起点北门，终点南门

    int gengxin[GuanjiandianNumber];
    int lujing[GuanjiandianNumber];

    int zuiduan_lujing[GuanjiandianNumber];  //存最短路径

    int didian_cnt=0;
    QPixmap yuantu;

    QLabel *xinxi[XinxiNumber];

    struct Xinxi_weizhi{
        double x1,y1,x2,y2;
    }xinxi_weizhi[XinxiNumber];

    int xinxi_flag=0; //信息绘图用，临时
    int xinxi_cnt=0;

    int suofang_flag=0; //缩放时是否正在进行规划
};

#endif // MAINWINDOW_H
