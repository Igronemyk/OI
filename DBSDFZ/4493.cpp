#include <cstdio>
#include <cstring>

using namespace std;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int MAXN = (int)(1e6) + 1;

namespace Adj{
    struct Node{
        int to,next;
    } nodes[MAXN * 2];
    int tot,heads[MAXN];
    void init(){
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }
    void addEdges(int u,int v){
        nodes[tot].to = v;
        nodes[tot].next = heads[u];
        heads[u] = tot++;
    }
}

int main(){
    int n = read<int>(), m = read<int>();
    for(int i = 0;i < n - 1;i++){

    }
    return 0;
}
