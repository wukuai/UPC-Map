#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPixmap"
#include "QDebug"
#include "QPainter"
#include "QMenu"
#include "QAction"
#include "QComboBox"
#include "QString"
#include "QStack"
#include "QMessageBox"
#include "QLabel"
#include "QtMath"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{  
    ui->setupUi(this);

    ditu_width=ui->label->width()*1.331;
    ditu_height=ui->label->height()*1.331;

    ditu_x=0;
    ditu_y=0;

    QPixmap temp(":/ditu/ditu.png");
    temp.save("temp.png");
    yuantu=temp;
    yuantu=yuantu.scaled(ui->label->width()*1.331, ui->label->height()*1.331, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label->setGeometry(0,0,ditu_width,ditu_height);
    ui->label->setPixmap(yuantu);

    huitu_button_cnt=51;

    didianzuobiao();
    guanjiandianzuobiao();
    biandejianli();
    julijuzheng(); //距离矩阵建立

    xinxijianli(); //信息建立

    //提示信息
//    ui->label_4->setToolTip("楼体名称	南教楼\n"
//                            "建筑年代	2010\n"
//                            "建筑面积	27600m²\n"
//                            "建筑层数	5\n"
//                            "简  介：\n"
//                            "全楼共5层，2层设有多媒体值班室，5层设有绘图室。\n"
//                            "每层都有热水器，单层2台，双层1台。\n"
//                            "每天晚上10:30物业打扫卫生。");
//    ui->label_4->setText("我是label_4");
////  ui->label_4->setPalette(Qt::red);
////  ui->label_4->setBackgroundRole();
//    ui->label_4->setAutoFillBackground(Qt::red);
//    ui->label_4->setParent(ui->label);
//    ui->label_4->setGeometry(200,100,50,100);
//    ui->label_5->setToolTip("文理楼");
//    ui->label_6->setToolTip("图书馆\n行政楼");



//    边的绘制
//    for(int i=1;i<GuanjiandianNumber;i++){
//        edge_huitu[i]=new QPushButton(this);
//        connect(edge_huitu[i], SIGNAL(clicked()), this, SLOT(edgeClicked()));
//        edge_huitu[i]->setGeometry(guanjiandian[i].x,guanjiandian[i].y-33,20,20);
//        edge_huitu[i]->setText(QString::number(i));
//        edge_huitu[i]->show();
//    }
//    qDebug()<<"71->74"<<juli[71][74]<<juli[74][71];
//    qDebug()<<"71->44"<<juli[71][44]<<juli[44][71];
//    qDebug()<<"44->74"<<juli[44][74]<<juli[74][44];
//    QPushButton *testbug[5];
//    testbug[0]=new QPushButton(this);
//    testbug[1]=new QPushButton(this);
//    testbug[2]=new QPushButton(this);

//    testbug[0]->setGeometry(guanjiandian[71].x,guanjiandian[71].y,20,20);
//    testbug[0]->setText("71");
//    testbug[0]->show();
//     testbug[1]->setGeometry(guanjiandian[74].x,guanjiandian[74].y,20,20);
//     testbug[1]->setText("74");
//     testbug[1]->show();
//     testbug[2]->setGeometry(guanjiandian[44].x,guanjiandian[44].y,20,20);
//     testbug[2]->setText("44");
//     testbug[2]->show();

//     qDebug()<<"74-44 de pingfang"<<(guanjiandian[74].x-guanjiandian[44].x)
//             *(guanjiandian[74].x-guanjiandian[44].x)+
//             (guanjiandian[74].y-guanjiandian[44].y)
//             *(guanjiandian[74].y-guanjiandian[44].y);
//    qDebug()<<sqrt(5714);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e){
     last=e->globalPos();
    if(xinxi_flag==0){
         xinxi_flag=1;
         qDebug()<<"xinxi_weizhi["<<xinxi_cnt<<"].x1="<<e->x()<<",xinxi_weizhi["<<xinxi_cnt<<"].y1="<<e->y()<<";";
         huitu_button[xinxi_cnt]=new QPushButton(this);
//         connect(huitu_button[huitu_button_cnt], SIGNAL(clicked()), this, SLOT(huituClicked()));
         huitu_button[xinxi_cnt]->setObjectName(QString::number(xinxi_cnt));
         huitu_button[xinxi_cnt]->setText(QString::number(xinxi_cnt));
         huitu_button[xinxi_cnt]->setGeometry(e->x(),e->y(),20,20);
//         huitu_button[xinxi_cnt]->show();

    }
    else if(xinxi_flag==1){
        xinxi_flag=0;
        qDebug()<<"xinxi_weizhi["<<xinxi_cnt<<"].x2="<<e->x()<<",xinxi_weizhi["<<xinxi_cnt<<"].y2="<<e->y()<<";";
        xinxi_cnt++;
    }

}
void MainWindow::mouseMoveEvent(QMouseEvent *e){

    qDebug()<<"move";
      ditu_x=ui->label->x();
      ditu_y=ui->label->y();
      int dx=e->globalX()-last.x();
      int dy=e->globalY()-last.y();
      last=e->globalPos();
      ditu_x+=dx;
      ditu_y+=dy;
      ui->label->setGeometry(ditu_x,ditu_y,ui->label->width(),ui->label->height());
}
void MainWindow::mouseReleaseEvent(QMouseEvent *e){
//  qDebug()<<"release";
    mouse_flag=0;
}
void MainWindow::paintEvent(QPaintEvent *e){
//    qDebug()<<"paint";
//    QPainter painter(ui->label);
//    QPixmap pix(":/ditu/ditu.png");
//    painter.drawPixmap(0,0,ditu_width,ditu_height,pix);
//    update();
}

void MainWindow::on_label_linkActivated(const QString &link)
{

}

