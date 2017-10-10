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


int main(){
    double *nowTimes = new double[3];
    nowTimes[0] = read<int>();
    nowTimes[1] = read<int>();
    nowTimes[2] = read<int>();
    nowTimes[0] *= 5;
    if(nowTimes[0] == 60) nowTimes[0] = 0;
    nowTimes[0] += (nowTimes[1] * 60 + nowTimes[2]) / 3600;
    nowTimes[1] += (nowTimes[2]) / 60;
    sort(nowTimes,nowTimes + 3);
    int timeA = read<int>(),timeB = read<int>();
    timeA *= 5;
    timeB *= 5;
    if(timeA == 60) timeA = 0;
    if(timeB == 60) timeB = 0;
    int rangeA = 3,rangeB = 3;
    if(timeA >= nowTimes[0] &&timeA <= nowTimes[1]){
        rangeA = 1;
    }else if(timeA >= nowTimes[1] &&timeA <= nowTimes[2]){
        rangeA = 2;
    }
    if(timeB >= nowTimes[0] && timeB <= nowTimes[1]){
        rangeB = 1;
    }else if(timeB >= nowTimes[1] && timeB <= nowTimes[2]){
        rangeB = 2;
    }
    printf((rangeA == rangeB) ? "YES\n" : "NO\n");
    return 0;
}
