#ifndef _Structure
#define _Structure
#include "../global/Header.hpp"
struct MapNode{
    int x,y,type; // type:代表此节点为路或者房子
};

struct Bill{
    int id;             // 订单id
    int start_time;     // 订单开始时间
    int end_time;
    int restaurant_x;   // 餐馆位置
    int restaurant_y;
    int target_x;       // 目的位置
    int target_y;
    int status;         // 订单状态 0未分配，1取货，2送货，3送达
    Bill(int id):
        id(id),
        end_time(0),
        status(0)
    {};
};


struct Position{
    int position_x;
    int position_y;
    int type; // 位置类型 0->餐馆 1->目的地 -1->未初始化
    int bill_id; // 当前去往位置的订单id
};

typedef vector<Position> RiderBag;

struct Rider{
    int id;             // 骑手id
    int position_x;     // 骑手当前位置
    int position_y;     
    Position cur_position; // 骑手当前订单
    RiderBag bag;     // 骑手背包数据
    int arrive_po_x;
    int arrive_po_y;
    int arrive_type;
    //QLabel* rLabel();
    Rider(int id):
        arrive_type(-1),
        arrive_po_x(-1),
        arrive_po_y(-1),
        id(id),
        position_x(1),
        position_y(0){
            cur_position.type = -1;
        }; // 构造函数,初始化Rider,位置设为(-1,-1);
    
};

typedef vector<Bill*> BillLog; // 存放所有订单
typedef queue<Bill*> BillQueue; //存放未分配订单队列
typedef vector<Rider*> RiderList; // 骑手列表
typedef vector<QLabel*> rLabelList; //骑手图标列表
typedef vector<QLabel*> hlList; //高亮图标列表

#endif
