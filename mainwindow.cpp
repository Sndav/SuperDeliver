#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lib/global/Header.hpp"
#include "windows.h"
#include <QTime>
#include <QElapsedTimer>

static int run=0,pausestop=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon(":/imgsrc/deli.ico"));

    // 设置窗体标题
    //setWindowTitle(tr("Delivery"));
    ui->setupUi(this);
    ui->timeText->setText("0");
    ui->BillC->setText("0");
    ui->FondB->setText("1000");
    ui->OverTimeB->setText("0");
    ui->CompleteB->setText("0");
    fstream _file;
    _file.open("sales.txt", ios::in);
    fstream _output;
    _output.open("output.txt",ios::out|ios::trunc);
    _output.close();
    if(_file){
        ui->mouseclabel->setText(" ");
    }
    else{mouseControl=1;}

}

void round();

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    pausestop=0;
    QElapsedTimer t;
    t.start();
    while(pausestop==0)
    {
        QCoreApplication::processEvents();
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(run==0){
        run=1;
        GlobalBillLog.push_back(new Bill(-1));

            if(mouseControl==0){
                freopen("sales.txt","r",stdin); // 输入
                while(ReadLine()){};
            }
            int i = 1;
            while(GlobalBillAccomplish != GlobalBillSum || i == 1){
                // sleep(2);
                if(GlobalMoney < 0){
                    printf("DIEEEEEE");
                    exit(0);
                }
                if(!mouseControl)i=0;
                GlobalTime++;

                printf("============TIME:%d================\n",GlobalTime);
                round();

                //PrintStatus();

                FILE *fout;

                fout=fopen("output.txt","a");
                int i;
                printf("时间：%d\n",GlobalTime);
                fprintf(fout,"时间：%d\n",GlobalTime);
                printf("钱：%d\n",GlobalMoney); // + (int)GlobalRiderList.size()*300 - 1000
                fprintf(fout,"钱：%d\n",GlobalMoney);
                printf("接单数：%d\n",GlobalBillSum);
                fprintf(fout,"接单数：%d\n",GlobalBillSum);
                printf("完成数：%d; ",GlobalBillAccomplish);
                fprintf(fout,"完成数：%d; ",GlobalBillAccomplish);
                Bill_print_finished();
                printf("超时数：%d ",GlobalBillovertime);
                fprintf(fout,"超时数：%d ",GlobalBillovertime);
                Bill_print_violation_ticket();
                for(auto iter = GlobalRiderList.begin();iter!=GlobalRiderList.end();++iter){
                    printf("骑手%d的位置：(%d,%d);停靠:",(*iter)->id,(*iter)->position_x,(*iter)->position_y);
                    fprintf(fout,"骑手%d的位置：(%d,%d);停靠:",(*iter)->id,(*iter)->position_x,(*iter)->position_y);
                    //QPixmap HLP;

                    if((*iter)->arrive_po_x != -1 && (*iter)->arrive_po_y != -1){
                        QLabel* HL = new QLabel(ui->TableW);
                        hltimes++;
                        if((*iter)->arrive_type == 0){
                            printf("食客");
                            fprintf(fout,"食客");
                            //HLP.load(":/imgsrc/A.png");
                            //HL->setPixmap(HLP);
                            HL->setStyleSheet(QString("border-image:url(:/imgsrc/B.png);"));
                            HL->setText(QString::number((*iter)->cur_position.bill_id));
                            HL->setScaledContents(true);
                            HL->resize(40,40);
                        }
                        if((*iter)->arrive_type == 1){
                            printf("餐馆");
                            fprintf(fout,"餐馆");
                            //HLP.load(":/imgsrc/B.png");
                            //HL->setPixmap(HLP);
                            HL->setStyleSheet(QString("border-image:url(:/imgsrc/A.png);"));
                            HL->setText(QString::number((*iter)->cur_position.bill_id));
                            HL->setScaledContents(true);
                            HL->resize(40,40);
                        }
                        printf("(%d,%d)",(*iter)->arrive_po_x,(*iter)->arrive_po_y);
                        fprintf(fout,"(%d,%d)",(*iter)->arrive_po_x,(*iter)->arrive_po_y);
                        HL->setGeometry((*iter)->arrive_po_x*40,(*iter)->arrive_po_y*40,40,40);
                        HL->show();
                        //HlList[hltimes]=HL;
                        //HL->clear();
                        (*iter)->arrive_po_x = (*iter)->arrive_po_y = -1;
                    }
                    printf("\n");
                    fprintf(fout,"\n");

                }
                fclose(fout);

                freshUI();
                /*if(hltimes>=0) for(int j=hltimes;j<0;j--)
                {
                    QLabel *hlt;
                    hlt=HlList[j];
                    hlt->clear();
                }*/
            }
        }
    else {
        pausestop=1;
    }
}

