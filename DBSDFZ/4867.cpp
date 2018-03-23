#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>
#include <stack>

using namespace std;

const int MIN_VAL_RANGE = 0;
const int MAX_VAL_RANGE = 2e8 + 10;
const int MAX_TREAP_NODE_SIZE = 2e5 + 10;
const int MAXN = 1e5 + 10;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct TreapNode {
    int ch[2],value,lazy,priority,size;
    long long sumValue;

    TreapNode() : value(0) , lazy(0) , priority(0) , size(0) , sumValue(0) {
        ch[0] = 0;
        ch[1] = 0;
    }

    TreapNode(int value) : value(value) , lazy(0) , priority(rand()) , size(1) , sumValue(value) {
        ch[0] = 0;
        ch[1] = 0;
    }

} tn[MAX_TREAP_NODE_SIZE];

int treapSize = 0,gcValue[MAX_TREAP_NODE_SIZE],gcTop = 0;

struct Treap {

    typedef pair<int,int> DRoot;

    int root;

    Treap() : root(0) { }

    static int newNode(int value) {
        int sign;
        if(gcTop != 0) {
            sign = gcValue[gcTop];
            gcTop--;
        }else {
            sign = ++treapSize;
        }
        tn[sign] = TreapNode(value);
        return sign;
    }

    void updateInfo(int now) {
        tn[now].size = tn[tn[now].ch[0]].size + tn[tn[now].ch[1]].size + 1;
        tn[now].sumValue = tn[tn[now].ch[0]].sumValue + tn[tn[now].ch[1]].sumValue + tn[now].value;
    }

    void updateLazyTag(int now,int tag) {
        if(now == 0) return;
        tn[now].lazy += tag;
        tn[now].value += tag;
        tn[now].sumValue += tn[now].size * 1LL * tag;
    }

    void pushDown(int now) {
        if(now == 0) return;
        if(tn[now].lazy == 0) return;
        updateLazyTag(tn[now].ch[0],tn[now].lazy);
        updateLazyTag(tn[now].ch[1],tn[now].lazy);
        tn[now].lazy = 0;
    }

    int merge(int a,int b) {
        if(a == 0) return b;
        if(b == 0) return a;
        pushDown(a);
        pushDown(b);
        if(tn[a].priority > tn[b].priority) {
            tn[a].ch[1] = merge(tn[a].ch[1],b);
            updateInfo(a);
            return a;
        }else {
            tn[b].ch[0] = merge(a,tn[b].ch[0]);
            updateInfo(b);
            return b;
        }
    }

    DRoot split(int now,int k) {
        DRoot result(0,0);
        if(now == 0) return result;
        pushDown(now);
        if(k <= tn[tn[now].ch[0]].size) {
            result = split(tn[now].ch[0],k);
            tn[now].ch[0] = result.second;
            updateInfo(now);
            result.second = now;
        }else {
            result = split(tn[now].ch[1],k - tn[tn[now].ch[0]].size - 1);
            tn[now].ch[1] = result.first;
            updateInfo(now);
            result.first = now;
        }
        return result;
    }