void MainWindow::on_pushButton_clicked()//放大地图
{
    if(suofang_flag==0){
        ditu_width*=1.1;
        ditu_height*=1.1;
        beishu=beishu*1.1;
        yuantu.load("temp.png");
        yuantu=yuantu.scaled(ditu_width, ditu_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label->setPixmap(yuantu);
        ui->label->setGeometry(ui->label->x(),ui->label->y(),ditu_width,ditu_height);
        for(int i=0;i<XinxiNumber;i++){
           xinxi[i]->setGeometry(xinxi_weizhi[i].x1*beishu,xinxi_weizhi[i].y1*beishu,(xinxi_weizhi[i].x2-xinxi_weizhi[i].x1)*beishu,(xinxi_weizhi[i].y2-xinxi_weizhi[i].y1)*beishu);
        }
     }
    else if(suofang_flag==1){
        QMessageBox *suofang_jinggao=new QMessageBox(this);
        suofang_jinggao->setText("正在进行路径规划，无法缩放，请稍候");
        suofang_jinggao->setWindowTitle("警告信息");
        suofang_jinggao->show();
    }

    for(int i=0;i<XinxiNumber;i++){
       xinxi[i]->setGeometry(xinxi_weizhi[i].x1*beishu,xinxi_weizhi[i].y1*beishu,(xinxi_weizhi[i].x2-xinxi_weizhi[i].x1)*beishu,(xinxi_weizhi[i].y2-xinxi_weizhi[i].y1)*beishu);
    }

}
void MainWindow::wheelEvent(QWheelEvent *e){
    if(e->delta()>0){
//        ditu_width*=1.1;
//        ditu_height*=1.1;
//        beishu*=1.1;
//        yuantu.load("temp.png");
//        yuantu=yuantu.scaled(ditu_width, ditu_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//        ui->label->setPixmap(yuantu);
//        ui->label->setGeometry(ui->label->x(),ui->label->y(),ditu_width,ditu_height);
        if(suofang_flag==0){
            ditu_width*=1.1;
            ditu_height*=1.1;
            beishu=beishu*1.1;
            yuantu.load("temp.png");
            yuantu=yuantu.scaled(ditu_width, ditu_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->label->setPixmap(yuantu);
            ui->label->setGeometry(ui->label->x(),ui->label->y(),ditu_width,ditu_height);
            for(int i=0;i<XinxiNumber;i++){
               xinxi[i]->setGeometry(xinxi_weizhi[i].x1*beishu,xinxi_weizhi[i].y1*beishu,(xinxi_weizhi[i].x2-xinxi_weizhi[i].x1)*beishu,(xinxi_weizhi[i].y2-xinxi_weizhi[i].y1)*beishu);
            }

         }
        else if(suofang_flag==1){
            QMessageBox *suofang_jinggao=new QMessageBox(this);
            suofang_jinggao->setText("正在进行路径规划，无法缩放，请稍候");
            suofang_jinggao->setWindowTitle("警告信息");
            suofang_jinggao->show();
        }

    }
    else if (e->delta()<0){

        if(suofang_flag==0){
            ditu_width*=0.9;
            ditu_height*=0.9;
            beishu=beishu*0.9;
            yuantu.load("temp.png");
            yuantu=yuantu.scaled(ditu_width, ditu_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->label->setPixmap(yuantu);
            ui->label->setGeometry(ui->label->x(),ui->label->y(),ditu_width,ditu_height);
            for(int i=0;i<XinxiNumber;i++){
               xinxi[i]->setGeometry(xinxi_weizhi[i].x1*beishu,xinxi_weizhi[i].y1*beishu,(xinxi_weizhi[i].x2-xinxi_weizhi[i].x1)*beishu,(xinxi_weizhi[i].y2-xinxi_weizhi[i].y1)*beishu);
            }
         }
        else if(suofang_flag==1){
            QMessageBox *suofang_jinggao=new QMessageBox(this);
            suofang_jinggao->setText("正在进行路径规划，无法缩放，请稍候");
            suofang_jinggao->setWindowTitle("警告信息");
            suofang_jinggao->show();
        }
    }
}

void MainWindow::on_pushButton_2_clicked()//缩小地图
{
    if(suofang_flag==0){
        ditu_width*=0.9;
        ditu_height*=0.9;
        beishu=beishu*0.9;
        yuantu.load("temp.png");
        yuantu=yuantu.scaled(ditu_width, ditu_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label->setPixmap(yuantu);
        ui->label->setGeometry(ui->label->x(),ui->label->y(),ditu_width,ditu_height);
        for(int i=0;i<XinxiNumber;i++){
           xinxi[i]->setGeometry(xinxi_weizhi[i].x1*beishu,xinxi_weizhi[i].y1*beishu,(xinxi_weizhi[i].x2-xinxi_weizhi[i].x1)*beishu,(xinxi_weizhi[i].y2-xinxi_weizhi[i].y1)*beishu);
        }
     }
    else if(suofang_flag==1){
        QMessageBox *suofang_jinggao=new QMessageBox(this);
        suofang_jinggao->setText("正在进行路径规划，无法缩放，请稍候");
        suofang_jinggao->setWindowTitle("警告信息");
        suofang_jinggao->show();
    }
}

void MainWindow::onMenu_1_Triggered(QAction *action)
{
    //起点
    if (action == action_s_nanjiao)
    {
        qDebug()<<"nanjiao qi dian";
    }
    else if (action == action_s_tushuguan)
    {
        qDebug()<<"tushuguan zhong dian";
    }
    //终点
    if (action == action_e_nanjiao)
    {
        qDebug()<<"nan jiao zhong dian";
    }
    else if (action == action_e_tushuguan)
    {
        qDebug()<<"tushuguan zhong dian";
    }
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{   
    if(arg1=="北门") s=23;
        else if(arg1=="南门")s=24;
        else if(arg1=="东门")s=25;
        else if(arg1=="西北门")s=26;
        else if(arg1=="工科A座")s=27;
        else if(arg1=="工科B座")s=28;
        else if(arg1=="工科C座")s=29;
        else if(arg1=="工科D座")s=30;
        else if(arg1=="工科E座")s=31;
        else if(arg1=="校医院")s=32;
        else if(arg1=="体育馆")s=33;
        else if(arg1=="体育场")s=34;
        else if(arg1=="东环 讲堂群")s=35;
        else if(arg1=="西环 讲堂群")s=36;
        else if(arg1=="南堂")s=37;
        else if(arg1=="图书馆行政楼")s=38;
        else if(arg1=="基础实验楼")s=39;
        else if(arg1=="多媒体中心")s=40;
        else if(arg1=="特种实验楼")s=41;
        else if(arg1=="南教北门")s=42;
        else if(arg1=="南教南门")s=43;
        else if(arg1=="南教西门")s=44;
        else if(arg1=="南教东门")s=45;
        else if(arg1=="文理楼西门")s=46;
        else if(arg1=="文理楼东门")s=47;
        else if(arg1=="留培楼")s=48;
        else if(arg1=="荟萃苑餐厅")s=49;
        else if(arg1=="唐岛湾餐厅")s=50;
        else if(arg1=="玉兰苑餐厅")s=0;
        else if(arg1=="1号公寓") s=1;
        else if(arg1=="2号公寓") s=2;
        else if(arg1=="3号公寓")s=3;
        else if(arg1=="4号公寓")s=4;
        else if(arg1=="5号公寓")s=5;
        else if(arg1=="6号公寓")s=6;
        else if(arg1=="7号公寓")s=7;
        else if(arg1=="8号公寓")s=8;
        else if(arg1=="9号公寓")s=9;
        else if(arg1=="10号公寓")s=10;
        else if(arg1=="11号公寓")s=11;
        else if(arg1=="12号公寓")s=12;
        else if(arg1=="13号公寓")s=13;
        else if(arg1=="14号公寓")s=14;
        else if(arg1=="15号公寓")s=15;
        else if(arg1=="16号公寓")s=16;
        else if(arg1=="17号公寓")s=17;
        else if(arg1=="18号公寓")s=18;
        else if(arg1=="19号公寓")s=19;
        else if(arg1=="研一公寓")s=20;
        else if(arg1=="研二公寓")s=21;
        else if(arg1=="研三公寓")s=22;
}
void MainWindow::didianzuobiao(){
    didian[ 0 ].x= 231 ,didian[ 0 ].y= 191 ;
    didian[ 1 ].x= 278 ,didian[ 1 ].y= 232 ;
    didian[ 2 ].x= 275 ,didian[ 2 ].y= 262 ;
    didian[ 3 ].x= 276 ,didian[ 3 ].y= 294 ;
    didian[ 4 ].x= 241 ,didian[ 4 ].y= 224 ;
    didian[ 5 ].x= 241 ,didian[ 5 ].y= 239 ;
    didian[ 6 ].x= 240 ,didian[ 6 ].y= 255 ;
    didian[ 7 ].x= 240 ,didian[ 7 ].y= 271 ;
    didian[ 8 ].x= 241 ,didian[ 8 ].y= 288 ;
    didian[ 9 ].x= 240 ,didian[ 9 ].y= 304 ;
    didian[ 10 ].x= 116 ,didian[ 10 ].y= 182 ;
    didian[ 11 ].x= 122 ,didian[ 11 ].y= 207 ;
    didian[ 12 ].x= 102 ,didian[ 12 ].y= 229 ;
    didian[ 13 ].x= 114 ,didian[ 13 ].y= 252 ;
    didian[ 14 ].x= 94 ,didian[ 14 ].y= 278 ;
    didian[ 15 ].x= 98 ,didian[ 15 ].y= 302 ;
    didian[ 16 ].x= 90 ,didian[ 16 ].y= 336 ;
    didian[ 17 ].x= 86 ,didian[ 17 ].y= 359 ;
    didian[ 18 ].x= 247 ,didian[ 18 ].y= 332 ;
    didian[ 19 ].x= 247 ,didian[ 19 ].y= 358 ;
    didian[ 20 ].x= 593 ,didian[ 20 ].y= 416 ;
    didian[ 21 ].x= 593 ,didian[ 21 ].y= 399 ;
    didian[ 22 ].x= 592 ,didian[ 22 ].y= 380 ;
    didian[ 23 ].x= 226 ,didian[ 23 ].y= 451 ;
    didian[ 24 ].x= 174 ,didian[ 24 ].y= 452 ;
    didian[ 25 ].x= 120 ,didian[ 25 ].y= 452 ;
    didian[ 26 ].x= 70 ,didian[ 26 ].y= 452 ;
    didian[ 27 ].x= 227 ,didian[ 27 ].y= 449 ;
    didian[ 28 ].x= 175 ,didian[ 28 ].y= 453 ;
    didian[ 29 ].x= 120 ,didian[ 29 ].y= 449 ;
    didian[ 30 ].x= 68 ,didian[ 30 ].y= 452 ;
    didian[ 31 ].x= 518 ,didian[ 31 ].y= 463 ;
    didian[ 32 ].x= 31 ,didian[ 32 ].y= 192 ;
    didian[ 33 ].x= 101 ,didian[ 33 ].y= 96 ;
    didian[ 34 ].x= 282 ,didian[ 34 ].y= 111 ;
    didian[ 35 ].x= 588 ,didian[ 35 ].y= 150 ;
    didian[ 36 ].x= 480 ,didian[ 36 ].y= 146 ;
    didian[ 37 ].x= 566 ,didian[ 37 ].y= 214 ;
    didian[ 38 ].x= 327 ,didian[ 38 ].y= 212 ;
    didian[ 39 ].x= 367 ,didian[ 39 ].y= 187 ;
    didian[ 40 ].x= 386 ,didian[ 40 ].y= 213 ;
    didian[ 41 ].x= 203 ,didian[ 41 ].y= 400 ;
    didian[ 42 ].x= 433 ,didian[ 42 ].y= 352 ;
    didian[ 43 ].x= 433 ,didian[ 43 ].y= 352 ;
    didian[ 44 ].x= 433 ,didian[ 44 ].y= 352 ;
    didian[ 45 ].x= 433 ,didian[ 45 ].y= 352 ;
    didian[ 46 ].x= 431 ,didian[ 46 ].y= 435 ;
    didian[ 47 ].x= 431 ,didian[ 47 ].y= 435 ;
    didian[ 48 ].x= 589 ,didian[ 48 ].y= 465 ;
    didian[ 49 ].x= 175 ,didian[ 49 ].y= 295 ;
    didian[ 50 ].x= 516 ,didian[ 50 ].y= 381 ;
}
void MainWindow::guanjiandianzuobiao(){

    guanjiandian[ 0 ].x= 230 ,guanjiandian[ 0 ].y= 209 ,guanjiandian[ 0 ].duiyingjianzhu= 0 ;
    guanjiandian[ 1 ].x= 295 ,guanjiandian[ 1 ].y= 232 ,guanjiandian[ 1 ].duiyingjianzhu= 1 ;
    guanjiandian[ 2 ].x= 295 ,guanjiandian[ 2 ].y= 261 ,guanjiandian[ 2 ].duiyingjianzhu= 2 ;
    guanjiandian[ 3 ].x= 294 ,guanjiandian[ 3 ].y= 291 ,guanjiandian[ 3 ].duiyingjianzhu= 3 ;
    guanjiandian[ 4 ].x= 211 ,guanjiandian[ 4 ].y= 222 ,guanjiandian[ 4 ].duiyingjianzhu= 4 ;
    guanjiandian[ 5 ].x= 210 ,guanjiandian[ 5 ].y= 238 ,guanjiandian[ 5 ].duiyingjianzhu= 5 ;
    guanjiandian[ 6 ].x= 211 ,guanjiandian[ 6 ].y= 254 ,guanjiandian[ 6 ].duiyingjianzhu= 6 ;
    guanjiandian[ 7 ].x= 211 ,guanjiandian[ 7 ].y= 269 ,guanjiandian[ 7 ].duiyingjianzhu= 7 ;
    guanjiandian[ 8 ].x= 210 ,guanjiandian[ 8 ].y= 286 ,guanjiandian[ 8 ].duiyingjianzhu= 8 ;
    guanjiandian[ 9 ].x= 211 ,guanjiandian[ 9 ].y= 303 ,guanjiandian[ 9 ].duiyingjianzhu= 9 ;
    guanjiandian[ 10 ].x= 158 ,guanjiandian[ 10 ].y= 181 ,guanjiandian[ 10 ].duiyingjianzhu= 10 ;
    guanjiandian[ 11 ].x= 153 ,guanjiandian[ 11 ].y= 206 ,guanjiandian[ 11 ].duiyingjianzhu= 11 ;
    guanjiandian[ 12 ].x= 149 ,guanjiandian[ 12 ].y= 229 ,guanjiandian[ 12 ].duiyingjianzhu= 12 ;
    guanjiandian[ 13 ].x= 145 ,guanjiandian[ 13 ].y= 254 ,guanjiandian[ 13 ].duiyingjianzhu= 13 ;
    guanjiandian[ 14 ].x= 141 ,guanjiandian[ 14 ].y= 277 ,guanjiandian[ 14 ].duiyingjianzhu= 14 ;
    guanjiandian[ 15 ].x= 136 ,guanjiandian[ 15 ].y= 300 ,guanjiandian[ 15 ].duiyingjianzhu= 15 ;
    guanjiandian[ 16 ].x= 133 ,guanjiandian[ 16 ].y= 335 ,guanjiandian[ 16 ].duiyingjianzhu= 16 ;
    guanjiandian[ 17 ].x= 123 ,guanjiandian[ 17 ].y= 360 ,guanjiandian[ 17 ].duiyingjianzhu= 17 ;
    guanjiandian[ 18 ].x= 209 ,guanjiandian[ 18 ].y= 331 ,guanjiandian[ 18 ].duiyingjianzhu= 18 ;
    guanjiandian[ 19 ].x= 209 ,guanjiandian[ 19 ].y= 355 ,guanjiandian[ 19 ].duiyingjianzhu= 19 ;
    guanjiandian[ 20 ].x= 550 ,guanjiandian[ 20 ].y= 415 ,guanjiandian[ 20 ].duiyingjianzhu= 20 ;
    guanjiandian[ 21 ].x= 549 ,guanjiandian[ 21 ].y= 399 ,guanjiandian[ 21 ].duiyingjianzhu= 21 ;
    guanjiandian[ 22 ].x= 550 ,guanjiandian[ 22 ].y= 380 ,guanjiandian[ 22 ].duiyingjianzhu= 22 ;
    guanjiandian[ 23 ].x= 526 ,guanjiandian[ 23 ].y= 44 ,guanjiandian[ 23 ].duiyingjianzhu= 23 ;

    //南门校准
    guanjiandian[ 24 ].x= 367-20 ,guanjiandian[ 24 ].y= 476 ,guanjiandian[ 24 ].duiyingjianzhu= 24 ;

    guanjiandian[ 25 ].x= 621 ,guanjiandian[ 25 ].y= 427 ,guanjiandian[ 25 ].duiyingjianzhu= 25 ;
    guanjiandian[ 26 ].x= 126 ,guanjiandian[ 26 ].y= 42 ,guanjiandian[ 26 ].duiyingjianzhu= 26 ;
    guanjiandian[ 27 ].x= 226 ,guanjiandian[ 27 ].y= 426 ,guanjiandian[ 27 ].duiyingjianzhu= 27 ;
    guanjiandian[ 28 ].x= 175 ,guanjiandian[ 28 ].y= 427 ,guanjiandian[ 28 ].duiyingjianzhu= 28 ;
    guanjiandian[ 29 ].x= 118 ,guanjiandian[ 29 ].y= 426 ,guanjiandian[ 29 ].duiyingjianzhu= 29 ;
    guanjiandian[ 30 ].x= 68 ,guanjiandian[ 30 ].y= 428 ,guanjiandian[ 30 ].duiyingjianzhu= 30 ;
    guanjiandian[ 31 ].x= 479 ,guanjiandian[ 31 ].y= 460 ,guanjiandian[ 31 ].duiyingjianzhu= 31 ;
    guanjiandian[ 32 ].x= 71 ,guanjiandian[ 32 ].y= 190 ,guanjiandian[ 32 ].duiyingjianzhu= 32 ;
    guanjiandian[ 33 ].x= 73 ,guanjiandian[ 33 ].y= 168 ,guanjiandian[ 33 ].duiyingjianzhu= 33 ;
    guanjiandian[ 34 ].x= 279 ,guanjiandian[ 34 ].y= 167 ,guanjiandian[ 34 ].duiyingjianzhu= 34 ;
    guanjiandian[ 35 ].x= 600 ,guanjiandian[ 35 ].y= 128 ,guanjiandian[ 35 ].duiyingjianzhu= 35 ;
    guanjiandian[ 36 ].x= 458 ,guanjiandian[ 36 ].y= 131 ,guanjiandian[ 36 ].duiyingjianzhu= 36 ;
    guanjiandian[ 37 ].x= 649 ,guanjiandian[ 37 ].y= 210 ,guanjiandian[ 37 ].duiyingjianzhu= 37 ;
    guanjiandian[ 38 ].x= 346 ,guanjiandian[ 38 ].y= 230 ,guanjiandian[ 38 ].duiyingjianzhu= 38 ;
    guanjiandian[ 39 ].x= 365 ,guanjiandian[ 39 ].y= 166 ,guanjiandian[ 39 ].duiyingjianzhu= 39 ;
    guanjiandian[ 40 ].x= 387 ,guanjiandian[ 40 ].y= 228 ,guanjiandian[ 40 ].duiyingjianzhu= 40 ;
    guanjiandian[ 41 ].x= 290 ,guanjiandian[ 41 ].y= 399 ,guanjiandian[ 41 ].duiyingjianzhu= 41 ;
    guanjiandian[ 42 ].x= 429 ,guanjiandian[ 42 ].y= 314 ,guanjiandian[ 42 ].duiyingjianzhu= 42 ;
    guanjiandian[ 43 ].x= 432 ,guanjiandian[ 43 ].y= 385 ,guanjiandian[ 43 ].duiyingjianzhu= 43 ;
    guanjiandian[ 44 ].x= 379 ,guanjiandian[ 44 ].y= 351 ,guanjiandian[ 44 ].duiyingjianzhu= 44 ;
    guanjiandian[ 45 ].x= 480 ,guanjiandian[ 45 ].y= 353 ,guanjiandian[ 45 ].duiyingjianzhu= 45 ;
    guanjiandian[ 46 ].x= 381 ,guanjiandian[ 46 ].y= 433 ,guanjiandian[ 46 ].duiyingjianzhu= 46 ;
    guanjiandian[ 47 ].x= 480 ,guanjiandian[ 47 ].y= 432 ,guanjiandian[ 47 ].duiyingjianzhu= 47 ;
    guanjiandian[ 48 ].x= 549 ,guanjiandian[ 48 ].y= 462 ,guanjiandian[ 48 ].duiyingjianzhu= 48 ;
    guanjiandian[ 49 ].x= 172 ,guanjiandian[ 49 ].y= 318 ,guanjiandian[ 49 ].duiyingjianzhu= 49 ;
    guanjiandian[ 50 ].x= 479 ,guanjiandian[ 50 ].y= 382 ,guanjiandian[ 50 ].duiyingjianzhu= 50 ;

    guanjiandian[ 51 ].x= 81 ,guanjiandian[ 51 ].y= 169 ;
    guanjiandian[ 52 ].x= 54 ,guanjiandian[ 52 ].y= 317 ;
    guanjiandian[ 53 ].x= 45 ,guanjiandian[ 53 ].y= 378 ;
    guanjiandian[ 54 ].x= 37 ,guanjiandian[ 54 ].y= 426 ;
    guanjiandian[ 55 ].x= 32 ,guanjiandian[ 55 ].y= 475 ;
    guanjiandian[ 56 ].x= 161 ,guanjiandian[ 56 ].y= 169 ;
    guanjiandian[ 57 ].x= 154 ,guanjiandian[ 57 ].y= 210 ;
    guanjiandian[ 58 ].x= 138 ,guanjiandian[ 58 ].y= 315 ;
    guanjiandian[ 59 ].x= 120 ,guanjiandian[ 59 ].y= 375 ;
    guanjiandian[ 60 ].x= 113 ,guanjiandian[ 60 ].y= 425 ;
    guanjiandian[ 61 ].x= 211 ,guanjiandian[ 61 ].y= 169 ;
    guanjiandian[ 62 ].x= 210 ,guanjiandian[ 62 ].y= 209 ;
    guanjiandian[ 63 ].x= 210 ,guanjiandian[ 63 ].y= 315 ;
    guanjiandian[ 64 ].x= 210 ,guanjiandian[ 64 ].y= 370 ;
    guanjiandian[ 65 ].x= 296 ,guanjiandian[ 65 ].y= 167 ;
    guanjiandian[ 66 ].x= 295 ,guanjiandian[ 66 ].y= 208 ;
    guanjiandian[ 67 ].x= 293 ,guanjiandian[ 67 ].y= 315 ;
    guanjiandian[ 68 ].x= 289 ,guanjiandian[ 68 ].y= 373 ;
    guanjiandian[ 69 ].x= 290 ,guanjiandian[ 69 ].y= 413 ;
    guanjiandian[ 70 ].x= 269 ,guanjiandian[ 70 ].y= 426 ;
    guanjiandian[ 71 ].x= 346 ,guanjiandian[ 71 ].y= 317 ;
    guanjiandian[ 72 ].x= 346 ,guanjiandian[ 72 ].y= 417 ;
    guanjiandian[ 73 ].x= 381 ,guanjiandian[ 73 ].y= 316 ;
    guanjiandian[ 74 ].x= 381 ,guanjiandian[ 74 ].y= 384 ;
    guanjiandian[ 75 ].x= 404 ,guanjiandian[ 75 ].y= 474 ;
    guanjiandian[ 76 ].x= 402 ,guanjiandian[ 76 ].y= 166 ;
    guanjiandian[ 77 ].x= 421 ,guanjiandian[ 77 ].y= 161 ;
    guanjiandian[ 78 ].x= 670 ,guanjiandian[ 78 ].y= 198 ;
    guanjiandian[ 79 ].x= 660 ,guanjiandian[ 79 ].y= 194 ;
    guanjiandian[ 80 ].x= 567 ,guanjiandian[ 80 ].y= 282 ;
    guanjiandian[ 81 ].x= 484 ,guanjiandian[ 81 ].y= 318 ;
    guanjiandian[ 82 ].x= 481 ,guanjiandian[ 82 ].y= 325 ;
    guanjiandian[ 83 ].x= 478 ,guanjiandian[ 83 ].y= 385 ;
    guanjiandian[ 84 ].x= 480 ,guanjiandian[ 84 ].y= 462 ;
    guanjiandian[ 85 ].x= 470 ,guanjiandian[ 85 ].y= 470 ;
    guanjiandian[ 86 ].x= 552 ,guanjiandian[ 86 ].y= 351 ;
    guanjiandian[ 87 ].x= 568 ,guanjiandian[ 87 ].y= 350 ;
    guanjiandian[ 88 ].x= 552 ,guanjiandian[ 88 ].y= 425 ;
    guanjiandian[ 89 ].x= 480 ,guanjiandian[ 89 ].y= 405 ;
    guanjiandian[ 90 ].x= 548 ,guanjiandian[ 90 ].y= 404 ;
    guanjiandian[ 91 ].x= 150 ,guanjiandian[ 91 ].y= 64 ;
    guanjiandian[ 92 ].x= 163 ,guanjiandian[ 92 ].y= 92 ;
    guanjiandian[ 93 ].x= 150 ,guanjiandian[ 93 ].y= 122 ;
    guanjiandian[ 94 ].x= 136 ,guanjiandian[ 94 ].y= 137 ;
    guanjiandian[ 95 ].x= 110 ,guanjiandian[ 95 ].y= 148 ;
    guanjiandian[ 96 ].x= 85 ,guanjiandian[ 96 ].y= 159 ;
    guanjiandian[ 97 ].x= 88 ,guanjiandian[ 97 ].y= 48 ;
    guanjiandian[ 98 ].x= 68 ,guanjiandian[ 98 ].y= 56 ;
    guanjiandian[ 99 ].x= 52 ,guanjiandian[ 99 ].y= 65 ;
    guanjiandian[ 100 ].x= 35 ,guanjiandian[ 100 ].y= 81 ;
    guanjiandian[ 101 ].x= 24 ,guanjiandian[ 101 ].y= 98 ;
    guanjiandian[ 102 ].x= 19 ,guanjiandian[ 102 ].y= 124 ;
    guanjiandian[ 103 ].x= 31 ,guanjiandian[ 103 ].y= 151 ;
    guanjiandian[ 104 ].x= 56 ,guanjiandian[ 104 ].y= 165 ;
}


void MainWindow::huituClicked(){
    huitu_button_cnt--;
    delete huitu_button[huitu_button_cnt];
}

void MainWindow::on_comboBox_2_activated(const QString &arg1)
{

}

void MainWindow::on_lujing_button_clicked()
{
    if(suofang_flag==0){
        if(s==e){
           QMessageBox *message=new QMessageBox(this);
           message->setText("起点和终点不能相同！");
           message->setWindowTitle("警告信息");
           message->show();
        }
        else {
            jisuanZuiduanLujing(s);
            lujingjisuan(e,s);
            huaxian();
        }
    }
    else if(suofang_flag==1){
        QMessageBox *message=new QMessageBox(this);
        message->setText("请等待本次路径规划完毕再进行下次路径规划！");
        message->setWindowTitle("警告信息");
        message->show();
    }


//  huitu();
}

void MainWindow::on_comboBox_4_activated(const QString &arg1)
{

    if(arg1=="北门") e=23;
        else if(arg1=="南门")e=24;
        else if(arg1=="东门")e=25;
        else if(arg1=="西北门")e=26;
        else if(arg1=="工科A座")e=27;
        else if(arg1=="工科B座")e=28;
        else if(arg1=="工科C座")e=29;
        else if(arg1=="工科D座")e=30;
        else if(arg1=="工科E座")e=31;
        else if(arg1=="校医院")e=32;
        else if(arg1=="体育馆")e=33;
        else if(arg1=="体育场")e=34;
        else if(arg1=="东环 讲堂群")e=35;
        else if(arg1=="西环 讲堂群")e=36;
        else if(arg1=="南堂")e=37;
        else if(arg1=="图书馆行政楼")e=38;
        else if(arg1=="基础实验楼")e=39;
        else if(arg1=="多媒体中心")e=40;
        else if(arg1=="特种实验楼")e=41;
        else if(arg1=="南教北门")e=42;
        else if(arg1=="南教南门")e=43;
        else if(arg1=="南教西门")e=44;
        else if(arg1=="南教东门")e=45;
        else if(arg1=="文理楼西门")e=46;
        else if(arg1=="文理楼东门")e=47;
        else if(arg1=="留培楼")e=48;
        else if(arg1=="荟萃苑餐厅")e=49;
        else if(arg1=="唐岛湾餐厅")e=50;
        else if(arg1=="玉兰苑餐厅")e=0;
        else if(arg1=="1号公寓") e=1;
        else if(arg1=="2号公寓") e=2;
        else if(arg1=="3号公寓")e=3;
        else if(arg1=="4号公寓")e=4;
        else if(arg1=="5号公寓")e=5;
        else if(arg1=="6号公寓")e=6;
        else if(arg1=="7号公寓")e=7;
        else if(arg1=="8号公寓")e=8;
        else if(arg1=="9号公寓")e=9;
        else if(arg1=="10号公寓")e=10;
        else if(arg1=="11号公寓")e=11;
        else if(arg1=="12号公寓")e=12;
        else if(arg1=="13号公寓")e=13;
        else if(arg1=="14号公寓")e=14;
        else if(arg1=="15号公寓")e=15;
        else if(arg1=="16号公寓")e=16;
        else if(arg1=="17号公寓")e=17;
        else if(arg1=="18号公寓")e=18;
        else if(arg1=="19号公寓")e=19;
        else if(arg1=="研一公寓")e=20;
        else if(arg1=="研二公寓")e=21;
        else if(arg1=="研三公寓")e=22;
}
void MainWindow::edgeClicked(){
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    int i=clickedButton->text().toInt();
    if(edge_huitu_flag==0){
        e_s=i;
        edge_huitu_flag=1;
    }
    else if(edge_huitu_flag==1){
        e_e=i;
        edge_huitu_flag=0;
        qDebug()<<"edge["<<edge_cnt<<"].start="<<e_s<<",edge["<<edge_cnt<<"].end="<<e_e<<";";
        edge_cnt++;
        //      edge[0].start=0,edge[0].end=1;
    }
}
void MainWindow::biandejianli(){
    edge[ 0 ].start= 0 ,edge[ 0 ].end= 62 ;
    edge[ 1 ].start= 0 ,edge[ 1 ].end= 66 ;
    edge[ 2 ].start= 1 ,edge[ 2 ].end= 66 ;
    edge[ 3 ].start= 1 ,edge[ 3 ].end= 67 ;
    edge[ 4 ].start= 2 ,edge[ 4 ].end= 66 ;
    edge[ 5 ].start= 2 ,edge[ 5 ].end= 67 ;
    edge[ 6 ].start= 3 ,edge[ 6 ].end= 66 ;
    edge[ 7 ].start= 3 ,edge[ 7 ].end= 67 ;
    edge[ 8 ].start= 4 ,edge[ 8 ].end= 62 ;
    edge[ 9 ].start= 4 ,edge[ 9 ].end= 63 ;
    edge[ 10 ].start= 4 ,edge[ 10 ].end= 62 ;
    edge[ 11 ].start= 4 ,edge[ 11 ].end= 63 ;
    edge[ 12 ].start= 5 ,edge[ 12 ].end= 62 ;
    edge[ 13 ].start= 5 ,edge[ 13 ].end= 63 ;
    edge[ 14 ].start= 6 ,edge[ 14 ].end= 62 ;
    edge[ 15 ].start= 6 ,edge[ 15 ].end= 63 ;
    edge[ 16 ].start= 7 ,edge[ 16 ].end= 62 ;
    edge[ 17 ].start= 7 ,edge[ 17 ].end= 63 ;
    edge[ 18 ].start= 8 ,edge[ 18 ].end= 62 ;
    edge[ 19 ].start= 8 ,edge[ 19 ].end= 63 ;
    edge[ 20 ].start= 9 ,edge[ 20 ].end= 62 ;
    edge[ 21 ].start= 9 ,edge[ 21 ].end= 63 ;
    edge[ 22 ].start= 10 ,edge[ 22 ].end= 56 ;
    edge[ 23 ].start= 10 ,edge[ 23 ].end= 57 ;
    edge[ 24 ].start= 11 ,edge[ 24 ].end= 56 ;
    edge[ 25 ].start= 11 ,edge[ 25 ].end= 57 ;
    edge[ 26 ].start= 11 ,edge[ 26 ].end= 62 ;
    edge[ 27 ].start= 12 ,edge[ 27 ].end= 57 ;
    edge[ 28 ].start= 12 ,edge[ 28 ].end= 58 ;
    edge[ 29 ].start= 13 ,edge[ 29 ].end= 57 ;
    edge[ 30 ].start= 13 ,edge[ 30 ].end= 58 ;
    edge[ 31 ].start= 14 ,edge[ 31 ].end= 57 ;
    edge[ 32 ].start= 14 ,edge[ 32 ].end= 58 ;
    edge[ 33 ].start= 15 ,edge[ 33 ].end= 57 ;
    edge[ 34 ].start= 15 ,edge[ 34 ].end= 58 ;
    edge[ 35 ].start= 16 ,edge[ 35 ].end= 58 ;
    edge[ 36 ].start= 16 ,edge[ 36 ].end= 59 ;
    edge[ 37 ].start= 17 ,edge[ 37 ].end= 58 ;
    edge[ 38 ].start= 17 ,edge[ 38 ].end= 59 ;
    edge[ 39 ].start= 18 ,edge[ 39 ].end= 63 ;
    edge[ 40 ].start= 18 ,edge[ 40 ].end= 64 ;
    edge[ 41 ].start= 19 ,edge[ 41 ].end= 63 ;
    edge[ 42 ].start= 19 ,edge[ 42 ].end= 64 ;
    edge[ 43 ].start= 20 ,edge[ 43 ].end= 88 ;
    edge[ 44 ].start= 20 ,edge[ 44 ].end= 90 ;
    edge[ 45 ].start= 21 ,edge[ 45 ].end= 90 ;
    edge[ 46 ].start= 21 ,edge[ 46 ].end= 86 ;
    edge[ 47 ].start= 22 ,edge[ 47 ].end= 90 ;
    edge[ 48 ].start= 22 ,edge[ 48 ].end= 86 ;
    edge[ 49 ].start= 23 ,edge[ 49 ].end= 36 ;
    edge[ 50 ].start= 23 ,edge[ 50 ].end= 35 ;
    edge[ 51 ].start= 24 ,edge[ 51 ].end= 75 ;
    edge[ 52 ].start= 24 ,edge[ 52 ].end= 46 ;
    edge[ 53 ].start= 24 ,edge[ 53 ].end= 72 ;
    edge[ 54 ].start= 25 ,edge[ 54 ].end= 88 ;
    edge[ 55 ].start= 26 ,edge[ 55 ].end= 97 ;
    edge[ 56 ].start= 26 ,edge[ 56 ].end= 91 ;
    edge[ 57 ].start= 27 ,edge[ 57 ].end= 70 ;
    edge[ 58 ].start= 27 ,edge[ 58 ].end= 60 ;
    edge[ 59 ].start= 28 ,edge[ 59 ].end= 70 ;
    edge[ 60 ].start= 28 ,edge[ 60 ].end= 60 ;
    edge[ 61 ].start= 29 ,edge[ 61 ].end= 70 ;
    edge[ 62 ].start= 29 ,edge[ 62 ].end= 60 ;
    edge[ 63 ].start= 30 ,edge[ 63 ].end= 60 ;
    edge[ 64 ].start= 30 ,edge[ 64 ].end= 54 ;
    edge[ 65 ].start= 31 ,edge[ 65 ].end= 84 ;
    edge[ 66 ].start= 31 ,edge[ 66 ].end= 89 ;
    edge[ 67 ].start= 32 ,edge[ 67 ].end= 52 ;
    edge[ 68 ].start= 32 ,edge[ 68 ].end= 33 ;
    edge[ 69 ].start= 32 ,edge[ 69 ].end= 51 ;
    edge[ 70 ].start= 33 ,edge[ 70 ].end= 52 ;
    edge[ 71 ].start= 33 ,edge[ 71 ].end= 51 ;
    edge[ 72 ].start= 34 ,edge[ 72 ].end= 65 ;
    edge[ 73 ].start= 34 ,edge[ 73 ].end= 61 ;
    edge[ 74 ].start= 35 ,edge[ 74 ].end= 79 ;
    edge[ 75 ].start= 36 ,edge[ 75 ].end= 77 ;
    edge[ 76 ].start= 37 ,edge[ 76 ].end= 79 ;
    edge[ 77 ].start= 37 ,edge[ 77 ].end= 80 ;
    edge[ 78 ].start= 38 ,edge[ 78 ].end= 71 ;
    edge[ 79 ].start= 38 ,edge[ 79 ].end= 40 ;
    edge[ 80 ].start= 38 ,edge[ 80 ].end= 73 ;
    edge[ 81 ].start= 39 ,edge[ 81 ].end= 76 ;
    edge[ 82 ].start= 39 ,edge[ 82 ].end= 65 ;
    edge[ 83 ].start= 40 ,edge[ 83 ].end= 73 ;
    edge[ 84 ].start= 40 ,edge[ 84 ].end= 71 ;
    edge[ 85 ].start= 41 ,edge[ 85 ].end= 68 ;
    edge[ 86 ].start= 41 ,edge[ 86 ].end= 69 ;
    edge[ 87 ].start= 41 ,edge[ 87 ].end= 70 ;
    edge[ 88 ].start= 42 ,edge[ 88 ].end= 73 ;
    edge[ 89 ].start= 42 ,edge[ 89 ].end= 81 ;
    edge[ 90 ].start= 43 ,edge[ 90 ].end= 74 ;
    edge[ 91 ].start= 43 ,edge[ 91 ].end= 83 ;
    edge[ 92 ].start= 44 ,edge[ 92 ].end= 73 ;
    edge[ 93 ].start= 44 ,edge[ 93 ].end= 74 ;
    edge[ 94 ].start= 44 ,edge[ 94 ].end= 71 ;
    edge[ 95 ].start= 44 ,edge[ 95 ].end= 72 ;
    edge[ 96 ].start= 45 ,edge[ 96 ].end= 82 ;
    edge[ 97 ].start= 45 ,edge[ 97 ].end= 82 ;
    edge[ 98 ].start= 45 ,edge[ 98 ].end= 81 ;
    edge[ 99 ].start= 45 ,edge[ 99 ].end= 83 ;
    edge[ 100 ].start= 46 ,edge[ 100 ].end= 72 ;
    edge[ 101 ].start= 46 ,edge[ 101 ].end= 74 ;
    edge[ 102 ].start= 46 ,edge[ 102 ].end= 75 ;
    edge[ 103 ].start= 46 ,edge[ 103 ].end= 24 ;
    edge[ 104 ].start= 47 ,edge[ 104 ].end= 89 ;
    edge[ 105 ].start= 47 ,edge[ 105 ].end= 84 ;
    edge[ 106 ].start= 48 ,edge[ 106 ].end= 88 ;
    edge[ 107 ].start= 49 ,edge[ 107 ].end= 63 ;
    edge[ 108 ].start= 49 ,edge[ 108 ].end= 58 ;
    edge[ 109 ].start= 83 ,edge[ 109 ].end= 50 ;
    edge[ 110 ].start= 50 ,edge[ 110 ].end= 89 ;
    edge[ 111 ].start= 50 ,edge[ 111 ].end= 81 ;
    edge[ 112 ].start= 97 ,edge[ 112 ].end= 98 ;
    edge[ 113 ].start= 98 ,edge[ 113 ].end= 99 ;
    edge[ 114 ].start= 99 ,edge[ 114 ].end= 100 ;
    edge[ 115 ].start= 100 ,edge[ 115 ].end= 101 ;
    edge[ 116 ].start= 101 ,edge[ 116 ].end= 102 ;
    edge[ 117 ].start= 102 ,edge[ 117 ].end= 103 ;
    edge[ 118 ].start= 103 ,edge[ 118 ].end= 104 ;
    edge[ 119 ].start= 104 ,edge[ 119 ].end= 51 ;
    edge[ 120 ].start= 51 ,edge[ 120 ].end= 96 ;
    edge[ 121 ].start= 96 ,edge[ 121 ].end= 95 ;
    edge[ 122 ].start= 95 ,edge[ 122 ].end= 94 ;
    edge[ 123 ].start= 94 ,edge[ 123 ].end= 93 ;
    edge[ 124 ].start= 93 ,edge[ 124 ].end= 92 ;
    edge[ 125 ].start= 92 ,edge[ 125 ].end= 91 ;
    edge[ 126 ].start= 51 ,edge[ 126 ].end= 56 ;
    edge[ 127 ].start= 56 ,edge[ 127 ].end= 61 ;
    edge[ 128 ].start= 61 ,edge[ 128 ].end= 65 ;
    edge[ 129 ].start= 65 ,edge[ 129 ].end= 76 ;
    edge[ 130 ].start= 76 ,edge[ 130 ].end= 77 ;
    edge[ 131 ].start= 77 ,edge[ 131 ].end= 36 ;
    edge[ 132 ].start= 79 ,edge[ 132 ].end= 78 ;
    edge[ 133 ].start= 79 ,edge[ 133 ].end= 80 ;
    edge[ 134 ].start= 51 ,edge[ 134 ].end= 52 ;
    edge[ 135 ].start= 52 ,edge[ 135 ].end= 53 ;
    edge[ 136 ].start= 53 ,edge[ 136 ].end= 54 ;
    edge[ 137 ].start= 54 ,edge[ 137 ].end= 55 ;
    edge[ 138 ].start= 56 ,edge[ 138 ].end= 57 ;
    edge[ 139 ].start= 57 ,edge[ 139 ].end= 58 ;
    edge[ 140 ].start= 58 ,edge[ 140 ].end= 59 ;
    edge[ 141 ].start= 59 ,edge[ 141 ].end= 60 ;
    edge[ 142 ].start= 61 ,edge[ 142 ].end= 62 ;
    edge[ 143 ].start= 62 ,edge[ 143 ].end= 63 ;
    edge[ 144 ].start= 63 ,edge[ 144 ].end= 64 ;
    edge[ 145 ].start= 65 ,edge[ 145 ].end= 66 ;
    edge[ 146 ].start= 66 ,edge[ 146 ].end= 67 ;
    edge[ 147 ].start= 67 ,edge[ 147 ].end= 68 ;
    edge[ 148 ].start= 68 ,edge[ 148 ].end= 69 ;
    edge[ 149 ].start= 57 ,edge[ 149 ].end= 62 ;
    edge[ 150 ].start= 62 ,edge[ 150 ].end= 66 ;
    edge[ 151 ].start= 52 ,edge[ 151 ].end= 58 ;
    edge[ 152 ].start= 58 ,edge[ 152 ].end= 63 ;
    edge[ 153 ].start= 63 ,edge[ 153 ].end= 67 ;
    edge[ 154 ].start= 53 ,edge[ 154 ].end= 59 ;
    edge[ 155 ].start= 59 ,edge[ 155 ].end= 64 ;
    edge[ 156 ].start= 64 ,edge[ 156 ].end= 68 ;
    edge[ 157 ].start= 54 ,edge[ 157 ].end= 60 ;
    edge[ 158 ].start= 60 ,edge[ 158 ].end= 70 ;
    edge[ 159 ].start= 70 ,edge[ 159 ].end= 69 ;
    edge[ 160 ].start= 55 ,edge[ 160 ].end= 24 ;
    edge[ 161 ].start= 67 ,edge[ 161 ].end= 71 ;
    edge[ 162 ].start= 71 ,edge[ 162 ].end= 73 ;
    edge[ 163 ].start= 73 ,edge[ 163 ].end= 81 ;
    edge[ 164 ].start= 81 ,edge[ 164 ].end= 80 ;
    edge[ 165 ].start= 80 ,edge[ 165 ].end= 79 ;
    edge[ 166 ].start= 72 ,edge[ 166 ].end= 74 ;
    edge[ 167 ].start= 74 ,edge[ 167 ].end= 83 ;
    edge[ 168 ].start= 82 ,edge[ 168 ].end= 83 ;
    edge[ 169 ].start= 83 ,edge[ 169 ].end= 89 ;
    edge[ 170 ].start= 83 ,edge[ 170 ].end= 84 ;
    edge[ 171 ].start= 84 ,edge[ 171 ].end= 85 ;
    edge[ 172 ].start= 85 ,edge[ 172 ].end= 75 ;
    edge[ 173 ].start= 82 ,edge[ 173 ].end= 81 ;
    edge[ 174 ].start= 86 ,edge[ 174 ].end= 90 ;
    edge[ 175 ].start= 90 ,edge[ 175 ].end= 88 ;
    edge[ 176 ].start= 88 ,edge[ 176 ].end= 48 ;
    edge[ 177 ].start= 82 ,edge[ 177 ].end= 86 ;
    edge[ 178 ].start= 86 ,edge[ 178 ].end= 87 ;

    edge[ 179 ].start= 80 ,edge[ 179 ].end= 87 ; //取消80-86

    edge[ 180 ].start= 72 ,edge[ 180 ].end= 46 ;
    edge[ 181 ].start= 72 ,edge[ 181 ].end= 75 ;
    edge[182].start=71,edge[182].end=72;
    edge[183].start=72,edge[183].end=24;
    edge[184].start=72,edge[184].end=74;
    //补边
    edge[ 185 ].start= 1 ,edge[ 185 ].end= 2 ;
    edge[ 186 ].start= 2 ,edge[ 186 ].end= 3 ;
    edge[ 187 ].start= 4 ,edge[ 187 ].end= 5 ;
    edge[ 188 ].start= 5 ,edge[ 188 ].end= 6 ;
    edge[ 189 ].start= 6 ,edge[ 189 ].end= 7 ;
    edge[ 190 ].start= 7 ,edge[ 190 ].end= 8 ;
    edge[ 191 ].start= 8 ,edge[ 191 ].end= 9 ;
    edge[ 192 ].start= 10 ,edge[ 192 ].end= 11 ;
    edge[ 193 ].start= 11 ,edge[ 193 ].end= 12 ;
    edge[ 194 ].start= 12 ,edge[ 194 ].end= 13 ;
    edge[ 195 ].start= 13 ,edge[ 195 ].end= 14 ;
    edge[ 196 ].start= 14 ,edge[ 196 ].end= 15 ;
    edge[ 197 ].start= 32 ,edge[ 197 ].end= 33 ;
    edge[ 198 ].start= 32 ,edge[ 198 ].end= 52 ;
    edge[ 199 ].start= 52 ,edge[ 199 ].end= 53 ;
    edge[ 200 ].start= 22 ,edge[ 200 ].end= 21 ;
    edge[ 201 ].start= 21 ,edge[ 201 ].end= 88 ;
    edge[ 202 ].start= 83 ,edge[ 202 ].end= 50 ;
    edge[ 203 ].start= 45 ,edge[ 203 ].end= 45 ;
    edge[ 204 ].start= 45 ,edge[ 204 ].end= 50 ;
    edge[ 205 ].start= 50 ,edge[ 205 ].end= 47 ;
    edge[ 206 ].start= 47 ,edge[ 206 ].end= 31 ;
    edge[ 207 ].start= 46 ,edge[ 207 ].end= 44 ;
    edge[ 208 ].start= 30 ,edge[ 208 ].end= 29 ;
    edge[ 209 ].start= 28 ,edge[ 209 ].end= 60 ;
    edge[ 210 ].start= 28 ,edge[ 210 ].end= 29 ;
    edge[ 211 ].start= 28 ,edge[ 211 ].end= 27 ;
    edge[ 212 ].start= 70 ,edge[ 212 ].end= 27 ;
    edge[ 213 ].start= 39 ,edge[ 213 ].end= 34 ;
    edge[ 214 ].start= 39 ,edge[ 214 ].end= 76 ;
    edge[215].start=71,edge[215].end=24;
    edge[216].start=69,edge[216].end=72;
    edge[217].start=72,edge[217].end=46;
    edge[218].start=72,edge[218].end=24;

    //留培楼补边
//    edge[ 185 ].start= 83 ,edge[ 185 ].end= 89 ;
//    edge[ 186 ].start= 89 ,edge[ 186 ].end= 90 ;
//    edge[ 187 ].start= 90 ,edge[ 187 ].end= 48 ;

    edge[ 219 ].start= 83 ,edge[ 219 ].end= 89 ;
    edge[ 220 ].start= 89 ,edge[ 220 ].end= 90 ;
    edge[ 221 ].start= 90 ,edge[ 221 ].end= 48 ;

    edge[ 222 ].start= 71 ,edge[ 222 ].end= 74 ;
//            24 72
}
void MainWindow::julijuzheng(){
    for(int i=0;i<GuanjiandianNumber;i++){
        for(int j=0;j<GuanjiandianNumber;j++){
            juli[i][j]=0;
        }
    }
    for(int i=0;i<EdgeNumber;i++){
        juli[edge[i].start][edge[i].end]=juli[edge[i].end][edge[i].start]=sqrt(
                (guanjiandian[edge[i].start].x-guanjiandian[edge[i].end].x)*
                (guanjiandian[edge[i].start].x-guanjiandian[edge[i].end].x)+
                (guanjiandian[edge[i].start].y-guanjiandian[edge[i].end].y)*
                (guanjiandian[edge[i].start].y-guanjiandian[edge[i].end].y));
    }
    qDebug()<<"72->24:"<<juli[72][24]<<juli[24][72];
    qDebug()<<"72->46:"<<juli[72][46]<<juli[46][72];
    qDebug()<<"46->24:"<<juli[46][24]<<juli[24][46];
//    juli[71][72]=juli[72][71]=1; //应该是多少？
}
void MainWindow::jisuanZuiduanLujing(int s)  //最短路径迪杰斯特拉算法
{
    //传入起点s,计算其到每一个点的最短路径
    //待插入其它代码
    bool fangwen_flag[GuanjiandianNumber]; //访问标记
    for(int i=0;i<GuanjiandianNumber;i++)
     {
        if(juli[s][i]>0&&i!=s)
        {
            gengxin[i]=juli[s][i];
            lujing[i]=s;
         }
        else
        {
            gengxin[i]=INT_MAX;
            lujing[i]=-1;
        }
        fangwen_flag[i]=false;
        lujing[s]=s;
        gengxin[s]=0;
    }
    fangwen_flag[s]=true;
    for(int i=1;i<GuanjiandianNumber;i++)
     {
        int min=INT_MAX;
        int temp;
        for(int j=0;j<GuanjiandianNumber;j++)
         {
            if(fangwen_flag[j]==false&&gengxin[j]<min)
            {
                min=gengxin[j];
                temp=j;
            }
        }
        fangwen_flag[temp]=true;
        for(int k=0;k<GuanjiandianNumber;k++)
         {
            if(fangwen_flag[k]==false&&juli[temp][k]>0&&min+juli[temp][k]<gengxin[k])
            {
                gengxin[k]=min+juli[temp][k];
                lujing[k]=temp;
            }
        }
    }
}
void MainWindow::lujingjisuan(int e,int s)   //e是终点
{
    for(int i=0;i<GuanjiandianNumber;i++)
        zuiduan_lujing[i]=-1;
    int cnt=0;
    QTextStream cout(stdout,  QIODevice::WriteOnly);
    QStack<int> stack;
    int u=e;
    while(e!=s)
    {
        stack.push(e);
        e=lujing[e];
    }
    stack.push(e);
    while(!stack.empty())
    {
        cout<<stack.top()<<" ";
        zuiduan_lujing[cnt++]=stack.top();
        stack.pop();
    }
}
void MainWindow::huaxian(){
        int s=this->s;
        int e=this->e;
        //画线
        suofang_flag=1;
        QPixmap pixmap_yuantu(":/ditu/ditu.png");
//      yuantu=yuantu.scaled(ditu_width, ditu_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        pixmap_yuantu = pixmap_yuantu.scaled(ditu_width,ditu_height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
         QPainter llpainter(&pixmap_yuantu);
    //   llpainter.setPen(QPen(Qt::red, 9, Qt::SolidLine));
         llpainter.setRenderHint(QPainter::Antialiasing);//平滑直线
//         llpainter.setPen(QPen(Qt::red,9,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin));
         llpainter.setPen(QPen(Qt::red,5,Qt::DotLine,Qt::RoundCap,Qt::MiterJoin)); //设置虚线

         if(s==0)
             llpainter.drawLine(231*beishu, (191-33)*beishu, guanjiandian[s].x*beishu, (guanjiandian[s].y-33)*beishu);
         else  if(s!=23&&s!=24&&s!=25&&s!=26)
         llpainter.drawLine(didian[s].x*beishu, (didian[s].y-33)*beishu, guanjiandian[s].x*beishu, (guanjiandian[s].y-33)*beishu);

         for (int i=1;zuiduan_lujing[i]!=-1;i++)
            {
                llpainter.drawLine(guanjiandian[zuiduan_lujing[i-1]].x*beishu, (guanjiandian[zuiduan_lujing[i-1]].y-33)*beishu, guanjiandian[zuiduan_lujing[i]].x*beishu, (guanjiandian[zuiduan_lujing[i]].y-33)*beishu);
                //延时
                sleep(200);
                QPixmap pixmap = pixmap_yuantu.scaled(ditu_width,ditu_height);
                QPainter painter(this);
                yuantu=pixmap;
                ui->label->setPixmap(yuantu);
                yuantu.save("temp.png");
            }

            llpainter.setPen(QPen(Qt::red,5,Qt::DotLine,Qt::RoundCap,Qt::MiterJoin)); //设置虚线
            if(e==0)
                llpainter.drawLine(231*beishu, (191-33)*beishu, guanjiandian[e].x*beishu, (guanjiandian[e].y-33)*beishu);
            else if(e!=23&&e!=24&&e!=25&&e!=26)
            llpainter.drawLine(didian[e].x*beishu, (didian[e].y-33)*beishu, guanjiandian[e].x*beishu, (guanjiandian[e].y-33)*beishu);
            llpainter.end();

            QPixmap pixmap = pixmap_yuantu.scaled(ditu_width,ditu_height); 
            QPainter painter(this);
            yuantu=pixmap;
            ui->label->setPixmap(yuantu);
            yuantu.save("temp.png");
            suofang_flag=0;
}
//void MainWindow::paintEvent(QPaintEvent *event)
//{
//    /*加载背景图*/
//    QPixmap pixmap_yuantu(":/beijing/yuanjiaobiaoti.png");
//    pixmap_yuantu = pixmap_yuantu.scaled(xx_yuan,yy_yuan);
//    if(hualujing[2]==-1&&hualujing[1]!=-1)
//        lujing=0;
//    if (lujing==1)//需要绘制路径
//    {
//        QPainter llpainter(&pixmap_yuantu);
////      llpainter.setPen(QPen(Qt::red, 9, Qt::SolidLine));
//        llpainter.setRenderHint(QPainter::Antialiasing);//平滑直线
//        llpainter.setPen(QPen(Qt::red,12,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin));

//        for (int i=1;hualujing[i]!=-1;i++)
//        {
//           llpainter.drawLine(ludian_x[hualujing[i-1]], ludian_y[hualujing[i-1]], ludian_x[hualujing[i]], ludian_y[hualujing[i]]);
//            //延时
////            sleep(100); ??paint一直执行
//        }

//        llpainter.end();
//        QPixmap pixmap = pixmap_yuantu.scaled(xx,yy);
//        QPainter painter(this);
//        painter.drawPixmap(0, 0, pixmap);
//    }

//    else if(lujing ==0){   //不需要绘制路径
////        qDebug()<<"bu xu yao hui zhi lu jing";
//        QPixmap pixmap = pixmap_yuantu.scaled(xx,yy);
//        QPainter painter(this);
//        painter.drawPixmap(0, 0, pixmap);
//    }
//    update();
//}

void MainWindow::on_pushButton_3_clicked()
{
    if(suofang_flag==0)
    {
        QPixmap temp(":/ditu/ditu.png");
        temp.save("temp.png");
        yuantu=temp;
        yuantu=yuantu.scaled(ui->label->width(), ui->label->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label->setPixmap(yuantu);
    }
    else if(suofang_flag==1){
        QMessageBox *qingchu_jinggao=new QMessageBox(this);
        qingchu_jinggao->setText("请等待路径规划完毕再清除!");
        qingchu_jinggao->setWindowTitle("警告信息");
        qingchu_jinggao->show();
    }

}


//bool MainWindow::event(QEvent *event)
// {
//     if (event->type() == QEvent::ToolTip) {
//         QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
//         int index = itemAt(helpEvent->pos());
//         if (index != -1) {
//             QToolTip::showText(helpEvent->globalPos(), shapeItems[index].toolTip());
//         } else {
//             QToolTip::hideText();
//             event->ignore();
//         }

//         return true;
//     }
//     return QWidget::event(event);
// }

void MainWindow::xinxijianli(){
    //信息标签初始化祖先
    for (int i=0;i<XinxiNumber;i++){
//       xinxi[i]->setParent(ui->label);
        xinxi[i]=new QLabel(ui->label);
    }

    xinxizuobiao();
    xinxitooltip();

//    信息位置与大小初始化
    for(int i=0;i<XinxiNumber;i++){
       xinxi[i]->setGeometry(xinxi_weizhi[i].x1,xinxi_weizhi[i].y1,xinxi_weizhi[i].x2-xinxi_weizhi[i].x1,xinxi_weizhi[i].y2-xinxi_weizhi[i].y1);
//       xinxi[i]->setAutoFillBackground(true);
      //xinxi[i]->setText(QString::number(i));
       xinxi[i]->show();
    }
}
void MainWindow::xinxizuobiao (){ //存储信息位置坐标x1，y1,x2,y2
    xinxi_weizhi[ 0 ].x1= 217 ,xinxi_weizhi[ 0 ].y1= 158 ;
    xinxi_weizhi[ 0 ].x2= 247 ,xinxi_weizhi[ 0 ].y2= 180 ;
    xinxi_weizhi[ 1 ].x1= 268 ,xinxi_weizhi[ 1 ].y1= 198 ;
    xinxi_weizhi[ 1 ].x2= 286 ,xinxi_weizhi[ 1 ].y2= 222 ;
    xinxi_weizhi[ 2 ].x1= 268 ,xinxi_weizhi[ 2 ].y1= 228 ;
    xinxi_weizhi[ 2 ].x2= 285 ,xinxi_weizhi[ 2 ].y2= 251 ;
    xinxi_weizhi[ 3 ].x1= 269 ,xinxi_weizhi[ 3 ].y1= 259 ;
    xinxi_weizhi[ 3 ].x2= 285 ,xinxi_weizhi[ 3 ].y2= 284 ;
    xinxi_weizhi[ 4 ].x1= 220 ,xinxi_weizhi[ 4 ].y1= 195 ;
    xinxi_weizhi[ 4 ].x2= 257 ,xinxi_weizhi[ 4 ].y2= 208 ;
    xinxi_weizhi[ 5 ].x1= 218 ,xinxi_weizhi[ 5 ].y1= 211 ;
    xinxi_weizhi[ 5 ].x2= 259 ,xinxi_weizhi[ 5 ].y2= 223 ;
    xinxi_weizhi[ 6 ].x1= 217 ,xinxi_weizhi[ 6 ].y1= 225 ;
    xinxi_weizhi[ 6 ].x2= 258 ,xinxi_weizhi[ 6 ].y2= 239 ;
    xinxi_weizhi[ 7 ].x1= 216 ,xinxi_weizhi[ 7 ].y1= 240 ;
    xinxi_weizhi[ 7 ].x2= 258 ,xinxi_weizhi[ 7 ].y2= 255 ;
    xinxi_weizhi[ 8 ].x1= 214 ,xinxi_weizhi[ 8 ].y1= 256 ;
    xinxi_weizhi[ 8 ].x2= 259 ,xinxi_weizhi[ 8 ].y2= 272 ;
    xinxi_weizhi[ 9 ].x1= 221 ,xinxi_weizhi[ 9 ].y1= 276 ;
    xinxi_weizhi[ 9 ].x2= 258 ,xinxi_weizhi[ 9 ].y2= 287 ;
    xinxi_weizhi[ 10 ].x1= 90 ,xinxi_weizhi[ 10 ].y1= 150 ;
    xinxi_weizhi[ 10 ].x2= 138 ,xinxi_weizhi[ 10 ].y2= 169 ;
    xinxi_weizhi[ 11 ].x1= 98 ,xinxi_weizhi[ 11 ].y1= 174 ;
    xinxi_weizhi[ 11 ].x2= 144 ,xinxi_weizhi[ 11 ].y2= 192 ;
    xinxi_weizhi[ 12 ].x1= 78 ,xinxi_weizhi[ 12 ].y1= 198 ;
    xinxi_weizhi[ 12 ].x2= 123 ,xinxi_weizhi[ 12 ].y2= 215 ;
    xinxi_weizhi[ 13 ].x1= 90 ,xinxi_weizhi[ 13 ].y1= 221 ;
    xinxi_weizhi[ 13 ].x2= 136 ,xinxi_weizhi[ 13 ].y2= 239 ;
    xinxi_weizhi[ 14 ].x1= 72 ,xinxi_weizhi[ 14 ].y1= 246 ;
    xinxi_weizhi[ 14 ].x2= 117 ,xinxi_weizhi[ 14 ].y2= 264 ;
    xinxi_weizhi[ 15 ].x1= 79 ,xinxi_weizhi[ 15 ].y1= 270 ;
    xinxi_weizhi[ 15 ].x2= 124 ,xinxi_weizhi[ 15 ].y2= 286 ;
    xinxi_weizhi[ 16 ].x1= 65 ,xinxi_weizhi[ 16 ].y1= 304 ;
    xinxi_weizhi[ 16 ].x2= 120 ,xinxi_weizhi[ 16 ].y2= 321 ;
    xinxi_weizhi[ 17 ].x1= 60 ,xinxi_weizhi[ 17 ].y1= 327 ;
    xinxi_weizhi[ 17 ].x2= 111 ,xinxi_weizhi[ 17 ].y2= 344 ;
    xinxi_weizhi[ 18 ].x1= 220 ,xinxi_weizhi[ 18 ].y1= 300 ;
    xinxi_weizhi[ 18 ].x2= 280 ,xinxi_weizhi[ 18 ].y2= 318 ;
    xinxi_weizhi[ 19 ].x1= 220 ,xinxi_weizhi[ 19 ].y1= 325 ;
    xinxi_weizhi[ 19 ].x2= 280 ,xinxi_weizhi[ 19 ].y2= 344 ;
    xinxi_weizhi[ 20 ].x1= 565 ,xinxi_weizhi[ 20 ].y1= 388 ;
    xinxi_weizhi[ 20 ].x2= 615 ,xinxi_weizhi[ 20 ].y2= 399 ;
    xinxi_weizhi[ 21 ].x1= 565 ,xinxi_weizhi[ 21 ].y1= 369 ;
    xinxi_weizhi[ 21 ].x2= 617 ,xinxi_weizhi[ 21 ].y2= 383 ;
    xinxi_weizhi[ 22 ].x1= 565 ,xinxi_weizhi[ 22 ].y1= 351 ;
    xinxi_weizhi[ 22 ].x2= 615 ,xinxi_weizhi[ 22 ].y2= 366 ;
    xinxi_weizhi[ 23 ].x1= 66 ,xinxi_weizhi[ 23 ].y1= 44 ;
    xinxi_weizhi[ 23 ].x2= 129 ,xinxi_weizhi[ 23 ].y2= 110 ;
    xinxi_weizhi[ 24 ].x1= 500 ,xinxi_weizhi[ 24 ].y1= 178 ;
    xinxi_weizhi[ 24 ].x2= 625 ,xinxi_weizhi[ 24 ].y2= 200 ;
    xinxi_weizhi[ 25 ].x1= 439 ,xinxi_weizhi[ 25 ].y1= 131 ;
    xinxi_weizhi[ 25 ].x2= 623 ,xinxi_weizhi[ 25 ].y2= 168 ;
    xinxi_weizhi[ 26 ].x1= 475 ,xinxi_weizhi[ 26 ].y1= 98 ;
    xinxi_weizhi[ 26 ].x2= 588 ,xinxi_weizhi[ 26 ].y2= 132 ;
    xinxi_weizhi[ 27 ].x1= 613 ,xinxi_weizhi[ 27 ].y1= 63 ;
    xinxi_weizhi[ 27 ].x2= 715 ,xinxi_weizhi[ 27 ].y2= 107 ;
    xinxi_weizhi[ 28 ].x1= 672 ,xinxi_weizhi[ 28 ].y1= 124 ;
    xinxi_weizhi[ 28 ].x2= 724 ,xinxi_weizhi[ 28 ].y2= 159 ;
    xinxi_weizhi[ 29 ].x1= 316 ,xinxi_weizhi[ 29 ].y1= 180 ;
    xinxi_weizhi[ 29 ].x2= 359 ,xinxi_weizhi[ 29 ].y2= 198 ;
    xinxi_weizhi[ 30 ].x1= 316 ,xinxi_weizhi[ 30 ].y1= 200 ;
    xinxi_weizhi[ 30 ].x2= 335 ,xinxi_weizhi[ 30 ].y2= 241 ;
    xinxi_weizhi[ 31 ].x1= 364 ,xinxi_weizhi[ 31 ].y1= 180 ;
    xinxi_weizhi[ 31 ].x2= 417 ,xinxi_weizhi[ 31 ].y2= 201 ;
    xinxi_weizhi[ 32 ].x1= 316 ,xinxi_weizhi[ 32 ].y1= 151 ;
    xinxi_weizhi[ 32 ].x2= 415 ,xinxi_weizhi[ 32 ].y2= 173 ;
    xinxi_weizhi[ 33 ].x1= 184 ,xinxi_weizhi[ 33 ].y1= 29 ;
    xinxi_weizhi[ 33 ].x2= 243 ,xinxi_weizhi[ 33 ].y2= 99 ;
    xinxi_weizhi[ 34 ].x1= 155 ,xinxi_weizhi[ 34 ].y1= 105 ;
    xinxi_weizhi[ 34 ].x2= 244 ,xinxi_weizhi[ 34 ].y2= 136 ;
    xinxi_weizhi[ 35 ].x1= 257 ,xinxi_weizhi[ 35 ].y1= 44 ;
    xinxi_weizhi[ 35 ].x2= 302 ,xinxi_weizhi[ 35 ].y2= 133 ;
    xinxi_weizhi[ 36 ].x1= 312 ,xinxi_weizhi[ 36 ].y1= 46 ;
    xinxi_weizhi[ 36 ].x2= 357 ,xinxi_weizhi[ 36 ].y2= 134 ;
    xinxi_weizhi[ 37 ].x1= 365 ,xinxi_weizhi[ 37 ].y1= 29 ;
    xinxi_weizhi[ 37 ].x2= 404 ,xinxi_weizhi[ 37 ].y2= 134 ;
    xinxi_weizhi[ 38 ].x1= 434 ,xinxi_weizhi[ 38 ].y1= 28 ;
    xinxi_weizhi[ 38 ].x2= 473 ,xinxi_weizhi[ 38 ].y2= 50 ;
    xinxi_weizhi[ 39 ].x1= 446 ,xinxi_weizhi[ 39 ].y1= 79 ;
    xinxi_weizhi[ 39 ].x2= 466 ,xinxi_weizhi[ 39 ].y2= 92 ;
    xinxi_weizhi[ 40 ].x1= 430 ,xinxi_weizhi[ 40 ].y1= 99 ;
    xinxi_weizhi[ 40 ].x2= 451 ,xinxi_weizhi[ 40 ].y2= 113 ;
    xinxi_weizhi[ 41 ].x1= 412 ,xinxi_weizhi[ 41 ].y1= 118 ;
    xinxi_weizhi[ 41 ].x2= 432 ,xinxi_weizhi[ 41 ].y2= 129 ;
    xinxi_weizhi[ 42 ].x1= 6 ,xinxi_weizhi[ 42 ].y1= 158 ;
    xinxi_weizhi[ 42 ].x2= 53 ,xinxi_weizhi[ 42 ].y2= 177 ;
    xinxi_weizhi[ 43 ].x1= 16 ,xinxi_weizhi[ 43 ].y1= 225 ;
    xinxi_weizhi[ 43 ].x2= 47 ,xinxi_weizhi[ 43 ].y2= 274 ;
    xinxi_weizhi[ 44 ].x1= 56 ,xinxi_weizhi[ 44 ].y1= 360 ;
    xinxi_weizhi[ 44 ].x2= 105 ,xinxi_weizhi[ 44 ].y2= 377 ;
    xinxi_weizhi[ 45 ].x1= 52 ,xinxi_weizhi[ 45 ].y1= 380 ;
    xinxi_weizhi[ 45 ].x2= 104 ,xinxi_weizhi[ 45 ].y2= 397 ;
    xinxi_weizhi[ 46 ].x1= 139 ,xinxi_weizhi[ 46 ].y1= 360 ;
    xinxi_weizhi[ 46 ].x2= 272 ,xinxi_weizhi[ 46 ].y2= 392 ;
    xinxi_weizhi[ 47 ].x1= 44 ,xinxi_weizhi[ 47 ].y1= 410 ;
    xinxi_weizhi[ 47 ].x2= 90 ,xinxi_weizhi[ 47 ].y2= 443 ;
    xinxi_weizhi[ 48 ].x1= 95 ,xinxi_weizhi[ 48 ].y1= 411 ;
    xinxi_weizhi[ 48 ].x2= 143 ,xinxi_weizhi[ 48 ].y2= 443 ;
    xinxi_weizhi[ 49 ].x1= 150 ,xinxi_weizhi[ 49 ].y1= 411 ;
    xinxi_weizhi[ 49 ].x2= 197 ,xinxi_weizhi[ 49 ].y2= 444 ;
    xinxi_weizhi[ 50 ].x1= 205 ,xinxi_weizhi[ 50 ].y1= 412 ;
    xinxi_weizhi[ 50 ].x2= 249 ,xinxi_weizhi[ 50 ].y2= 443 ;
    xinxi_weizhi[ 51 ].x1= 264 ,xinxi_weizhi[ 51 ].y1= 412 ;
    xinxi_weizhi[ 51 ].x2= 334 ,xinxi_weizhi[ 51 ].y2= 440 ;
    xinxi_weizhi[ 52 ].x1= 161 ,xinxi_weizhi[ 52 ].y1= 200 ;
    xinxi_weizhi[ 52 ].x2= 197 ,xinxi_weizhi[ 52 ].y2= 253 ;
    xinxi_weizhi[ 53 ].x1= 155 ,xinxi_weizhi[ 53 ].y1= 258 ;
    xinxi_weizhi[ 53 ].x2= 192 ,xinxi_weizhi[ 53 ].y2= 287 ;
    xinxi_weizhi[ 54 ].x1= 339 ,xinxi_weizhi[ 54 ].y1= 204 ;
    xinxi_weizhi[ 54 ].x2= 370 ,xinxi_weizhi[ 54 ].y2= 240 ;
    xinxi_weizhi[ 55 ].x1= 402 ,xinxi_weizhi[ 55 ].y1= 302 ;
    xinxi_weizhi[ 55 ].x2= 462 ,xinxi_weizhi[ 55 ].y2= 354 ;
    xinxi_weizhi[ 56 ].x1= 400 ,xinxi_weizhi[ 56 ].y1= 386 ;
    xinxi_weizhi[ 56 ].x2= 462 ,xinxi_weizhi[ 56 ].y2= 439 ;
    xinxi_weizhi[ 57 ].x1= 489 ,xinxi_weizhi[ 57 ].y1= 427 ;
    xinxi_weizhi[ 57 ].x2= 542 ,xinxi_weizhi[ 57 ].y2= 451 ;
    xinxi_weizhi[ 58 ].x1= 492 ,xinxi_weizhi[ 58 ].y1= 339 ;
    xinxi_weizhi[ 58 ].x2= 537 ,xinxi_weizhi[ 58 ].y2= 372 ;
    xinxi_weizhi[ 59 ].x1= 562 ,xinxi_weizhi[ 59 ].y1= 413 ;
    xinxi_weizhi[ 59 ].x2= 620 ,xinxi_weizhi[ 59 ].y2= 424 ;
    xinxi_weizhi[ 60 ].x1= 560 ,xinxi_weizhi[ 60 ].y1= 430 ;
    xinxi_weizhi[ 60 ].x2= 620 ,xinxi_weizhi[ 60 ].y2= 453 ;
    xinxi_weizhi[ 61 ].x1= 621 ,xinxi_weizhi[ 61 ].y1= 224 ;
    xinxi_weizhi[ 61 ].x2= 755 ,xinxi_weizhi[ 61 ].y2= 301 ;
    xinxi_weizhi[ 62 ].x1= 260 ,xinxi_weizhi[ 62 ].y1= 155 ;
    xinxi_weizhi[ 62 ].x2= 286 ,xinxi_weizhi[ 62 ].y2= 179 ;
    xinxi_weizhi[ 63 ].x1= 352 ,xinxi_weizhi[ 63 ].y1= 375 ;
    xinxi_weizhi[ 63 ].x2= 379 ,xinxi_weizhi[ 63 ].y2= 400 ;

    for(int i=0;i<XinxiNumber;i++)
        xinxi_weizhi[i].y1-=11,xinxi_weizhi[i].y2-=11;
}

void MainWindow::sleep(unsigned int msec){
    QTime reachTime =QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

void MainWindow::xinxitooltip(){
    xinxi[0]->setToolTip("楼体名称	玉兰苑餐厅\n"
                         "建筑年代	2003\n"
                         "建筑面积	18790.7m²	\n"
                         "建筑层数	4\n"
                         "简  介\n"
                         "玉兰苑餐厅共四层，一层西北角为凤凰快餐店。\n"
                         "一楼：大众厅，提供大众化的菜肴与面点食品，\n"
                         "近200多种南北风味的菜肴和点心供大家选择，提供免费咸菜和免费汤。\n"
                         "二楼：特色厅，分为：东北风味、千里香馄饨、\n"
                         "热干面、北方风味、重庆风味。\n"
                         "三楼：温馨厅，菜品类：正宗川味、兰州牛肉拉面等。\n"
                         "饮品类：奶茶、果脯、刨冰及可口可乐等饮品;\n"
                         "四楼：风味特色小炒，晚上开放到22:00。\n"
                         "玉兰苑东门特设包子组，全天提供各式包子。三楼特设教职工餐厅。\n"
                         "就餐时间：早上6:30--8:30，\n"
                         "中午10:40--12:30，晚上16:30--18:30。");
    xinxi[1]->setToolTip("楼体名称	学生公寓1号楼	\n"
                         "建筑年代	2002\n"
                         "建筑面积	7667m²\n"
                         "建筑层数	7\n"
                         "简  介	\n"
                         "为青年教师公寓，2人间，独立卫生间，独立浴室。\n"
                         "北侧为大学生活动中心和玉兰苑餐厅，东侧为图书馆。");
    xinxi[2]->setToolTip("楼体名称	学生公寓2号楼\n"
                         "建筑年代	2002\n"
                         "建筑面积	7667m²\n"
                         "建筑层数	7\n"
                         "简  介\n"
                         "为本科生公寓，标准6人间，公用楼层卫生间。\n"
                         "晚上23:00熄灯，节假日推迟到1:00熄灯。\n"
                         "丹田物业办公室在南侧。");
    xinxi[3]->setToolTip("楼体名称	学生公寓3号楼	\n"
                         "建筑年代	2002\n"
                        "建筑面积	7667m²	\n"
                         "建筑层数	7\n"
                        "简  介\n"
                        "为本科生公寓，标准6人间，独立卫生间。\n"
                        "晚上23:00熄灯，节假日推迟到1:00熄灯。\n"
                        "北侧有校园网络维修中心、思创图书杂志社等，\n"
                        "中国农业银行ATM、中国银行ATM、中国邮政收发室就在该楼南侧。");
    xinxi[4]->setToolTip("楼体名称	学生公寓4号楼	\n"
                         "建筑年代	2002\n"
                         "建筑面积	5673m²\n"
                         "建筑层数	6\n"
                         "简  介\n"
                         "为本科生公寓，两室一厅格局，每个卧室标准6人间，共用一个厅和卫生间。\n"
                         "晚上23:00熄灯，节假日推迟到1:00熄灯。\n"
                         "北侧为玉兰苑餐厅、校园卡综合业务中心、大学生活动中心等，\n"
                         "东侧有教材图书供应中心、水电费缴费中心、壹度源地。");
     xinxi[5]->setToolTip("楼体名称	学生公寓5号楼	\n"
                          "建筑年代	2002\n"
                          "建筑面积	5673m²\n"
                          "建筑层数	6\n"
                          "简  介\n"
                          "为本科生公寓，两室一厅格局，每个卧室标准6人间，共用一个厅和卫生间。\n"
                          "晚上23:00熄灯，节假日推迟到1:00熄灯。\n"
                          "北侧为玉兰苑餐厅、校园卡综合业务中心、大学生活动中心等，\n"
                          "东侧有教材图书供应中心、水电费缴费中心、壹度源地。");
      xinxi[6]->setToolTip("楼体名称	学生公寓6号楼	\n"
                           "建筑年代	2002\n"
                           "建筑面积	5673m²	\n"
                           "建筑层数	6\n"
                           "简  介\n"
                           "为本科生公寓，两室一厅格局，每个卧室标准6人间，共用一个厅和卫生间。\n"
                           "晚上23:00熄灯，节假日推迟到1:00熄灯。西侧为荟萃苑餐厅。");
       xinxi[7]->setToolTip("楼体名称	学生公寓7号楼	\n"
                            "建筑年代	2002\n"
                            "建筑面积	5673m²	\n"
                            "建筑层数	6\n"
                            "简  介\n"
                            "为本科生公寓，两室一厅格局，每个卧室标准6人间，共用一个厅和卫生间。\n"
                            "晚上23:00熄灯，节假日推迟到1:00熄灯。西侧为荟萃苑餐厅。");
        xinxi[8]->setToolTip("楼体名称	学生公寓8号楼	\n"
                             "建筑年代	2002\n"
                             "建筑面积	5673m²	\n"
                             "建筑层数	6\n"
                             "简  介\n"
                             "为留学生公寓，两室一厅格局，每个卧室标准6人间，共用一个厅和卫生间。\n"
                             "晚上23:00熄灯，节假日推迟到1:00熄灯。西侧为荟萃苑餐厅。");
         xinxi[9]->setToolTip("楼体名称	学生公寓9号楼	\n"
                              "建筑年代	2002\n"
                              "建筑面积	5673m²	\n"
                              "建筑层数	6\n"
                              "简  介\n"
                              "为留学生公寓，两室一厅格局，每个卧室标准6人间，共用一个厅和卫生间。\n"
                              "晚上23:00熄灯，节假日推迟到1:00熄灯。\n"
                              "西侧为荟萃苑餐厅，南侧有中国农业银行ATM、中国银行ATM、中国邮政收发室等。");
          xinxi[10]->setToolTip("楼体名称	学生公寓10号楼	\n"
                                "建筑年代	2006\n"
                                "建筑面积	13003m²	\n"
                                "建筑层数	7\n"
                                "简  介\n"
                                "为本科生公寓，标准6人间，公用楼层卫生间。\n"
                                "晚上23:00熄灯，节假日推迟到1:00熄灯。\n"
                                "东侧为玉兰苑餐厅，南侧有7点面包房，西侧紧挨校医院，北侧靠近体育馆及体育场。");
           xinxi[11]->setToolTip("楼体名称	学生公寓11号楼	\n"
                                 "建筑年代	2004\n"
                                 "建筑面积	13003m²	\n"
                                 "建筑层数	7\n"
                                 "简  介\n"
                                 "为本科生公寓，标准6人间，公用楼层卫生间。\n"
                                 "晚上23:00熄灯，节假日推迟到1:00熄灯。\n"
                                 "东侧为玉兰苑餐厅，南侧有天乐和超市、综合维修部等，西侧为校医院。");
           xinxi[12]->setToolTip("楼体名称	学生公寓12号楼	\n"
                                 "建筑年代	2006\n"
                                 "建筑面积	13003m²	建筑层数	7\n"
                                 "简  介\n"
                                 "为本科生公寓，标准6人间，公用楼层卫生间。\n"
                                 "晚上23:00熄灯，节假日推迟到1:00熄灯。\n"
                                 "东侧离玉兰苑餐厅和荟萃苑餐厅都较近，南侧有天乐和超市、沙宣理发店、金华眼镜店等。");
            xinxi[13]->setToolTip("楼体名称	学生公寓13号楼	\n"
                                  "建筑年代	2006\n"
                                  "建筑面积	13003m²	\n"
                                  "建筑层数	7\n"
                                  "简  介\n"
                                  "为本科生公寓，标准6人间，公用楼层卫生间。\n"
                                  "晚上23:00熄灯，节假日推迟到1:00熄灯。\n"
                                  "东侧为荟萃苑餐厅，南侧有伊尚房洗衣店、\n"
                                  "山东省邮政速递物流有限公司石油大学营业厅。");
             xinxi[14]->setToolTip("楼体名称	学生公寓14号楼\n"
                                   "建筑年代	2006\n"
                                   "建筑面积	13003m²	\n"
                                   "建筑层数	7\n"
                                   "简  介\n"
                                   "为本科生公寓，标准6人间，公用楼层卫生间。\n"
                                   "晚上23:00熄灯，节假日推迟到1:00熄灯。\n"
                                   "北侧有天乐和超市、沙宣理发店、金华眼镜店等，\n"
                                   "南侧有顺丰速递、鲜阳光超市等，东侧离荟萃苑餐厅较近。");
              xinxi[15]->setToolTip("楼体名称	学生公寓15号楼\n"
                                    "建筑年代	2006\n"
                                    "建筑面积	13003m²	\n"
                                    "建筑层数	7\n"
                                    "简  介\n"
                                    "为本科生公寓，标准6人间，公用楼层卫生间。\n"
                                    "晚上23:00熄灯，节假日推迟到1:00熄灯。\n"
                                    "北侧有侧有伊尚房洗衣店、山东省邮政速递物流有\n"
                                    "限公司石油大学营业厅，东侧离荟萃餐厅较近。\n");
               xinxi[16]->setToolTip("楼体名称	学生公寓16号楼	\n"
                                     "建筑年代	2007\n"
                                     "建筑面积	13030m²	\n"
                                     "建筑层数	7\n"
                                     "简  介\n"
                                     "为本科生公寓，标准6人间，公用楼层卫生间。\n"
                                     "晚上23:00熄灯，节假日推迟到1:00熄灯。\n"
                                     "北侧有顺丰速递、鲜阳光超市等，南侧有博帆超市、\n"
                                     "华鹰电脑服务部等，东侧离荟萃苑餐厅较近。");
                xinxi[17]->setToolTip("楼体名称	学生公寓17号楼\n"
                                      "建筑年代	2007\n"
                                      "建筑面积	13030m²\n"
                                      "建筑层数	7\n"
                                      "简  介\n"
                                      "为本科生公寓，标准6人间，公用楼层卫生间。\n"
                                      "晚上23:00熄灯，节假日推迟到1:00熄灯。\n"
                                      "东侧离荟萃苑餐厅较近。");
                xinxi[18]->setToolTip("楼体名称	学生公寓18号楼	\n"
                                      "建筑年代	2010\n"
                                      "建筑面积	17264.5m²	\n"
                                      "建筑层数	8\n"
                                      "简  介\n"
                                      "为本科生公寓，标准6人间，公用楼层卫生间。\n"
                                      "晚上23:00熄灯，节假日推迟到1:00熄灯。\n"
                                      "丹田物业办公室在北侧，离荟萃苑餐厅较近。");
                 xinxi[19]->setToolTip("楼体名称	学生公寓19号楼\n"
                                       "建筑年代	2010\n"
                                       "建筑面积	17264.5m²\n"
                                       "建筑层数	8\n"
                                       "简  介\n"
                                       "为本科生公寓，标准6人间，公用楼层卫生间。\n"
                                       "晚上23:00熄灯，节假日推迟到1:00熄灯。\n"
                                       "北侧为中国银行ATM、中国农业银行ATM以及中国邮政收发室。");
                 xinxi[20]->setToolTip("楼体名称	研究生公寓1号\n"
                                    "建筑年代	2009\n"
                                    "建筑面积	20389.1m²\n"
                                    "建筑层数	7\n"
                                    "简  介\n"
                                    "为硕士研究生公寓，四人间，独立卫生间，独立浴室。\n"
                                    "晚上0:00熄灯，节假日推迟到1:00熄灯。");
                 xinxi[21]->setToolTip("楼体名称	研究生公寓2号\n"
                                    "建筑年代	2009\n"
                                    "建筑面积	18681.2m²\n"
                                    "建筑层数	7\n"
                                    "简  介\n"
                                    "为硕士研究生公寓，四人间，独立卫生间，独立浴室。\n"
                                    "晚上0:00熄灯，节假日推迟到1:00熄灯。");
                 xinxi[22]->setToolTip("楼体名称	研究生公寓3号\n"
                                    "建筑年代	2010\n"
                                    "建筑面积	28089.3m²\n"
                                    "建筑层数	9\n"
                                    "简  介\n"
                                    "为硕士研究生公寓，四人间，独立卫生间，独立浴室。\n"
                                    "晚上0:00熄灯，节假日推迟到1:00熄灯。");
    xinxi[23]->setToolTip("楼体名称 体育馆\n"
                        "建筑年代	2007\n"
                        "建筑面积	19491m²\n"
                        "建筑层数	3\n"
                        "简  介\n"
                        "体育馆内设健身馆、羽毛球馆、健美操馆、乒乓球馆、\n"
                        "跆拳道馆、篮球馆等，内驻机构是体育教学部。");
    xinxi[24]->setToolTip("楼体名称	讲堂群(包含东西环、东西廊、南堂)	\n"
                          "建筑年代	2002\n"
                          "建筑面积	47300m²	\n"
                          "建筑层数	3\n"
                          "简  介\n"
                          "讲堂群分为东环、西环、东廊、西廊、南堂五部分，鸟瞰呈党徽标志。\n"
                          "南堂共5层，2、3、4层有外语语音室。多媒体值班室设在南堂2层。");
    xinxi[25]->setToolTip("楼体名称	讲堂群(包含东西环、东西廊、南堂)	\n"
                          "建筑年代	2002\n"
                          "建筑面积	47300m²	\n"
                          "建筑层数	3\n"
                          "简  介\n"
                          "讲堂群分为东环、西环、东廊、西廊、南堂五部分，鸟瞰呈党徽标志。\n"
                          "南堂共5层，2、3、4层有外语语音室。多媒体值班室设在南堂2层。");
    xinxi[26]->setToolTip("楼体名称	讲堂群(包含东西环、东西廊、南堂)	\n"
                          "建筑年代	2002\n"
                          "建筑面积	47300m²	\n"
                          "建筑层数	3\n"
                          "简  介\n"
                          "讲堂群分为东环、西环、东廊、西廊、南堂五部分，鸟瞰呈党徽标志。\n"
                          "南堂共5层，2、3、4层有外语语音室。多媒体值班室设在南堂2层。");
    xinxi[27]->setToolTip("楼体名称	国际交流及会议中心\n	"
                          "建筑年代	2002\n"
                          "建筑面积	29801m²\n"
                          "建筑层数	12\n"
                          "简  介\n"
                          "蓝海金港大饭店在此营业，可承办各种会议，安排住宿、就餐等，\n"
                          "拥有1个多功能厅及5个不同形式的中小型会议室，\n"
                          "可满足15至700人的各类会议、宴会活动及婚宴。");
    xinxi[28]->setToolTip("楼体名称	国际交流及会议中心\n	"
                          "建筑年代	2002\n"
                          "建筑面积	29801m²\n"
                          "建筑层数	12\n"
                          "简  介\n"
                          "蓝海金港大饭店在此营业，可承办各种会议，安排住宿、就餐等，\n"
                          "拥有1个多功能厅及5个不同形式的中小型会议室，\n"
                          "可满足15至700人的各类会议、宴会活动及婚宴。");
    xinxi[29]->setToolTip("楼体名称	图文信息与行政中心	\n"
                          "建筑年代	2003\n"
                          "建筑面积	53517m²	\n"
                          "建筑层数	17\n"
                          "简  介\n"
                          "该楼东侧部分是学校行政管理机构，学校的党政部门和直属机构主要在此办公；\n"
                          "西侧部分为图书馆，一楼是文艺书库，二楼是社科书库，三楼是科技书库，\n"
                          "四楼是保存本阅览室，五楼是工具书阅览室。");
    xinxi[30]->setToolTip("楼体名称	图文信息与行政中心	\n"
                          "建筑年代	2003\n"
                          "建筑面积	53517m²	\n"
                          "建筑层数	17\n"
                          "简  介\n"
                          "该楼东侧部分是学校行政管理机构，学校的党政部门和直属机构主要在此办公；\n"
                          "西侧部分为图书馆，一楼是文艺书库，二楼是社科书库，三楼是科技书库，\n"
                          "四楼是保存本阅览室，五楼是工具书阅览室。");
    xinxi[31]->setToolTip("楼体名称	多媒体中心	\n"
                          "建筑年代	2002\n"
                          "建筑面积	11493m²	\n"
                          "建筑层数	9\n"
                          "简  介\n"
                          "教学科研实验室和多媒体技术部，\n"
                          "多媒体教室向本科生开放上机。");
    xinxi[32]->setToolTip("楼体名称	基础实验楼\n"
                          "建筑年代	2002\n"
                          "建筑面积	9745m²	\n"
                          "建筑层数	9\n"
                          "简  介\n"
                          "该楼是计算机与通信工程学院和信息与控制工程学院的教学科研实验室。");
    xinxi[33]->setToolTip("排球场");
    xinxi[34]->setToolTip("篮球场");
    xinxi[35]->setToolTip("体育场才体育场看台是体育教学部和文学院办公使用。");
    xinxi[36]->setToolTip("第二运动场");
    xinxi[37]->setToolTip("篮球场");
    xinxi[38]->setToolTip("排球场");
    xinxi[39]->setToolTip("网球场");
    xinxi[40]->setToolTip("网球场");
    xinxi[41]->setToolTip("网球场");
    xinxi[42]->setToolTip("楼体名称	校医院	\n"
                          "建筑年代	2009\n"
                          "建筑面积	3769m²	\n"
                          "建筑层数	3\n"
                          "简  介\n"
                          "校内唯一的卫生医疗机构，设有急诊部，看病时需要一卡通挂号、买药。\n"
                          "上班时间：\n"
                          "上午：8:00--12:00；下午：14:00--17:30\n"
                          "（牙科仅周六、周日上班）。");
    xinxi[43]->setToolTip("沙滩排球场");
    xinxi[44]->setToolTip("篮球场");
    xinxi[45]->setToolTip("排球场");
    xinxi[46]->setToolTip("楼体名称	特种实验楼	\n"
                          "建筑年代	2015\n"
                           "简  介\n"
                          "该楼是储运与建筑工程学院、地球科学与技术学院、\n"
                          "非常规油气与新能源研究院、工程训练中心、化学工程学院、\n"
                          "机电工程学院、石油工程学院、信息与控制科学学院的教学科研实验室。");
    xinxi[47]->setToolTip("楼体名称	工科实验楼D座\n"
                          "建筑年代	2006\n"
                          "建筑面积	17882.36m²	\n"
                          "建筑层数	7\n"
                          "简  介\n"
                          "该楼是储运与建筑工程学院的行政办公室和教学科研实验室。");

    xinxi[48]->setToolTip("楼体名称	工科实验楼C座	\n"
                          "建筑年代	2006\n"
                          "建筑面积	17882.36m²	\n"
                          "建筑层数	7\n"
                          "简  介\n"
                          "该楼是地球科学与技术学院的行政办公室和教学科研实验室。");
    xinxi[49]->setToolTip("楼体名称	工科实验楼B座	\n"
                          "建筑年代	2006\n"
                          "建筑面积	17810.28m²	\n"
                          "建筑层数	7\n"
                          "简  介\n"
                          "该楼是石油工程学院的行政办公室和教学科研实验室。");
    xinxi[50]->setToolTip("楼体名称	工科实验楼A座	\n"
                          "建筑年代	2006\n"
                          "建筑面积	17810.28m²	\n"
                          "建筑层数	7\n"
                          "简  介\n"
                          "该楼是化学工程学院的行政办公楼和教学科研实验室。");
    xinxi[51]->setToolTip("楼体名称	逸夫实验楼\n"
                          "建筑年代	2005\n"
                          "建筑面积	18460m²\n"
                          "建筑层数	5\n"
                          "简  介\n"
                          "该楼是学校主要科研机构和会议中心的所在地，\n"
                          "科研机构包括化学工程学院科研实验室、\n"
                          "地球科学与技术学院科研实验室、\n"
                          "非常规油气与新能源研究院科研实验室及生物\n"
                          "工程中心科研实验室，逸夫会议中心主要举办各\n"
                          "种大型会议以及学术讲座。");
    xinxi[52]->setToolTip("荟萃广场");
    xinxi[53]->setToolTip("楼体名称	荟萃苑餐厅	\n"
                          "建筑年代	2005\n"
                          "建筑面积	15561m²\n"
                          "建筑层数	4\n"
                          "简  介\n"
                          "荟萃苑餐厅共三层：\n"
                          "一楼西侧为家常菜和各式主食，\n"
                          "开放时间：\n"
                          "早上6:00--8:30，中午10:40--13:00，晚上16:30--19:00\n"
                          "二楼设有食味轩，提供炒菜，服务到晚间23:00。\n"
                          "三楼设有自选菜和火锅。");
    xinxi[54]->setToolTip("子元广场");
    xinxi[55]->setToolTip("楼体名称	南教楼\n"
                          "建筑年代	2010\n"
                          "建筑面积	27600m²\n"
                          "建筑层数	5\n"
                          "简  介\n"
                          "全楼共5层，2层设有多媒体值班室，5层设有绘图室。\n"
                          "每层都有热水器，单层2台，双层1台。\n"
                          "每天晚上10:30物业打扫卫生。");
    xinxi[56]->setToolTip("楼体名称	文理综合楼	\n"
                          "建筑年代	2009\n"
                          "建筑面积	25433m²	\n"
                          "建筑层数	5\n"
                          "简  介\n"
                          "文理综合楼是经济管理学院、文学院、\n"
                          "理学院和马克思主义学院的行政及办公地点。");
    xinxi[57]->setToolTip("楼体名称 工科实验楼E座	\n"
                        "建筑年代	2013\n"
                        "建筑面积	53143m²	\n"
                        "建筑层数	21\n"
                        "简  介\n"
                        "该楼主要是石油工程学院、机电工程学院、化学工程学院、\n"
                        "储运与建筑工程学院、计算机与通信工程学院及信息与控制工程学院\n"
                        "的行政办公室和教学科研实验室。");
     xinxi[58]->setToolTip("楼体名称	唐岛湾餐厅	\n"
                           "建筑年代	2010\n"
                           "建筑面积	12252.3m²\n"
                           "建筑层数	3\n"
                           "简  介\n"
                           "唐岛湾餐厅共三层，一楼二楼是餐厅（二楼有一清真餐厅），\n"
                           "三楼是各个社团办公室及活动大厅。\n"
                           "就餐时间：早上6:30--8:30，\n"
                           "中午10:40--12:30，晚上16:30--18:30。");
      xinxi[59]->setToolTip("篮球场");
       xinxi[60]->setToolTip("楼体名称	留学生与培训生综合楼	\n"
                             "建筑年代	2013\n"
                             "建筑面积	46372m²	\n"
                             "建筑层数	15\n"
                             "简  介\n"
                             "该楼主要用于各种技术培训及留学生培养及科研。");
        xinxi[61]->setToolTip("小黄山");
         xinxi[62]->setToolTip("楼体名称	大学生活动中心\n"
                               "建筑年代	2003\n"
                               "建筑面积	5360m²\n"
                               "建筑层数	4\n"
                                "简  介\n"
                               "大学生活动中心是学生社团的主要所在地，\n"
                               "大学生资助事务大厅、学生教育信息工作站、\n"
                               "学生管理信息工作站也在此办公。");
          xinxi[63]->setToolTip("创造太阳");
}

