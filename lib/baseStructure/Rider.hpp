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
int buy_rider(){
    int new_id = GlobalRiderList.size()+1;
    Rider* R = new Rider(new_id);
}