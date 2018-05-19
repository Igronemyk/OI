#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MAXM = 6000010;
const int MAXN = 500010;
const long long INF = 0x3f3f3f3f3f3f3f3f;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

long long dis[MAXN];
bool visit[MAXN];
int values[MAXN];

int main() {
    int N = read<int>();
    long long minValue = read<long long>() - 1,maxValue = read<long long>();
    for(int i = 0;i < N;i++) {
        values[i] = read<int>();
    }
    sort(values,values + N);
    int initValue = values[0];
    for(int i = 0;i < initValue;i++) dis[i] = INF;
    queue<int> que;
    dis[0] = 0;
    que.push(0);
    while(!que.empty()) {
        int now = que.front();
        que.pop();
        visit[now] = false;
        for(int i = 1;i < N;i++) {
            int v = (now + values[i]) % initValue;
            if(dis[v] <= dis[now] + values[i]) continue;
            dis[v] = dis[now] + values[i];
            if(!visit[v]) {
                visit[v] = true;
                que.push(v);
            }
        }
    }
    long long result = 0;
    result += maxValue / initValue;
    for(int i = 1;i < initValue;i++) {
        if(dis[i] <= maxValue) {
            result += (maxValue - dis[i]) / initValue + 1;
        }
    }
    result -= minValue / initValue;
    for(int i = 1;i < initValue;i++) {
        if(dis[i] <= minValue) {
            result -= (minValue - dis[i]) / initValue + 1;
        }
    }
    printf("%lld\n",result);
    return 0;
}
