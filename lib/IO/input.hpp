#include "../global/Header.hpp"

bool ReadLine(){
    Bill* newBill = new Bill(0);
    int in = scanf("%d %d %d %d %d %d\n",
        &newBill->id,           &newBill->start_time,
        &newBill->restaurant_x, &newBill->restaurant_y,
        &newBill->target_x,     &newBill->target_y
    );
    if(in == EOF) return false;
    newBill->status = 0;
    GlobalBillQueue.push(newBill);
    GlobalBillLog.push_back(newBill);
    return true;
}

