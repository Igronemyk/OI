// luogu-judger-enable-o2
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <utility>
#include <stack>
#include <vector>
#include <ctime>

using namespace std;

const int MAX_DEPTH = 17;
const int MAXN = 1e5 + 10;
const double alpha = 0.75;
const int MODDER = 1e9;

namespace FastIO

{
    const size_t str=1<<16;
    struct Reader
    {
        char buf[str],*s,*t;
        Reader():s(),t(),buf(){}
        inline char pick()
        {
            return (s==t)?(t=buf+fread(s=buf,1,str,stdin),*s++):(*s++);
        }
        Reader& operator >> (int &x)
        {
            register char c;
            do c=pick(); while(c<'0'||c>'9');
            x=0;
            while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-'0',c=pick();
            return *this;
        }
    }cin;
    struct Writer
    {
        char buf[str],*s,*t;
        Writer():s(buf),t(buf+str),buf(){}
        ~Writer(){fwrite(buf,1,s-buf,stdout);}
        inline void echo(char c)
        {
            (s==t)?(fwrite(s=buf,1,str,stdout),*s++=c):(*s++=c);
        }
        Writer& operator << (long long x)
        {
            if(!x) return echo('0'),*this;
            register char a[21],t=1;
            while(x) a[t++]=x%10,x/=10;
            while(--t) echo(a[t]+'0');
            return *this;
        }
        Writer& operator << (const char* s)
        {
            while(*s) echo(*s++);
            return *this;
        }
    }cout;
    const char *endl="\n";
}
using FastIO::cin;
using FastIO::cout;
using FastIO::endl;

struct LCAGetter {
    int fathers[MAXN][MAX_DEPTH + 1];
    int depths[MAXN];
    long long dis[MAXN];
    
    LCAGetter() {
        memset(fathers,0,sizeof(fathers));
        memset(depths,0,sizeof(depths));
        memset(dis,0,sizeof(dis));
    }


    int getLCA(int u,int v) {
        if(u == v) return u;
        if(depths[u] < depths[v]) {
            swap(u,v);
        }
        for(int i = MAX_DEPTH;i >= 0;i--) {
            if(depths[fathers[u][i]] >= depths[v]) {
                u = fathers[u][i];
            }
        }
        if(u == v) return u;
        for(int i = MAX_DEPTH;i >= 0;i--) {
            if(fathers[u][i] != fathers[v][i]) {
                u = fathers[u][i];
                v = fathers[v][i];
            }
        }
        return fathers[u][0];
    }

    long long getDis(int u,int v) {
        return dis[u] + dis[v] - 2LL * dis[getLCA(u,v)];
    }

    void addInfo(int now,int father,long long weight) {
        fathers[now][0] = father;
        for(int i = 1;i <= MAX_DEPTH;i++) {
            fathers[now][i] = fathers[fathers[now][i - 1]][i - 1];
        }
        depths[now] = depths[father] + 1;
        dis[now] = dis[father] + weight;
    }
} lcaGetter;

struct Graph {
    struct Edge {
        int next,to;
        long long weight;
        Edge() : next(-1) , to(0) , weight(0) { } 
    };
    Edge edges[MAXN * 3];
    int rec[MAXN * 3],recSize;
    int tot,heads[MAXN];

    Graph() : recSize(0) , tot(0) {
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v,long long w) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        edges[tot].weight = w;
        heads[u] = tot++;
    }

    void addTwoEdges(int u,int v,long long w) {
        addEdge(u,v,w);
        addEdge(v,u,w);
    }

} graph;

vector<int> virtualGraph[MAXN];

void changeLink(int u,int oldSign,int newSign) {
    for(vector<int>::iterator it = virtualGraph[u].begin();it != virtualGraph[u].end();it++) {
        if(*it == oldSign) {
            *it = newSign;
            break;
        }
    }
}

template<typename F,typename S>
struct Pair {
    F first;
    S second;

    Pair() : first(0) , second(0) { } 

    Pair(F first,S second) : first(first) , second(second) { } 
};

