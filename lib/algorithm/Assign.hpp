#include "../global/Header.hpp"

int getBestRider(Bill * bill){
    Position P;
    P.bill_id = bill->id;
    P.position_x = bill->restaurant_x;
    P.position_y = bill->restaurant_y;

    auto rider = GlobalRiderList.begin();
    auto Bag = (*rider)->bag;
    Bag.push_back(P);

    int min_cost = getPath(Bag,Bag);
    auto min_rider = rider;

    for(rider = GlobalRiderList.begin()+1; rider != GlobalRiderList.end();++rider){
        if((*rider)->cur_position.type == -1)
            return (*rider)->id;
        auto Bag = (*rider)->bag;
        Bag.push_back(P);
        int tmp_cost = getPath(Bag,Bag);
        if(tmp_cost < min_cost){
            min_rider = rider;
            min_cost = tmp_cost;
        }
    }
    return (*min_rider)->id;
}