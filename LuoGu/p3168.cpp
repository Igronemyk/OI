#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>
#include <cstddef>
#include <climits>

using namespace std;


const int MAX_TREAP_NODE_SIZE = 5000010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Graph {
    struct Edge {
        int next,to;
    };
    Edge *edges;
    int tot,*heads;

    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }
};

struct TreapNode {
    int ch[2],value,version,priority,size;
    long long sumValue;
    TreapNode() : value(0) , version(-1) , priority(0) , size(0) , sumValue(0) {
        ch[0] = 0;
        ch[1] = 0;
    }

    TreapNode(int value,int version) : value(value) , version(version) , priority(rand()) , size(1) , sumValue(value) {
        ch[0] = 0;
        ch[1] = 0;
    }

} tn[MAX_TREAP_NODE_SIZE];

int treapSize = 0;

struct Treap {
    int root,version;

    typedef pair<int,int> DRoot;

    Treap() : root(0) , version(-1) { }

    Treap(int version) : root(0) , version(version) { }

    Treap(int root,int version) : root(root) , version(version) { }

    int newNode(int value) {
        tn[++treapSize] = TreapNode(value,version);
        return treapSize;
    }

    int copyNode(int sign) {
        if(sign == 0) return 0;
        if(tn[sign].version == version) return sign;
        tn[++treapSize] = tn[sign];
        tn[treapSize].version = version;
        return treapSize;
    }

    void updateInfo(int now) {
        tn[now].size = tn[tn[now].ch[0]].size + tn[tn[now].ch[1]].size + 1;
        tn[now].sumValue = tn[tn[now].ch[0]].sumValue + tn[tn[now].ch[1]].sumValue + tn[now].value;
    }

    int merge(int a,int b) {
        if(a == 0) return b;
        if(b == 0) return a;
        if(tn[a].priority > tn[b].priority) {
            tn[a].ch[1] = merge(copyNode(tn[a].ch[1]),b);
            updateInfo(a);
            return a;
        }else {
            tn[b].ch[0] = merge(a,copyNode(tn[b].ch[0]));
            updateInfo(b);
            return b;
        }
    }

    DRoot split(int now,int k) {
        DRoot result(0,0);
        if(now == 0) return result;
        if(k <= tn[tn[now].ch[0]].size) {
            result = split(copyNode(tn[now].ch[0]),k);
            tn[now].ch[0] = result.second;
            updateInfo(now);
            result.second = now;
        }else {
            result = split(copyNode(tn[now].ch[1]),k - tn[tn[now].ch[0]].size - 1);
            tn[now].ch[1] = result.first;
            updateInfo(now);
            result.first = now;
        }
        return result;
    }

    int lowerCount(int value) {
        int result = 0,now = root;
        while(now != 0) {
            if(tn[now].value < value) {
                result += tn[tn[now].ch[0]].size + 1;
                now = tn[now].ch[1];
            }else {
                now = tn[now].ch[0];
            }
        }
        return result;
    }

    void insert(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        int newNodeSign = newNode(value);
        root = merge(tmp.first,merge(newNodeSign,tmp.second));
    }

    void remove(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        root = merge(tmp.first,split(tmp.second,1).second);
    }

    Treap copy(int newVersion) {
        Treap result(root,newVersion);
        result.root = result.copyNode(root);
        return result;
    }

    long long getResult(int k) {
        long long result = 0;
        int now = root;
        while(now != 0) {
            if(tn[tn[now].ch[0]].size < k) {
                k -= tn[tn[now].ch[0]].size  + 1;
                result += tn[tn[now].ch[0]].sumValue + tn[now].value;
                now = tn[now].ch[1];
            }else {
                now = tn[now].ch[0];
            }
        }
        return result;
    }

};

int main() {
    srand(1123469);
    int m = read<int>(),n = read<int>();
    Graph graph(m * 2,n + 2);//n + 1 is the end.
    while(m--) {
        int start = read<int>(),end = read<int>(),e = read<int>();
        graph.addEdge(start,e);
        graph.addEdge(end + 1,-e);
    }
    Treap *treaps = new Treap[n + 1];
    for(int nowTime = 1;nowTime <= n;nowTime++) {
        treaps[nowTime] = treaps[nowTime - 1].copy(nowTime);
        for(int i = graph.heads[nowTime];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(tmpEdge.to > 0) {
                treaps[nowTime].insert(tmpEdge.to);
            }else {
                treaps[nowTime].remove(-tmpEdge.to);
            }
        }
    }
    long long pre = 1;
    for(int i = 0;i < n;i++) {
        int x = read<int>(),a = read<int>(),b = read<int>(),c = read<int>();
        int k = ((pre * a + b) % c) + 1;
        pre = treaps[x].getResult(k);
        printf("%lld\n",pre);
    }
    return 0;
}
