#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
#include <vector>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

typedef pair<int,int> Info;

map<int,Info> val1;
map<Info,int> val2;

int main() {
    int n = read<int>(),m = read<int>();
    int nowCnt = 0,result = 0;
    for(int nowTime = 1;nowTime <= m;nowTime++) {
        int value = read<int>();
        if(val1.count(value) != 0) {
            Info tmpInfo = val1[value];
            val2.erase(val2.find(tmpInfo));
            tmpInfo.first++;
            val2[tmpInfo] = value;
            val1[value].first++;
            result++;
            continue;
        }
        if(nowCnt < n) {
            Info tmpInfo = {1,nowTime};
            val1[value] = tmpInfo;
            val2[tmpInfo] = value;
            nowCnt++;
            continue;
        }
        int sign = (*val2.begin()).second;
        val1.erase(val1.find(sign));
        val2.erase(val2.begin());
        Info tmpInfo = {1,nowTime};
        val1[value] = tmpInfo;
        val2[tmpInfo] = value;
    }
    printf("%d\n",result);
    return 0;
}
