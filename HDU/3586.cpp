#include <cstdio>
#include <algorithm>

using namespace std;

namespace Adj {
    int size, head[1000];
    struct Node{
        int v, w, next;
    } E[1998];
    inline void initAdj(){
        size = 0;
        fill(head,head + 1000,-1);
    }
    inline void addEdge(int u, int v, int w) {
        E[size].v = v;
        E[size].w = w;
        E[size].next = head[u];
        head[u] = size++;
    }
}

using namespace Adj;

int n,m,value;
int f[1000];
const int INF = 1000001;


void dp(int now,int fatherId){
    if(E[head[now]].v == fatherId && E[head[now]].next == -1) {
        f[now] = INF;
        return;
    }
    int tmpAns = 0;
    for(int i = head[now];~i;i = E[i].next){
        if(E[i].v == fatherId) continue;
        dp(E[i].v,now);
        tmpAns += min(E[i].w > value ? INF : E[i].w,f[E[i].v]);
    }
    f[now] = tmpAns;
}


int main(){
    while(~scanf("%d%d",&n,&m) && n + m){
        initAdj();
        int left = 0,right = 0;
        for(int i = 0;i < n - 1;i++){
            int nodeA,nodeB,weight;
            scanf("%d%d%d",&nodeA,&nodeB,&weight);
            nodeA--;nodeB--;
            addEdge(nodeA,nodeB,weight);
            addEdge(nodeB,nodeA,weight);
            right = max(right,weight);
        }
        int ans = INF;
        while(left <= right){
            int mid = (left + right) >> 1;
            value = mid;
            dp(0,-1);
            if(f[0] <= m){
                right = mid - 1;
                ans = min(ans,mid);
            }else{
                left = mid + 1;
            }
        }
        printf("%d\n",ans == INF ? -1 : ans);
    }
    return 0;
}

