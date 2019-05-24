#include "../global/Header.hpp"
void PrintStatus(){
	int i;
	printf("时间：%d\n",GlobalTime);
	printf("钱：%d\n",GlobalMoney); // + (int)GlobalRiderList.size()*300 - 1000
	printf("接单数：%d\n",GlobalBillSum);
	printf("完成数：%d; ",GlobalBillAccomplish);
	Bill_print_finished();
	printf("超时数：%d\n",GlobalBillovertime);
	Bill_print_violation_ticket();
	for(auto iter = GlobalRiderList.begin();iter!=GlobalRiderList.end();++iter){ 
		printf("骑手%d的位置：(%d,%d);停靠:",(*iter)->id,(*iter)->position_x,(*iter)->position_y);
	}

}