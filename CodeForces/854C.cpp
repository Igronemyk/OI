#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Data{
    long long cost;
    int sign;
    Data() : cost(-1) , sign(-1) {}
    Data(int cost,int sign) : cost(cost) , sign(sign) {}
};

struct Comparator{

    bool operator()(Data d1,Data d2){
        return d1.cost < d2.cost;
    }
};



int main(){
    int n = read<int>(),k = read<int>();
    priority_queue<Data,vector<Data>,Comparator> que;
    long long result = 0;
    vector<int> ans(n,0);
    for(int i = 1;i <= n;i++){
        int cost = read<int>();
        Data tmpData(cost,i);
        que.push(tmpData);
        if(i <= k) continue;
        Data topData = que.top();
        que.pop();
        result += topData.cost * (i - topData.sign);
        ans[topData.sign - 1] = i;
    }
    for(int i = n + 1;i <= n + k;i++){
        Data topData = que.top();
        que.pop();
        result += topData.cost * (i - topData.sign);
        ans[topData.sign - 1] = i;
    }
    cout << result << endl;
    for(vector<int>::iterator it = ans.begin();it != ans.end();it++) cout << *it << " ";
    cout << endl;
    return 0;
}
