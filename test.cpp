#include "lib/global/Header.hpp"

Position newP(int x,int y,int id){
    Position Tmp;
    Tmp.position_x = x;
    Tmp.position_y = y;
    Tmp.bill_id = id;
    return Tmp;
}
void Pr(RiderBag B){
    for(auto iter = B.begin();iter!=B.end();++iter){
        printf("%d ",(*iter).bill_id);
    }
    printf("\n");
}
void PrR(Rider *R){
    printf("骑手%d的位置：(%d,%d)\n",R->id,R->position_x,R->position_y);
}
int main(){
    Rider* R = new Rider(1);
    R->position_x = 0;
    R->position_y = 0;
    R->cur_position = newP(0,8,1);
    RiderBag B;
    B.push_back(newP(0,1,2));
    B.push_back(newP(0,2,3));
    B.push_back(newP(0,3,4));
    B.push_back(newP(0,4,5));
    B.push_back(newP(0,5,6));
    R->bag = B;
    int rx=0,ry=0;
    Alg_Path_getNextMove(R->position_x,R->position_y,R->cur_position,rx,ry);
    printf("%d %d\n",rx,ry);
    PrR(R);
    Pr(R->bag);
    adjustRider(R);
    Pr(R->bag);
    getPath(B,B);

}