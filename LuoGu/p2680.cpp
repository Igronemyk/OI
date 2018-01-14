#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstddef>

using namespace std;

const int INF = 0x3f3f3f3f;

template <std::size_t bufferSize = 1U << 15>
class quick_read
{
public:
    static std::size_t buffer_size()
    {
        return bufferSize;
    }

    static int getchar()
    {
        if (S == T)
        {
            S = buffer;
            T = buffer + std::fread(buffer, 1, buffer_size(), stdin);
            if (S == T)
            {
                return EOF;
            }
        }
        return *S++;
    }

    template <typename UnsignedInteger>
    static UnsignedInteger scan()
    {
        char c = getchar();
        UnsignedInteger ret = 0;
        for (; c < '0' || c > '9'; c = getchar());
        for (; c >= '0' && c <= '9'; c = getchar())
        {
            ret = ret * 10 + (c - '0');
        }
        return ret;
    }

    template <typename UnsignedInteger>
    static int scan(UnsignedInteger &ref)
    {
        int c = getchar();
        if (c == EOF)
        {
            return EOF;
        }
        ref = 0;
        for (; c < '0' || c > '9'; c = getchar());
        for (; c >= '0' && c <= '9'; c = getchar())
        {
            ref = ref * 10 + (c - '0');
        }
        return 1;
    }

private:
    static char buffer[bufferSize];
    static char *S;
    static char *T;
};

template<typename T>
T read() {
    return quick_read<>::scan<T>();
}

template <std::size_t bufferSize>
char quick_read<bufferSize>::buffer[bufferSize];

template <std::size_t bufferSize>
char *quick_read<bufferSize>::S;

template <std::size_t bufferSize>
char *quick_read<bufferSize>::T;

struct Graph {
    struct Edge {
        int next,to,weight;
    } *edges;
    int tot,*heads;

    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v,int w) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        edges[tot].weight = w;
        heads[u] = tot++;
    }

};

struct AdjList{
    struct Node {
        int next,to,sign;
    } *nodes;
    int tot,*heads;

    AdjList(int nodeSize,int headSize) {
        nodes = new Node[nodeSize];
        tot = 0;
        heads = new int[headSize];
        memset(heads,-1,sizeof(int) * headSize);
    }

    void addNode(int u,int v,int sign) {
        nodes[tot].to = v;
        nodes[tot].next = heads[u];
        nodes[tot].sign = sign;
        heads[u] = tot++;
    }

};

struct BCS {
    int *father;
    BCS(int size) {
        father = new int[size];
        for(int i = 0;i < size;i++) father[i] = i;
    }

    int getFather(int pos) {
        if(father[pos] == pos) return pos;
        father[pos] = getFather(father[pos]);
        return father[pos];
    }

    void merge(int u,int v) {
        int faU = getFather(u) , faV = getFather(v);
        if(faU == faV) return;
        father[faU] = faV;
    }

    bool isLinked(int u,int v) {
        return getFather(u) == getFather(v);
    }

};

struct Info {
    int u,v,lca;
};

int n,m;

void tarjan(int now,int father,int nowDis,Graph &graph,AdjList &querys,BCS &bcset,Info *result,int *dis,bool *visit,int *fatherEdgeValue) {
    dis[now] = nowDis;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        fatherEdgeValue[tmpEdge.to] = tmpEdge.weight;
        tarjan(tmpEdge.to,now,nowDis + tmpEdge.weight,graph,querys,bcset,result,dis,visit,fatherEdgeValue);
        bcset.merge(tmpEdge.to,now);
    }
    visit[now] = true;
    for(int i = querys.heads[now];i != -1;i = querys.nodes[i].next) {
        AdjList::Node &tmpNode = querys.nodes[i];
        if(!visit[tmpNode.to]) continue;
        result[tmpNode.sign].lca = bcset.getFather(tmpNode.to);
    }
}

void updateInfo(int now,int father,Graph &graph,int *pointValue) {
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        updateInfo(tmpEdge.to,now,graph,pointValue);
        pointValue[now] += pointValue[tmpEdge.to];
    }
}

bool check(int mid,Graph &graph,Info *infos,int *dis,int *pointValue,int *fatherEdgeValue) {
    memset(pointValue,0,sizeof(int) * n);
    int outOfRangeMax = 0,countEdge = 0;
    for(int i = 0;i < m;i++) {
        Info &tmpInfo = infos[i];
        int nowDis = dis[tmpInfo.u] + dis[tmpInfo.v] - 2 * dis[tmpInfo.lca];
        if(nowDis <= mid) continue;
        pointValue[tmpInfo.u]++;
        pointValue[tmpInfo.v]++;
        pointValue[tmpInfo.lca] -= 2;
        outOfRangeMax = max(outOfRangeMax,nowDis - mid);
        countEdge++;
    }
    updateInfo(0,-1,graph,pointValue);
    for(int i = 0;i < n;i++) {
        if(pointValue[i] == countEdge && fatherEdgeValue[i] >= outOfRangeMax) {
            return true;
        }
    }
    return false;
}

int main() {
    n = read<int>();m = read<int>();
    Graph graph((n - 1) * 2,n);
    for(int i = 0;i < n - 1;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>();
        u--; v--;
        graph.addEdge(u,v,w);
        graph.addEdge(v,u,w);
    }
    Info *infos = new Info[m];
    AdjList querys(m * 2,n);
    for(int i = 0;i < m;i++) {
        infos[i].u = read<int>() - 1;
        infos[i].v = read<int>() - 1;
        querys.addNode(infos[i].u,infos[i].v,i);
        querys.addNode(infos[i].v,infos[i].u,i);
    }
    BCS bcset(n);
    int *dis = new int[n],*pointValue = new int[n],*fatherEdgeValue = new int[n];
    memset(dis,0,sizeof(int) * n);
    bool *visit = new bool[n];
    memset(visit,false,sizeof(bool) * n);
    tarjan(0,-1,0,graph,querys,bcset,infos,dis,visit,fatherEdgeValue);
    int left = 0,right = INF,ans = INF;
    while(left <= right) {
        int mid = (left + right) >> 1;
        if(check(mid,graph,infos,dis,pointValue,fatherEdgeValue)) {
            ans = min(ans,mid);
            right = mid - 1;
        }else {
            left = mid + 1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
