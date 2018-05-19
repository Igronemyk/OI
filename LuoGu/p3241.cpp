#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>
#include <vector>

using namespace std;

const int MAXN = 150010;
const int MAX_DEPTH = 18;
const int INT_INF = 0x3f3f3f3f;
const long long LL_INF = 0x3f3f3f3f3f3f3f3f;

char xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
#define isd(c) ((c>='0'&&c<='9')||(c=='-'))

template<typename T>
inline bool rd(T& xa){
    char xchh; T f=1; while(xchh=getc(),(!isd(xchh))&&(xchh!=0));
    if(xchh==0) return 0; if(xchh=='-') xchh=getc(),f=-1; xa=xchh-'0';
    while(xchh=getc(),isd(xchh)) xa=xa*10+xchh-'0'; xa*=f; return 1;
}

template<typename T>
T read() {
    T val;
    rd(val);
    return val;
}

struct Graph {
    struct Edge {
        int next,to,weight;
    };
    Edge edges[MAXN * 2];
    int tot,heads[MAXN];

    Graph() : tot(0) {
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v,int w) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        edges[tot].weight = w;
        heads[u] = tot++;
    }
} graph,newGraph;

int valueLog2[MAXN * 2];

struct ST {
    int values[MAXN * 2][MAX_DEPTH + 1],length;

    ST() : length(0) {
        memset(values,0,sizeof(values));
    }

    void build() {
        int calLength = valueLog2[length];
        for(int j = 1;j <= calLength;j++) {
            for(int i = 0;i + (1 << j) - 1 < length;i++) {
                values[i][j] = min(values[i][j - 1],values[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int left,int right) {
        if(left > right) swap(left,right);
        int calLen = valueLog2[right - left + 1];
        return min(values[left][calLen],values[right - (1 << calLen) + 1][calLen]);
    }
} st;

int dis[MAXN],fathers[MAXN],dfn[MAXN],sizes[MAXN],age[MAXN];
bool visit[MAXN];

typedef pair<int,long long> Info;
vector<Info> sum1[MAXN],sum2[MAXN];

Info operator - (Info a,Info b) {
    return Info(a.first - b.first,a.second - b.second);
}

void getInfo(int now,int father) {
    dfn[now] = st.length;
    st.values[st.length++][0] = dis[now];
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        dis[tmpEdge.to] = dis[now] + tmpEdge.weight;
        getInfo(tmpEdge.to,now);
        st.values[st.length++][0] = dis[now];
    }
}

int getDis(int u,int v) {
    return dis[u] + dis[v] - 2 * st.query(dfn[u],dfn[v]);
}

int getSize(int now,int father) {
    int nowSize = 1;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to] || tmpEdge.to == father) continue;
        nowSize += getSize(tmpEdge.to,now);
    }
    return nowSize;
}

int getCenter(int now,int father,const int &nowTreeSize,int &nowRoot,int &nowRootSize) {
    int maxChild = 0,nowSize = 1;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to] || tmpEdge.to == father) continue;
        int tmpSize = getCenter(tmpEdge.to,now,nowTreeSize,nowRoot,nowRootSize);
        nowSize += tmpSize;
        maxChild = max(maxChild,tmpSize);
    }
    maxChild = max(maxChild,nowTreeSize - nowSize);
    if(nowRootSize > maxChild) {
        nowRootSize = maxChild;
        nowRoot = now;
    }
    return nowSize;
}

int build(int now) {
    int root = 0,rootSize = MAXN;
    int nowTreeSize = getSize(now,0);
    getCenter(now,0,nowTreeSize,root,rootSize);
    visit[root] = true;
    for(int i = graph.heads[root];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to]) continue;
        int to = build(tmpEdge.to);
        fathers[to] = root;
        newGraph.addEdge(root,to,tmpEdge.to);
    }
    return root;
}

void calcInfo(int now,const int &nowSign,const int &faSign) {
    int dis = getDis(faSign,now);
    sum1[faSign].push_back(Info(age[now],dis));
    sum2[nowSign].push_back(Info(age[now],dis));
    for(int i = newGraph.heads[now];i != -1;i = newGraph.edges[i].next) {
        Graph::Edge &tmpEdge = newGraph.edges[i];
        calcInfo(tmpEdge.to,nowSign,faSign);
    }
}

void initSize(int now) {
    sizes[now] = 1;
    for(int i = newGraph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = newGraph.edges[i];
        initSize(tmpEdge.to);
        sizes[now] += sizes[tmpEdge.to];
    }
}

void initInfo(int now) {
    sum1[now].reserve(sizes[now] + 2);
    sum1[now].push_back(Info(-1,0));
    for(int i = newGraph.heads[now];i != -1;i = newGraph.edges[i].next) {
        Graph::Edge &tmpEdge = newGraph.edges[i];
        sum2[tmpEdge.to].reserve(sizes[tmpEdge.to] + 2);
        sum2[tmpEdge.to].push_back(Info(-1,0));
        calcInfo(tmpEdge.to,tmpEdge.to,now);
        sum2[tmpEdge.to].push_back(Info(INT_INF,0));
        sort(sum2[tmpEdge.to].begin(),sum2[tmpEdge.to].end());
        for(vector<Info>::iterator it = sum2[tmpEdge.to].begin() + 1;it != sum2[tmpEdge.to].end();it++) {
            it->second += (it - 1)->second;
        }
        initInfo(tmpEdge.to);
    }
    sum1[now].push_back(Info(age[now],0));
    sum1[now].push_back(Info(INT_INF,0)); 
    sort(sum1[now].begin(),sum1[now].end());
    for(vector<Info>::iterator it = sum1[now].begin() + 1;it != sum1[now].end();it++) {
        it->second += (it - 1)->second;
    }
}

Info getInfo(vector<Info> &vec,int a,int b) {
    vector<Info>::iterator it1 = lower_bound(vec.begin(),vec.end(),Info(a,0)) - 1,it2 = upper_bound(vec.begin(),vec.end(),Info(b,LL_INF)) - 1; 
    return Info(it2 - it1,it2->second - it1->second);
}

long long getResult(int u,int a,int b) {
    int now = u;
    long long result = getInfo(sum1[u],a,b).second;
    while(fathers[now] != 0) {
        Info tmpInfo = getInfo(sum1[fathers[now]],a,b) - getInfo(sum2[now],a,b);
        int dis = getDis(fathers[now],u);
        result += tmpInfo.second + dis * 1LL * tmpInfo.first;
        now = fathers[now];
    }
    return result;
}

void init() {
    for(int i = 2;i < 2 * MAXN;i++) {
        valueLog2[i] = valueLog2[i >> 1] + 1;
    }
}

int main() {
    init();
    int n = read<int>(),Q = read<int>(),A = read<int>();
    for(int i = 1;i <= n;i++) {
        age[i] = read<int>();
    }
    for(int i = 0;i < n - 1;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>();
        graph.addEdge(u,v,w);
        graph.addEdge(v,u,w);
    }
    getInfo(1,0);
    st.build();
    int root = build(1);
    initSize(root);
    initInfo(root);
    long long lastAns = 0;
    while(Q--) {
        int u = read<int>(),a = static_cast<int>((lastAns + read<int>()) % A),b = static_cast<int>((lastAns + read<int>()) % A);
        if(a > b) swap(a,b);
        lastAns = getResult(u,a,b);
        printf("%lld\n",lastAns);
    }
    return 0;
}
