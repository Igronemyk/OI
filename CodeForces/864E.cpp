#include <cstdio>
#include <algorithm>
#include <stack>

using namespace std;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Item{
    int time,limit,value,sign;
    Item() : time(-1) , limit(-1) , value(-1) ,sign(-1) {}
    Item(int time,int limit,int value,int sign) :time(time) ,limit(limit),value(value),sign(sign) {}
};

struct Data{
    int value,nowSave;
    Data *prev;
    Data() : value(0),nowSave(-1),prev(NULL) {}
    Data(int value,int nowSave,Data *prev) : value(value),nowSave(nowSave),prev(prev){}
};

struct Comparator{
    bool operator () (Item i1,Item i2){
        return i1.limit < i2.limit;
    }
};

Data *dp[2010];

int main(){
    int n = read<int>();
    Item *items = new Item[n];
    //for(int i = 0;i < n;i++) items[i] = Item(read<int>(),read<int>(),read<int>(),i);
    for(int i = 0;i < n;i++) {
        int time = read<int>(),limit = read<int>(),value = read<int>();
        items[i] = Item(time,limit,value,i);
    }
    sort(items,items + n,Comparator());
    int result = 0,maxTime = 0;
    for(int i = 0;i <= 2010;i++) dp[i] = new Data();
    for(int i = 0;i < n;i++){
        for(int j = 2000;j >= 0;j--){
            if(j < items[i].time || j >= items[i].limit) continue;
            if(dp[j - items[i].time]->value + items[i].value > dp[j]->value){
                Data *newData = new Data(dp[j - items[i].time]->value + items[i].value,items[i].sign,dp[j - items[i].time]);
                dp[j] = newData;
               }
            if(dp[j]->value > result){
                result = dp[j]->value;
                maxTime = j;
            }
        }
    }
    int countItems = 0;
    Data *doing = dp[maxTime];
    stack<int> stk;
    while(doing->nowSave != -1){
        stk.push(doing->nowSave);
        doing = doing->prev;
        countItems++;
    }
    printf("%d\n%d\n",result,countItems);
    while(!stk.empty()){
        printf("%d ",stk.top() + 1);
        stk.pop();
    }
    printf("\n");
    return 0;
}
