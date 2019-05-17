#ifndef _Vars
#define _Vars

#include "Header.hpp"

RiderList GlobalRiderList;
BillLog GlobalBillLog;
BillQueue GlobalBillQueue;

int GlobalMoney = 1000; // 当前多少钱
int GlobalTime = 0;  // 当前时间
int GlobalBillSum = 0;  // 接单数
int GlobalBillAccomplish = 0;  // 完成数
int GlobalBillovertime = 0;  // 接单数

#endif