namespace TreapSpace {
    
    const static int MAX_TREAP_NODE_SIZE = 4e6;

    int ch[MAX_TREAP_NODE_SIZE][2],siz[MAX_TREAP_NODE_SIZE],pri[MAX_TREAP_NODE_SIZE],fa[MAX_TREAP_NODE_SIZE];
    long long val[MAX_TREAP_NODE_SIZE];
    int rec[MAX_TREAP_NODE_SIZE],recSZ,sZ;

    struct Treap {

        int root;

        Treap() : root(0) { }

        int newNode(long long value,int father) {
            int sign;
            if(recSZ != 0) {
                sign = rec[recSZ--];
                if(ch[sign][0] != 0) delNode(ch[sign][0]);
                if(ch[sign][1] != 0) delNode(ch[sign][1]);
            }else {
                sign = ++sZ;
            }
            ch[sign][0] = 0;
            ch[sign][1] = 0;
            siz[sign] = 1;
            pri[sign] = rand();
            fa[sign] = father;
            val[sign] = value;
            return sign;
        }

        void delNode(int sign) {
            if(sign == 0) return;
            rec[++recSZ] = sign;
        }

        void del() {
            delNode(root);
            root = 0;
        }

        void reInit() {
            root = 0;
        }
        
        void upd(int now) {
            siz[now] = siz[ch[now][0]] + siz[ch[now][1]] + 1;
        }

        int lowCnt(long long value) {
            int res = 0,now = root;
            while(now != 0) {
                if(val[now] < value) {
                    res += siz[ch[now][0]] + 1;
                    now = ch[now][1];
                }else {
                    now = ch[now][0];
                }
            }
            return res;
        }

        void rotate(int now) {
            int father = fa[now],anc = fa[father];
            if(anc != 0) {
                ch[anc][ch[anc][1] == father] = now;
            }
            fa[now] = anc;
            fa[father] = now;
            int dir = ch[father][0] == now;
            ch[father][!dir] = ch[now][dir];
            ch[now][dir] = father;
            if(ch[father][!dir] != 0) {
                fa[ch[father][!dir]] = father;
            }
            if(fa[now] == 0) {
                root = now;
            }
            upd(father);
            upd(now);
        }
        
        void insert(int now,long long value) {
            if(val[now] < value) {
                if(ch[now][1] == 0) {
                    ch[now][1] = newNode(value,now);
                }else {
                    insert(ch[now][1],value);
                }
                if(pri[ch[now][1]] < pri[now]) {
                    rotate(ch[now][1]);
                }
            }else {
                if(ch[now][0] == 0) {
                    ch[now][0] = newNode(value,now);
                }else {
                    insert(ch[now][0],value);
                }
                if(pri[ch[now][0]] < pri[now]) {
                    rotate(ch[now][0]);
                }
            }
            upd(now);
        }

        void insert(long long value) {
            if(root == 0) {
                root = newNode(value,0);
                return;
            }
            insert(root,value);
        }

        int getRes(long long value) {
            int cnt = lowCnt(value);
            return siz[root] - cnt;
        }

    };
}

using TreapSpace::Treap;

int tmpSize[MAXN];
bool visit[MAXN],needBuild[MAXN];

int getSize(int now,int father) {
    int result = 1;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father || visit[tmpEdge.to] || !needBuild[tmpEdge.to]) continue;
        result += getSize(tmpEdge.to,now);
    }
    return result;
}

void getRoot(int now,int father,int &nowRoot,int &nowRootSize,const int nowTreeSize) {
    tmpSize[now] = 1;
    int maxChildSize = 0;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father || visit[tmpEdge.to] || !needBuild[tmpEdge.to]) continue;
        getRoot(tmpEdge.to,now,nowRoot,nowRootSize,nowTreeSize);
        tmpSize[now] += tmpSize[tmpEdge.to];
        maxChildSize = max(maxChildSize,tmpSize[tmpEdge.to]);
    }
    maxChildSize = max(maxChildSize,nowTreeSize - tmpSize[now]);
    if(maxChildSize < nowRootSize) {
        nowRootSize = maxChildSize;
        nowRoot = now;
    }
}

