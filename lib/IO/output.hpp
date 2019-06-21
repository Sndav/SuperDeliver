#include "../global/Header.hpp"

void PrintStatus(){
    FILE *fout;
    fout=fopen("output.txt","a");
    //int i;
    printf("时间:%d\n",GlobalTime);
    fprintf(fout,"时间:%d\n",GlobalTime);
    printf("钱:%d\n",GlobalMoney); // + (int)GlobalRiderList.size()*300 - 1000
    fprintf(fout,"钱:%d\n",GlobalMoney);
    printf("接单数:%d\n",GlobalBillSum);
    fprintf(fout,"接单数:%d\n",GlobalBillSum);
    printf("完成数:%d; ",GlobalBillAccomplish);
    fprintf(fout,"完成数:%d;",GlobalBillAccomplish);
    //Bill_print_finished();
    printf("结单:");fprintf(fout,"结单:");
    for(int i = 0; i < GlobalBillLog.size(); i++){
        Bill* R = GlobalBillLog[i];
        if((R->end_time == GlobalTime)&&(R->status == 3))
        printf("%d;",i);
        fprintf(fout,"%d;",i);
    }
    printf("\n");
    fprintf(fout,"\n");
    printf("超时数:%d;",GlobalBillovertime);
    fprintf(fout,"超时数:%d;",GlobalBillovertime);
    //Bill_print_violation_ticket();
    printf("罚单:");
    fprintf(fout,"罚单:");
    for(int i = 0; i < GlobalBillLog.size(); i++){
       if (Bill_return_id(i)!=NULL)
       printf("%d",i);
       fprintf(fout,"%d",i);
    }
    printf("\n");
    fprintf(fout,"\n");

	for(auto iter = GlobalRiderList.begin();iter!=GlobalRiderList.end();++iter){ 
        printf("骑手%d位置:%d,%d;停靠:",(*iter)->id,(*iter)->position_x,(*iter)->position_y);
        fprintf(fout,"骑手%d位置:%d,%d;停靠:",(*iter)->id,(*iter)->position_x,(*iter)->position_y);

		if((*iter)->arrive_po_x != -1 && (*iter)->arrive_po_y != -1){
            if((*iter)->arrive_type == 0){
                printf("食客");
                fprintf(fout,"食客");
            }
            if((*iter)->arrive_type == 1){
                printf("餐馆");
                fprintf(fout,"餐馆");
            }
            printf(" %d %d;",(*iter)->arrive_po_x,(*iter)->arrive_po_y);
            fprintf(fout," %d %d;",(*iter)->arrive_po_x,(*iter)->arrive_po_y);

			(*iter)->arrive_po_x = (*iter)->arrive_po_y = -1;
		}
		printf("\n");
        fprintf(fout,"\n");

	}
    fclose(fout);

}
