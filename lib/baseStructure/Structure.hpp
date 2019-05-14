#include "../global/Header.hpp"
struct MapNode{
    int x,y,type; // type:代表此节点为路或者房子
};

struct Bill{
    int id;             // 订单id
    int start_time;     // 订单开始时间
    int restaurant_x;   // 餐馆位置
    int restaurant_y;
    int target_x;       // 目的位置
    int target_y;
};


struct Position{
    int position_x;
    int position_y;
    int type; // 位置类型 0->餐馆 1->目的地
    int bill_id; // 当前去往位置的订单id
};

typedef priority_queue<Position*> RiderBag;

struct Rider{
    int id;             // 骑手id
    int position_x;     // 骑手当前位置
    int position_y;     
    Bill* current_bill; // 骑手当前订单
    RiderBag bag;     // 骑手背包数据
};

typedef vector<Bill*> BillLog; // 存放所有订单
typedef queue<Bill*> BillQueue; //存放为分配订单队列
typedef vector<Rider*> RiderList; // 骑手列表