stack<int> nodes;
int fathers[MAXN],sizes[MAXN];
long long values[MAXN],result;
Treap addValues[MAXN],minValues[MAXN];

void calcInfo(int now,int father,long long dis,Treap &infos) {
    infos.insert(values[now] - dis);
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father || visit[tmpEdge.to] || !needBuild[tmpEdge.to]) continue;
        calcInfo(tmpEdge.to,now,dis + tmpEdge.weight,infos);
    }
}

int build(int now,int father) {
    int root = 0,nowRootSize = MAXN;
    getRoot(now,father,root,nowRootSize,getSize(now,father));
    visit[root] = true;
    needBuild[root] = false;
    nodes.push(root);
    sizes[root] = 1;
    calcInfo(root,0,0,addValues[root]);
    for(int i = graph.heads[root];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father || visit[tmpEdge.to] || !needBuild[tmpEdge.to]) continue;
        Treap temp;
        calcInfo(tmpEdge.to,root,tmpEdge.weight,temp);
        int to = build(tmpEdge.to,root);
        fathers[to] = root;
        minValues[to] = temp;
        virtualGraph[root].push_back(to);
        sizes[root] += sizes[to];
    }
    return root;
}

void markBuild(int now,bool isRoot) {
    needBuild[now] = true;
    addValues[now].del();
    if(!isRoot) {
        minValues[now].del();
    }else {
        minValues[now].reInit();
    }
    for(vector<int>::iterator it = virtualGraph[now].begin();it != virtualGraph[now].end();it++) {
        markBuild(*it,false);
    }
    virtualGraph[now].clear();
}

void rebuild(int now,int father) {
    Treap temp = minValues[now];
    markBuild(now,true);
    int root = build(now,father);
    minValues[root] = temp;
    fathers[root] = father;
    changeLink(father,now,root);
    while(!nodes.empty()) {
        int sign = nodes.top();
        nodes.pop();
        visit[sign] = false;
    }
}

void cntResult(int sign) {
    int now = sign;
    result += addValues[sign].getRes(0 - values[sign]);
    while(fathers[now] != 0) {
        long long dis = lcaGetter.getDis(sign,fathers[now]);
        result += addValues[fathers[now]].getRes(dis - values[sign]);
        result -= minValues[now].getRes(dis - values[sign]); 
        now = fathers[now];
    }
    result--;
}

void insert(int sign,int father,long long weight,long long value) {
    graph.addTwoEdges(sign,father,weight);
    lcaGetter.addInfo(sign,father,weight);
    values[sign] = value;
    fathers[sign] = father;
    virtualGraph[father].push_back(sign);
    int now = sign,goat = 0;
    while(now != 0) {
        sizes[now]++;
        if(fathers[now] != 0) {
            double limit = (sizes[fathers[now]] + 1) * alpha;
            if(sizes[fathers[now]] + 1 > 30 && sizes[now] > limit) {
                goat = fathers[now];
            }
        }
        now = fathers[now];
    }
    now = sign;
    addValues[now].insert(values[now]);
    while(fathers[now] != 0) {
        long long dis = lcaGetter.getDis(sign,fathers[now]);
        long long insertValue = values[sign] - dis;
        addValues[fathers[now]].insert(insertValue);
        minValues[now].insert(insertValue);
        now = fathers[now];
    }
    if(goat != 0) {
        rebuild(goat,fathers[goat]);
    }
    cntResult(sign);
}

int main() {
    srand(time(NULL));
    int n;
    cin >> n >> n;
    for(int i = 1;i <= n;i++) {
        int a,b,r;
        cin >> a >> b >> r;
        a ^= static_cast<int>(result % MODDER);
        if(a == 0) {
            values[i] = r;
            addValues[i].insert(values[i]);
            sizes[i]++;
            cout << result << endl;
            continue;
        }
        insert(i,a,b,r);
        cout << result << endl;
    }
    return 0;
}
