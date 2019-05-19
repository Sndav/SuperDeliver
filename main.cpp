#include "lib/global/Header.hpp"
int main(){
    int T =100;
    freopen("data1/sales.txt","r",stdin); // 输入
    while(ReadLine()){};
    while(T--){
        GlobalTime++;
        printf("============TIME:%d================\n",GlobalTime);
        while(GlobalMoney >= 300){
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
            Rider_CheckPosition(*rider);
            Rider_MoveRider(*rider);
        }
        PrintStatus();
    }
    return 0;
}