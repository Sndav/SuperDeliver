#include "../global/Header.hpp"

void ReadLine(){
    Bill* newBill = new Bill();
    scanf("%d %d %d %d %d %d",
        &newBill->id,           &newBill->start_time,
        &newBill->restaurant_x, &newBill->restaurant_y,
        &newBill->target_x,     &newBill->target_y
    );
    newBill->status = 0;
    GlobalBillQueue.push(newBill);
    GlobalBillLog.push_back(newBill);
    GlobalBillSum++; //增加订单
}

