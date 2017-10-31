#include <cstdio>
#include <cstring>
#include <algorithm>

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
    int n = read<int>(),m = read<int>(),*values = new int[n];
    bool *visit = new bool[m + 1];
    memset(visit,false,sizeof(bool) * (m + 1));
    int nowCountVal = 0,head = 0,result = INF;
    bool startPop = false;
    for(int i = 0;i < n;i++) {
        values[i] = read<int>();
        if(!visit[value[i]]) {
            visit[value[i]] = true;
            nowCountVal++;
        }
        if(nowCountVal == m) {
            result = min(result,i - m + 1);

        }

    }
    return 0;
}
