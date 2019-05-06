// 头文件声明
#include "Structure.c"
#include <stdlib.h>
// 函数原型
Rider * newRider(int id,int x,int y); // 新建骑手:id(ID),x(x坐标),y(y坐标);骑手指针
ListRider* listRiderAppend(ListRider *list,Rider *rider); // 骑手链表加入骑手:list(骑手链表),rider(骑手);新链表
ListRider* newListRider(Rider *rider); // 新建骑手链表节点:rider(初始化骑手);节点的指针
void freeListRider(ListRider *list); // 释放链表:list(骑手链表)

//函数编写
Rider * newRider(int id,int x,int y){
    Rider* rider = (Rider*)malloc(sizeof(Rider*)); // 分配空间
    rider->id = id;  // 赋值 这里的ID应该是递增
    rider->position_x = x;
    rider->position_y = y;
    rider->current_bill = NULL;
    rider->bag = NULL;
    return rider;
}

ListRider* listRiderAppend(ListRider *list,Rider *rider){
    ListRider* node = newListRider(rider);
    node->next_rider = list; // 双链表
    node->pre_rider = list->pre_rider;
    list->pre_rider->next_rider = node;
    list->pre_rider = node;
    return node;
}

ListRider* newListRider(Rider *rider){
    ListRider *list = (ListRider *)malloc(sizeof(ListRider*)); // 分配空间
    list->cur_rider = rider;
    list->pre_rider = list->next_rider = list; // 指向自己
    return list;
}

void freeListRider(ListRider *list){
    while(list != NULL){
        ListRider* pre = list;             // 备份当前节点便于free
        pre->pre_rider->next_rider = NULL; // 删除链接
        list = list->next_rider;           // 指向下一个节点
        free(pre);                         // 释放空间
    }
}