#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

inline int read(){
    int result = 0,f = 1;char c = getchar();
    while(c > '9' || c < '0'){if(c == '-')f *= -1;c = getchar();}
    while(c <= '9' && c >= '0'){result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int N,m,result = INF;

struct Edge{
    int to,dep,p,r,next;
    Edge() : to(-1),dep(-1),p(-1),r(-1),next(-1) {}
    Edge(int to,int dep,int p,int r) : to(to), dep(dep),p(p),r(r),next(-1) {}
};

struct Graph{
    Edge edges[10];
    int visit[10],head[10],nowSize;
    void init(){
        nowSize = 0;
        memset(head,-1,sizeof(head));
        memset(visit,0,sizeof(visit));
    }
    int addEdge(int a,int b,int c,int p,int r){
        edges[nowSize] = Edge(b,c,p,r);
        edges[nowSize].next = head[a];
        head[a] = nowSize++;
    }
};

Graph graph;

void dfs(int nowNode,int nowWeight){
    if(nowWeight > result) return;
    if(nowNode == N - 1){
        result = nowWeight;
        return;
    }
    for(int i = graph.head[nowNode];i != -1;i = graph.edges[i].next){
        if(graph.visit[graph.edges[i].to] > 3) continue;
        graph.visit[graph.edges[i].to]++;
        if(graph.visit[graph.edges[i].dep] > 0){
            dfs(graph.edges[i].to,nowWeight + graph.edges[i].p);
        }else{
            dfs(graph.edges[i].to,nowWeight + graph.edges[i].r);
        }
        graph.visit[graph.edges[i].to]--;
    }
}

int main(){
    while(~scanf("%d%d",&N,&m)){
        result = INF;
        graph.init();
        for(int i = 0;i < m;i++){
            int a = read(),b = read(),c = read(),p = read(),r = read();
            a--;b--;c--;
            graph.addEdge(a,b,c,p,r);
        }
        dfs(0,0);
        if(result == INF){
            printf("impossible\n");
        }else{
            printf("%d\n",result);
        }
    }
    return 0;
}
