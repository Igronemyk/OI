#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 20010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

vector<int> graph[MAXN];

int visit[MAXN],nowTime,match[MAXN],N;

bool augment(int now) {
    for(vector<int>::iterator it = graph[now].begin();it != graph[now].end();it++) {
        int v = *it;
        if(visit[v] == nowTime) continue;
        visit[v] = nowTime;
        if(match[v] == -1 || augment(match[v])) {
            match[v] = now;
            match[now] = v;
            return true;
        }
    }
    return false;
}

int hungry() {
    memset(match,-1,sizeof(match));
    nowTime = 0;
    int result = 0;
    for(int i = N - 1;i >= 0;i--) {
        nowTime++;
        if(augment(i)) {
            result++;
        }
    }
    return result;
}

void addTwoEdges(int u,int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

int main() {
    N = read<int>();
    for(int i = 0;i < N;i++) {
        int dist = read<int>(),first = (i - dist + N) % N,second = (i + dist) % N;
        addTwoEdges(i,first + N);
        if(first != second) {
            addTwoEdges(i,second + N);
        }
    }
    for(int i = 0;i < 2 * N;i++) {
        sort(graph[i].begin(),graph[i].end());
    }
    if(hungry() != N) {
        printf("No Answer\n");
        return 0;
    }
    for(int i = 0;i < N;i++) {
        printf("%d ",match[i] - N);
    }
    printf("\n");
    return 0;
}
