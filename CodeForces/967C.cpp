#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <cstddef>
#include <set>
#include <cmath>

using namespace std;

const int INF = 0x3f3f3f3f;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int n = read<int>(),m = read<int>(),cl = read<int>(),ce = read<int>(),v = read<int>();
    set<int> valuesL,valuesE;
    for(int i = 0;i < cl;i++) {
        int tmpValue = read<int>();
        valuesL.insert(tmpValue);
    }
    for(int i = 0;i < ce;i++) {
        int tmpValue = read<int>();
        valuesE.insert(tmpValue);
    }
    int q = read<int>();
    while(q--) {
        int x1 = read<int>(),y1 = read<int>(),x2 = read<int>(),y2 = read<int>(),disX = abs(x1 - x2),minResult = INF;
        if(x1 == x2) {
            printf("%d\n",abs(y2 - y1));
            continue;
        }
        {
            set<int>::iterator it = valuesL.lower_bound(y1);
            if(it != valuesL.end()) {
                if(*it == y1) it++;
                if(it != valuesL.end()) {
                    int tmpResult = 0;
                    tmpResult += abs(*it - y1);
                    tmpResult += abs(*it - y2);
                    tmpResult += disX;
                    minResult = min(minResult,tmpResult);
                }
            }
            it = valuesL.lower_bound(y1);
            if(it != valuesL.begin()) {
                it--;
                    int tmpResult = 0;
                    tmpResult += abs(*it - y1);
                    tmpResult += abs(*it - y2);
                    tmpResult += disX;
                    minResult = min(minResult,tmpResult);
            }
        }
        disX = (disX + v - 1) / v;
        {
            set<int>::iterator it = valuesE.lower_bound(y1);
            if(it != valuesE.end()) {
               if(*it == y1) it++;
                if(it != valuesE.end()) {
                    int tmpResult = 0;
                    tmpResult += abs(*it - y1);
                    tmpResult += abs(*it - y2);
                    tmpResult += disX;
                    minResult = min(minResult,tmpResult);
                }
            }
            it = valuesE.lower_bound(y1);
            if(it!= valuesE.begin()) {
                it--;
                    int tmpResult = 0;
                    tmpResult += abs(*it - y1);
                    tmpResult += abs(*it - y2);
                    tmpResult += disX;
                    minResult = min(minResult,tmpResult);
            }
        }
        printf("%d\n",minResult);
    }
    return 0;
}
