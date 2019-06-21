#include "lib/global/Header.hpp"
#include <fstream>
int  main(){
    //initgraph(1024,768);
    //ege::getch();
    fstream _output;
    _output.open("output.txt",ios::out|ios::trunc);
    _output.close();
    GlobalBillLog.push_back(new Bill(-1));
    freopen("sales.txt","r",stdin); // 输入
    while(ReadLine()){};
    int i = 1;
    while(GlobalBillAccomplish != GlobalBillSum || i == 1){
        // sleep(2);
        if(GlobalMoney < 0){
            printf("DIEEEEEE");
            exit(0);
        }
        i=0;
        GlobalTime++;
        printf("============TIME:%d================\n",GlobalTime);
        while(GlobalMoney >= 400){
            Rider_buy_rider();
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
        PrintStatus();
    }
    //closegraph();
    
    return 0;
}