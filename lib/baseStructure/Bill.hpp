// 头文件声明
#include "../global/Header.hpp"

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
    thetime = nowtiem - R->start_time;
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
        获取队列里第一个未分配订单
    Parameters:
        id:bill_id
    Return:
        None
*/
Bill* bill_get_next_bill(){
    //TODO:获取起始订单id
    Bill* R = GlobalBillLog[id];
    if(R->status==0)//如果订单状态是0未分配就返回，否则id++判断下一个订单是否被分配
    return R;
    else id++;
}

/*
    Summary:
        返回为id的订单
    Parameters:
        id:bill_id
    Return:
       bill
*/
Bill* bill_get_bill(int id){
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
void bill_change_status(int id,int statu){
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
int bill_get_status(int id){
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
void assign(int bill_id,int rider_id){
    Bill* R = GlobalBillQueue[bill_id];//获取订单
    Rider* P = GlobalRiderList[rider_id];//获取rider

    P->bag.push(bill_id);
    P->cur_position.position_x = R->restaurant_x;
    P->cur_position.position_y = R->restaurant_y;
    P->cur_position.type = 0;
    P->cur_position.bill_id = bill_id;   
}