void MainWindow::freshUI()
{
    ui->timeText->setText(QString::number(GlobalTime));
    ui->BillC->setText(QString::number(GlobalBillSum-GlobalBillAccomplish));
    ui->FondB->setText(QString::number(GlobalMoney));
    ui->OverTimeB->setText(QString::number(GlobalBillovertime));
    ui->CompleteB->setText(QString::number(GlobalBillAccomplish));
    QWidget::update();
    QElapsedTimer t;
    t.start();
    while(t.elapsed()<speed)
        QCoreApplication::processEvents();
}

void MainWindow::round()
{
    int riderbought = 0;
    while(GlobalMoney >= 400){
        Rider_buy_rider();
        riderbought++;
        //QPixmap riderp;
        //riderp.load(":/imgsrc/rider.png");
        QLabel* rLabel = new QLabel(ui->TableW);
        //rLabel->setPixmap(riderp);
        rLabel->setStyleSheet(QString("border-image:url(:/imgsrc/rider.png);"));
        rLabel->setText(QString::number(riderbought));
        rLabel->setScaledContents(true);
        rLabel->resize(40,40);
        rLabel->setGeometry(-40,-40,40,40);
        GlobalRLabel.push_back(rLabel);
        rLabel->show();
        GlobalMoney -= 300;
    }
    auto CurBill = GlobalBillQueue.front();
    while(!GlobalBillQueue.empty() && CurBill->start_time <= GlobalTime){
        GlobalBillQueue.pop();
        // 分配订单
        int best_id = getBestRider(CurBill);
        Bill_assign(CurBill->id,best_id);
        // 订单操作
        if(GlobalBillQueue.empty())break;
        CurBill = GlobalBillQueue.front();
    }
    for(auto rider = GlobalRiderList.begin(); rider != GlobalRiderList.end();++rider){
        Rider_MoveRider(*rider);
        Rider_CheckPosition(*rider);
    }
};

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //int mx,my,ex,ey;
    if(event->button() == Qt::LeftButton)
        {
            mx=event->x();
            my=event->y();
            //printf("%d,%d/n",mx,my);
            /*HL->setStyleSheet(QString("border-image:url(:/imgsrc/A.png);"));
            HL->setText(QString::number((*iter)->cur_position.bill_id));
            HL->setScaledContents(true);
            HL->resize(40,40);*/

        }
};

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    ex=event->x();
    ey=event->y();
    if(mx>19&&mx<701&&my>59&&my<741&&mouseControl&&ex>19&&ex<701&&ey>59&&ey<741)
    {
        Bill* newBill = new Bill(0);
        /*int in = scanf("%d %d %d %d %d %d\n",
            &newBill->id,           &newBill->start_time,
            &newBill->restaurant_x, &newBill->restaurant_y,
            &newBill->target_x,     &newBill->target_y
        );*/
        mouseBillID++;
        newBill->id = mouseBillID;
        newBill->status = 0;
        newBill->start_time = GlobalTime;
        newBill->restaurant_x=(mx-20)/40;
        newBill->restaurant_y=(my-60)/40;
        newBill->target_x=(ex-20)/40;
        newBill->target_y=(ey-60)/40;
        GlobalBillSum++;
        GlobalBillQueue.push(newBill);
        GlobalBillLog.push_back(newBill);
        //freshUI();
        ui->NewBill->setText(QString::number(mouseBillID));
        ui->ax->setText(QString::number((mx-20)/40));
        ui->ax->repaint();
        ui->ay->setText(QString::number((my-60)/40));
        ui->ay->repaint();
        ui->bx->setText(QString::number((ex-20)/40));
        ui->bx->repaint();
        ui->by->setText(QString::number((ey-60)/40));
        ui->by->repaint();
    }

};


void MainWindow::on_pushButton_3_clicked()
{
    mouseControl=0;
    qApp->exit(0);
}

void MainWindow::on_radioButton_4_toggled(bool checked)
{
    speed=50;
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    speed=150;
}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    speed=500;
}

void MainWindow::on_radioButton_3_toggled(bool checked)
{
    speed=2000;
}