    int lowerCount(int value) {
        int result = 0,now = root;
        while(now != 0) {
            pushDown(now);
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

    void addAll(int value) {
        updateLazyTag(root,value);
    }


    /*
    long long getResult(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        long long result = tn[tmp.first].sumValue;
        root = merge(tmp.first,tmp.second);
        return value * 1LL * cnt - result;
    }
    */

    int getResult(int value) {
        int maxUnableResult = MIN_VAL_RANGE,minAbleResult = MAX_VAL_RANGE;
        int now = root,extraCnt = 0,maxUnableCnt = 0;
        long long extraValue = 0,maxUnableValue = 0;
        while(now != 0) {
            pushDown(now);
            int nowCnt = tn[tn[now].ch[0]].size + extraCnt + 1;
            long long nowValue = tn[tn[now].ch[0]].sumValue + extraValue + tn[now].value;
            if(tn[now].value * 1LL * nowCnt - nowValue >= value) {
                minAbleResult = min(minAbleResult,tn[now].value);
                now = tn[now].ch[0];
            }else {
                if(tn[now].value >= maxUnableResult) {//平衡树内的值可能相等，这种情况下总是取右侧更优
                    maxUnableResult = tn[now].value;
                    maxUnableCnt = nowCnt;
                    maxUnableValue = nowValue;
                }
                extraCnt = nowCnt;
                extraValue = nowValue;
                now = tn[now].ch[1];
            }
        }
        if(maxUnableCnt == 0) {
            return minAbleResult;
        }else {
            long long nowValue = value + maxUnableValue;
            nowValue = (nowValue + maxUnableCnt - 1) / maxUnableCnt;
            return min(static_cast<int>(nowValue),minAbleResult);
        }
    }

    int getSize() {
        return tn[root].size;
    }

    void join(Treap &otherTreap) {
        travel(otherTreap.root);
        otherTreap.root = 0;
    }

    void travel(int now) {
        if(now == 0) return;
        pushDown(now);
        travel(tn[now].ch[0]);
        insert(tn[now].value);
        travel(tn[now].ch[1]);
        gcValue[++gcTop] = now;
    }

    static Treap merge(Treap &a,Treap &b) {
        if(a.getSize() > b.getSize()) {
            a.join(b);
            return a;
        }else {
            b.join(a);
            return b;
        }
    }
};

struct Graph {
    struct Edge {
        int next,to,weight;
    };
    Edge edges[MAXN * 2];
    int tot,heads[MAXN];

    Graph() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v,int w) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        edges[tot].weight = w;
        heads[u] = tot++;
    }
} graph;

Treap treaps[MAXN];
int result = MIN_VAL_RANGE,values[MAXN];


void dfs(int now,int father) {
    bool isLeaf = true;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        dfs(tmpEdge.to,now);
        isLeaf = false;
        treaps[tmpEdge.to].addAll(tmpEdge.weight);
        treaps[now] = Treap::merge(treaps[now],treaps[tmpEdge.to]);
    }
    if(isLeaf) {
        treaps[now].insert(0);
        return;
    }
    int nowResult = treaps[now].getResult(values[now]);
    result = max(result,nowResult);
    treaps[now].insert(nowResult);
}

/*
int father[MAXN];
bool visit[MAXN];

void dfs(int root) {
    stack<int> stk;
    stk.push(root);
    while(!stk.empty()) {
        int now = stk.top();
        stk.pop();
        if(!visit[now]) {
            visit[now] = true;
            stk.push(now);
            for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
                Graph::Edge &tmpEdge = graph.edges[i];
                if(tmpEdge.to == father[now]) continue;
                father[tmpEdge.to] = now;
                stk.push(tmpEdge.to);
            }
        }else {
            bool isLeaf = true;
            for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
                Graph::Edge &tmpEdge = graph.edges[i];
                if(tmpEdge.to == father[now]) continue;
                isLeaf = false;
                treaps[tmpEdge.to].addAll(tmpEdge.weight);
                treaps[now] = Treap::merge(treaps[now],treaps[tmpEdge.to]);
            }
            if(isLeaf) {
                treaps[now].insert(0);
                continue;
            }
            int left = MIN_VAL_RANGE,right = MAX_VAL_RANGE,nowResult = MAX_VAL_RANGE;
            while(left <= right) {
                int mid = (left + right) >> 1;
                if(treaps[now].getResult(mid) >= values[now]) {
                    nowResult = min(nowResult,mid);
                    right = mid - 1;
                }else {
                    left = mid + 1;
                }
            }
            result = max(result,nowResult);
            treaps[now].insert(nowResult);
        }
    }
}
*/

int main() {
    int n = read<int>();
    for(int i = 1;i <= n;i++) {
        values[i] = read<int>();
    }
    for(int i = 0;i < n - 1;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>();
        graph.addEdge(u,v,w);
        graph.addEdge(v,u,w);
    }
    dfs(1,0);
    printf("%d\n",result);
    return 0;
}
