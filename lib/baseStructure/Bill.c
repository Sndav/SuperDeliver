// 头文件声明
#include "Structure.c"

// 函数原型
ListBill* newListBill(Bill* bill); // 新建订单链表节点:bill(订单)
void listBillAppend(ListBill *list,Bill *bill); // 订单列表添加订单:list(订单列表),bill(订单);
void listBillRemove(ListBill *node); // 删除订单列表中的节点
Bill* newBill(int id,int start_time,int r_x,int r_y,int t_x,int t_y);
// 新订单:id(ID),start_time(订单开始时间),r_x(餐馆坐标x),r_y(餐馆坐标y),t_x(目的地坐标x),t_y(目的地坐标y)

