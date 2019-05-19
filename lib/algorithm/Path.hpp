#include "../global/Header.hpp"

class TSP_Unit{
public:
    int path[100];
    int length;//个体价值
};

/*
使用方法：
构造函数 传入vector<Position>
执行 .work
使用 int getRes(vector<Position> &res)获取
*/

class TSP_Group{
public:
    RiderBag Plist;
    int city_num;//城市数量
    const int unit_num = 100;//群体规模
    int ps = 10;//变异概率
    const int genmax = 500;//最大迭代数
    TSP_Unit group[100];
    TSP_Unit best;
    int best_gen;

    TSP_Group(RiderBag List){
        Plist = List;
        city_num = Plist.size();
        best.length = 0x3f3f3f3f;
        best_gen = 0;
        for(int i = 0; i < unit_num; i++){
            bool flag[100] = {};

            for(int j = 0; j < city_num; j++){
                int t_city = rand()%city_num;
                while(flag[t_city])
                    t_city = rand()%city_num;
                flag[t_city] = true;
                group[i].path[j] = t_city;
            }
        }
    }

    int getDis(int i,int j){
        Position A = Plist[i];
        Position B = Plist[j];
        return abs(A.position_x - B.position_x) + abs(A.position_y - B.position_y);
    }
    //对每个个体进行评估
    void assess(){
        for(int k = 0; k < unit_num; k++){
            int rel = 0;
            for(int i = 1; i < city_num; i++)
                rel += getDis(group[k].path[i-1],group[k].path[i]);
            group[k].length = rel;
        }
    }

    //根据评估结果对个体进行排序
    void unit_sort(){
        for(int i = 0; i < unit_num; i++){
            for(int j = i+1; j < unit_num; j++){
                if(group[i].length > group[j].length){
                    TSP_Unit temp;
                    memcpy(&temp, &group[i], sizeof(TSP_Unit));
                    memcpy(&group[i], &group[j], sizeof(TSP_Unit));
                    memcpy(&group[j], &temp, sizeof(TSP_Unit));
                }
            }
        }
    }

    //交叉
    TSP_Unit cross(TSP_Unit &father, TSP_Unit &mother){
        int l = rand()%city_num;
        int r = rand()%city_num;
        if(l > r)
            swap(l, r);

        bool flag[100] = {};
        for(int i = l; i <= r; i++)
            flag[father.path[i]] = true;

        TSP_Unit son;
        int pos = 0;

        for(int i = 0; i < l; i++){
            while(flag[mother.path[pos]])
                pos++;
            son.path[i] = mother.path[pos++];
        }
        for(int i = l; i <= r; i++)
            son.path[i] = father.path[i];
        for(int i = r+1; i < city_num; i++){
            while(flag[mother.path[pos]])
                pos++;
            son.path[i] = mother.path[pos++];
        }

        return son;
    }

    //突变
    void mutation(TSP_Unit &t){
        int proport = rand() % 100;

        if(proport > ps)
            return;
        int one = rand()%city_num;
        int two = rand()%city_num;
        while(two != one)
            two = rand()%city_num;
        swap(t.path[one], t.path[two]);
    }

    //输出信息
    int getRes(RiderBag &res){
        RiderBag ret;
        for(int j = 0; j < city_num; j++){
            ret.push_back(Plist[group[0].path[j]]);
        }
        res = ret;
        return group[0].length;
    }

    //种群进化
    void work(){
        for(int i = 0; i < genmax; i++){
            //如果进化层数大于20，加大变异的概率
            if(i > 20)
                ps *= 3;
            assess();//评估
            unit_sort();//根据评估结果排序
            if(best.length > group[0].length){
                memcpy(&best, &group[0], sizeof(group[0]));
                best_gen = i;
            }
            for(int j = 0; j+2 < unit_num; j+=3)
                group[j+2] = cross(group[j], group[j+1]);
            for(int j = 0; j < city_num; j++)//变异(从1开始，保留最优)
                mutation(group[j]);
        }
    }

};

int getPath(vector<Position> input,vector<Position> &res){
    auto TSP = TSP_Group(input);
    TSP.work();
    return TSP.getRes(res);
}

void adjustPath(vector<Position> &input, int start_id){
    vector<Position> tmp;
    int i;
    for(i = 0;i<input.size();i++){
        if(input[i].bill_id == start_id) break;
    }
    for(int j = 0;j<input.size();j++){
        tmp.push_back( input[(j+i) % (input.size())] );
    }
    input = tmp;
}

void adjustRider(Rider* &R){
    RiderBag tmp = R->bag;
    tmp.push_back(R->cur_position);
    getPath(tmp,tmp);
    adjustPath(tmp,R->cur_position.bill_id);
    tmp.erase(tmp.begin());
    R->bag = tmp;
}
/*
    获取下一步走法
*/
void Alg_Path_getNextMove(int x,int y,Position Target,int &r_x,int &r_y){
    // 反正怎么走长度都是一样的不如先横着在竖着。
    // OK TODO:这里需要考虑几个问题 对于一个目的地可以到达其周围4个点 如何知道怎么到达其中的一个点呢？
    // 感觉其实好像不用纠结这个问题，毕竟也多不了几步。
    /*
        如果本来在左方 -> 到左边那个地方
        在右方 -> 右方
    */
    int t_x = Target.position_x; 
    int t_y = Target.position_y;

    if(x < t_x-1 || x == t_x){r_x = 1;r_y =0;return;} 
    if(x > t_x+1){r_x = -1;r_y =0;return;}
    if(x == t_x+1 || x == t_x-1){
        if(y == t_y){r_x = r_y = 0;return;}
        r_x = 0;
        r_y = (t_y > y)?1:-1;
        return;
    }

}