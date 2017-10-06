#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Data{
    int flat;
    int floor;
    Data() : flat(-1),floor(-1) {}
    Data(int flat,int floor) : flat(flat),floor(floor) {}
};

int main(){
    int n = read<int>(),m = read<int>();
    vector<Data> datas;
    datas.reserve(m);
    for(int i = 0;i < m;i++){
        int k = read<int>(),f = read<int>();
        datas.push_back(Data(k,f));
    }
    bool found = false;
    int result = -1;
    for(int i = 1;i <= 100;i++){
        bool flag = true;
        for(vector<Data>::iterator it = datas.begin();it != datas.end();it++){
            Data tmpData = *it;
            if(!(tmpData.floor * i >= tmpData.flat && tmpData.floor * i - i < tmpData.flat)){
                flag = false;
                break;
            }
        }
        if(flag){
            if(!found){
                found = true;
                result = i;
            }else if(n / result + (n % result == 0 ? 0 : 1) != n / i + (n % i == 0 ? 0 : 1)){
                result = -1;
                break;
            }
        }
    }
    printf("%d\n",result == -1 ? -1 : n / result + (n % result == 0 ? 0 : 1));
    return 0;
}
