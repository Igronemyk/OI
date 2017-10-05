#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int myPow(int a,int b){
    int result = 1,base =a;
    while(b){
        if(b & 1) result *= base;
        base *= base;
        b >>= 1;
    }
    return result;
}

string strs[202];
int kValue[202];

bool visit[64];

int main(){
    int n;
    cin >> n;
    for(int i = 0;i < n;i++){
        cin >> strs[i];
        for(int k = 1;strs[i].size() >= myPow(2,k);k++){
            int stateCount = myPow(2,k);
            memset(visit,false,sizeof(visit));
            int tmpValue = 0;
            for(int j = 0;j < k;j++) tmpValue = (tmpValue << 1) + strs[i][j] - '0';
            visit[tmpValue] = true;
            for(int j = k;j < strs[i].size();j++){
                tmpValue = min(tmpValue,tmpValue ^ (1 << (k - 1)));
                tmpValue = (tmpValue << 1) + strs[i][j] - '0';
                visit[tmpValue] = true;
            }
            bool flag = true;
            for(int j = 0;j < stateCount;j++) if(!visit[j]) {flag = false;break;}
            if(flag){
                kValue[i] = max(kValue[i],k);
            }else break;
        }
    }
    int optCount;
    cin >> optCount;
    for(int i = 0;i < optCount;i++){
        int index1,index2,newIndex = n + i;
        cin >> index1 >> index2;
        index1--;index2--;
        strs[newIndex] = strs[index1] + strs[index2];
        kValue[newIndex] = max(kValue[index1],kValue[index2]);
        for(int k = kValue[newIndex] + 1;strs[newIndex].size() >= myPow(2,k);k++){
            int stateCount = myPow(2,k);
            memset(visit,false,sizeof(visit));
            int tmpValue = 0;
            for(int j = 0;j < k;j++) tmpValue = (tmpValue << 1) + strs[newIndex][j] - '0';
            visit[tmpValue] = true;
            for(int j = k;j < strs[newIndex].size();j++){
                tmpValue = min(tmpValue,tmpValue ^ (1 << (k - 1)));
                tmpValue = (tmpValue << 1) + strs[newIndex][j] - '0';
                visit[tmpValue] = true;
            }
            bool flag = true;
            for(int j = 0;j < stateCount;j++) if(!visit[j]) {flag = false;break;}
            if(flag){
                kValue[newIndex] = max(kValue[newIndex],k);
            }else break;
        }
        printf("%d\n",kValue[newIndex]);
    }
    return 0;
}
