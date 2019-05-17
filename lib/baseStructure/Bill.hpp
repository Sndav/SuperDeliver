// 头文件声明
#include "Structure.hpp"
#include "../global/Header.hpp"
#include "../global/Vars.hpp"

/*
    Summary:
        判断订单是否超时
    Parameters:
        id:bill_id
    Return:
        None
*/
void Bill_check_bill(int id){
    Bill* R = GlobalBillLog[id];
// TODO:获取现在的时间nowtime，并都转化为时间单位
    int nowtime,thetime;
    thetime = nowtime - R->start_time;
    if(thetime>30&&thetime<=60)//判断是否超时
    GlobalMoney-=50;
}

/*
    Summary:
        让订单加入队列
    Parameters:
        id:bill_id
    Return:
        None
*/
void Bill_read_bill(){
    int new_id = GlobalBillLog.size()+1;//获取新id
    Bill* R = new Bill(new_id);   // new Rider
    GlobalBillLog.push_back(R);   // 加入队列
}
/*
    Summary:
        获取未分配队列里第一个未分配订单
    Parameters:
        
    Return:
        None
*/
Bill* Bill_get_next_bill(){
    
    Bill* R = GlobalBillQueue.front();//获得未分配queue的第一个元素
    return R;
}

/*
    Summary:
        返回为id的订单
    Parameters:
        id:bill_id
    Return:
       bill
*/
Bill* Bill_get_bill(int id){
    Bill* R = GlobalBillLog[id];//将id为id的订单返回
    return R;
}

/*
    Summary:
        改变订单的状态
    Parameters:
        bill id
        statu
    Return:
    
*/
void Bill_change_status(int id,int statu){
    Bill* R = GlobalBillLog[id];
    R->status = statu;//将status改变
}

/*
    Summary:
        获取订单的状态
    Parameters:
        bill id
    Return:
      status
*/
int Bill_get_status(int id){
    Bill* R = GlobalBillLog[id];
    return R->status;
}
/*
    Summary:
        将bill加到rider的背包中
    Parameters:
        bill id
        rider id
    Return:
      void
*/
void Bill_assign(int bill_id,int rider_id){
    Bill* R = GlobalBillLog[bill_id];//获取订单
    Rider* P = GlobalRiderList[rider_id];//获取rider

    
    Position Q;
    Q.bill_id = bill_id;
    Q.position_x = R->restaurant_x;
    Q.position_y = R->restaurant_y;
    Q.type = 0;
    P->bag.push(Q);    
}



