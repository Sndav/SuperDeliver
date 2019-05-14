// 头文件声明
#include "Structure.hpp"
#include "../global/Header.hpp"
#include "../global/Vars.hpp"

/*
    Summary:
        buy a rider,return the rider_id
    Parameters:
        None
    Return:
        int, id of the registed rider;
*/
int Rider_buy_rider(){
    int new_id = GlobalRiderList.size()+1; // 获取新id
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
    // TODO: 边界操作判断
    R->position_x += x;
    R->position_y += y;
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
    next_p.bill_id = curbill_id;
    next_p.position_x = curBill->restaurant_x;
    next_p.position_y = curBill->restaurant_y;
    R->bag.push(next_p); // 将订单目的地地址入队列

    R->cur_position = R->bag.top();R->bag.pop(); // 更新当前目的地址
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
    Rider* R = GlobalRiderList[id];             // 取得Rider
    Position R_position = R->cur_position;      // 取得当前目的位置信息
    int curbill_id = R_position.bill_id;        // 获取当前Billid
    Bill * curBill = GlobalBillLog[curbill_id]; // 获取当前Bill

    GlobalMoney += 10; // TODO: get_bill_oney(curbill_id) // 加钱
    curBill->status = 3; // TODO:chang_status(id,status)

    R->cur_position = R->bag.top();R->bag.pop(); // 更新当前目的地址

}

Rider * Rider_get_rider(int id){
    return GlobalRiderList[id];
}