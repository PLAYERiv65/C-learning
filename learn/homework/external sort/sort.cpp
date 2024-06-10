#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;
const int Max = 2000;//每个小段数据的最大长度

struct Node{
    int val, from;
    bool operator< (const Node &a) const{
        return val > a.val;
    }
};//用于优先队列的比较

int main(){
    //从txt中读入数据，对小段数据进行内排序
    ifstream fin("input.txt");
    int *temp = new int[Max];//用于存放小段数据
    int cnt = 0;//数据段数
    int tot = 0;//数据总数
    int itemp = 0;//枚举变量
    while(fin >> temp[itemp]){
        tot++;
        itemp++;
        if(itemp == Max){
            sort(temp, temp + Max);
            ofstream fout("temp" + to_string(cnt) + ".txt");
            for(int i = 0; i < Max; i++){
                fout << temp[i] << endl;
            }
            cnt ++;
            itemp = 0;
        }
    }
    //特判最后一段数据
    if(itemp){
        sort(temp, temp + itemp);
        ofstream fout("temp" + to_string(cnt) + ".txt");
        for(int i = 0; i < itemp; i++){
            fout << temp[i] << endl;
        }
        cnt ++;
    }
    //释放内存
    delete [] temp;
    //对每个小段数据进行归并排序
    priority_queue<Node> q;
    vector<ifstream> finv(cnt);
    for(int i = 0; i < cnt; i++){
        finv[i].open("temp" + to_string(i) + ".txt");
        int val;
        finv[i] >> val;
        q.push({val, i});
    }
    //多路归并排序
    ofstream fout("output.txt");
    while(!q.empty()){
        Node now = q.top();
        q.pop();
        fout << now.val << endl;
        if(finv[now.from] >> now.val){
            q.push(now);
        }
    }
    //释放内存
    for(int i = 0; i < cnt; i++){
        finv[i].close();
    }
    return 0;
}