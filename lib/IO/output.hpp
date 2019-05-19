#include "../global/Header.hpp"
void PrintStatus(){
	int i;
	printf("当前钱数：%d\n",GlobalMoney); // + (int)GlobalRiderList.size()*300 - 1000
	for(auto iter = GlobalRiderList.begin();iter!=GlobalRiderList.end();++iter){ 
		printf("骑手%d的位置：(%d,%d)\n",(*iter)->id,(*iter)->position_x,(*iter)->position_y);
	}
	printf("接单数：%d\n",GlobalBillSum);
	printf("完成数：%d\n",GlobalBillAccomplish);
	printf("超时数：%d\n",GlobalBillovertime);
}