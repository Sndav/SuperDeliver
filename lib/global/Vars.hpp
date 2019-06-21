#ifndef _Vars
#define _Vars

#include "Header.hpp"

RiderList GlobalRiderList;
BillLog GlobalBillLog;
BillQueue GlobalBillQueue;
rLabelList GlobalRLabel;
//hlList HlList;

int GlobalMoney = 1000; // 当前多少钱
int GlobalTime = 0;  // 当前时间
int GlobalBillSum = 0;  // 接单数
int GlobalBillAccomplish = 0;  // 完成数
int GlobalBillovertime = 0;  // 超时单数
int mouseControl = 0;
int mouseBillID = 0;

int hltimes=-1;

int mx,my,ex,ey;

int speed=500;

queue<QLabel*> HTs;
#endif
