typedef struct MapNode{
    int x,y,type; // type:代表此节点为路或者房子
}MapNode;

typedef struct Bill{
    int id;             // 订单id
    int start_time;     // 订单开始时间
    int restaurant_x;   // 餐馆位置
    int restaurant_y;
    int target_x;       // 目的位置
    int target_y;
}Bill;
typedef struct ListBill{         // 订单链表 这里使用双链表，便于查询，实现起来应该是队列
    struct ListBill* pre_bill;  // 上一个订单
    struct Bill* cur_bill;      // 当前订单
    struct ListBill* next_bill; // 下一个订单
}ListBill;

typedef struct Rider{
    int id;             // 骑手id
    int position_x;     // 骑手当前位置
    int position_y;     
    struct Bill* current_bill; // 骑手当前订单
    struct ListBill* bag;       // 骑手背包数据
}Rider;

typedef struct ListRider{
	struct ListRider* pre_rider; // 前一个骑手
    struct Rider* cur_rider;      // 当前骑手
    struct ListRider* next_rider;// 下一个骑手
}ListRider;