// 头文件声明
#include "../global/Header.hpp"
/*
    Summary:
        buy a rider,return the rider_id
    Parameters:
        None
    Return:
        int, id of the registed rider;
*/
int Rider_buy_rider(){

    int new_id = GlobalRiderList.size(); // 获取新id
    Rider* R = new Rider(new_id);   // new Rider


    GlobalRiderList.push_back(R);   // 加入队列

    return new_id;   // 返回
}

/*
    Summary:
        move a rider
    Parameters:
        id:rider_id
        x: 向右平移的多少,负数为向左
        y: 向上平移多少,负数为向下
    Return:
        None
*/
void Rider_move_rider(int id,int x,int y){
    Rider* R = GlobalRiderList[id];
    if(R->cur_position.type == -1) return;
    // TODO: 边界操作判断
    R->position_x += x;
    R->position_y += y;
    GlobalRLabel[id]->setGeometry(R->position_x*40,R->position_y*40,40,40);
}

/*
    Summary:
        骑手到达餐馆，接收外卖
    Parameters:
        id:rider_id
    Return:
        None
*/
void Rider_pick_up_bill(int id){
    Rider* R = GlobalRiderList[id];             // 取得Rider
    Position R_position = R->cur_position;      // 取得当前目的位置信息
    int curbill_id = R_position.bill_id;        // 获取当前Billid
    Bill * curBill = GlobalBillLog[curbill_id]; // 获取当前Bill

    curBill->status = 2; // TODO: 此处应该调用bill的change_status

    Position next_p;
    next_p.type = 1;
    next_p.bill_id = curbill_id;
    next_p.position_x = curBill->target_x;
    next_p.position_y = curBill->target_y;
    R->bag.push_back(next_p); // 将订单目的地地址入队列

    R->cur_position = *R->bag.begin();
    R->bag.erase(R->bag.begin()); // 更新当前目的地址

    GlobalRLabel[id]->setGeometry(R->position_x*40,R->position_y*40,40,40);
}

/*
    Summary:
        送货结束处理
    Parameters:
        id:rider_id
    Return:
        None
*/

void Rider_deliver_ok(int id){
    GlobalBillAccomplish++;
    Rider* &R = GlobalRiderList[id];             // 取得Rider
    Position R_position = R->cur_position;      // 取得当前目的位置信息
    int curbill_id = R_position.bill_id;        // 获取当前Bill_id
    Bill * curBill = GlobalBillLog[curbill_id]; // 获取当前Bill
    Bill_check_bill(curbill_id);
    GlobalMoney += 10; // 加钱
    curBill->status = 3; // TODO:chang_status(id,status)
    curBill->end_time = GlobalTime;//方便我判断

    if(!R->bag.empty()){ // 空
        R->cur_position = *R->bag.begin();
        R->bag.erase(R->bag.begin()); // 更新当前目的地址
        adjustRider(R);
    }else{
        R->cur_position.position_x = 0;
        R->cur_position.position_y = 0;
        R->cur_position.type = -1;
    }
}

void Rider_MoveRider(Rider * rider){
    if(rider->cur_position.type == -1) return;
    int rx=0,ry=0;
    Alg_Path_getNextMove(rider->position_x,rider->position_y,rider->cur_position,rx,ry);
    Rider_move_rider(rider->id,rx,ry);
    GlobalRLabel[rider->id]->setGeometry(rider->position_x*40,rider->position_y*40,40,40);
}

Rider * Rider_get_rider(int id){
    return GlobalRiderList[id];
}

bool isNearPosition(int x,int y,int x2,int y2){ // 是否在旁边？
    if((abs(x-x2) <= 2 && abs(y-y2)<= 1) || (abs(x-y2)<=1 && abs(y-y2) <= 2))return true;
    return false;
} 

void Rider_CheckPosition(Rider *rider){
    GlobalRLabel[rider->id]->setGeometry(rider->position_x*40,rider->position_y*40,40,40);
    if( isNearPosition( rider->cur_position.position_x,
                        rider->cur_position.position_y,
                        rider->position_x,
                        rider->position_y)){
        auto curP = rider->cur_position;
        if(curP.type == 1){ // 目的地
            // printf("========Arrive========\n");
            rider->arrive_po_x = rider->cur_position.position_x;
            rider->arrive_po_y = rider->cur_position.position_y;
            rider->arrive_type = 0;
            Rider_deliver_ok(rider->id);
        }else if(curP.type == -1){
            return;
        }else if(curP.type == 0){ // 餐馆
            rider->arrive_type = 1;
            rider->arrive_po_x = rider->cur_position.position_x;
            rider->arrive_po_y = rider->cur_position.position_y;
            // printf("========PickUP========\n");
            Rider_pick_up_bill(rider->id);
        }
    } // 到达当前目的地
}

bool check_finish(){
    for(auto rider = GlobalRiderList.begin(); rider != GlobalRiderList.end();++rider){
        if((*rider)->cur_position.type != -1)
        return false;
    }
    return true;
}

