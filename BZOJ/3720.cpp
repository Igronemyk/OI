#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>
#include <map>
#include <cctype>

using namespace std;

const int MAX_SCAPE_NODE_SIZE = 120010;
const int MAX_TREAP_NODE_SIZE = 2e6;
const int MAX_SEGMENT_NDOE_SIZE = 2e6;
const int MAX_VAL_RANGE = 1e8;
const int MIN_VAL_RANGE = 0;
const double MIN_TAG_RANGE = -1e9;
const double MAX_TAG_RANGE = 1e9;
const int MAXN = 60010;

namespace FastIO{
    const int L=(1<<21)+1;
    struct io{
        char ibuf[L],*iS,*iT,obuf[L],*oS,*oT,c,st[55];
        int tp;
        void flush(){fwrite(obuf,1,oS-obuf,stdout),oS=obuf;}
        void putc(char x){
            *oS++=x;
            if(oS==oT)flush();
        }
        char gc(){return iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,L,stdin),(iS==iT?EOF:*iS++)):*iS++;}
        template<class T>T rd(){
            register T x=0;
            while(!isdigit(c=gc()));
            for(;isdigit(c);c=gc())x=x*10+(c&15);
            return x;
        }
        template<class T>void print(register T x){
            if(!x)putc('0');
            else{
                for(tp=0;x;st[tp++]=x%10+48,x/=10);
                for(tp--;~tp;putc(st[tp--]));
            }
            putc('\n');
        }
        io():oS(obuf),oT(obuf+L-1){}
        ~io(){flush();}
    }ip;
}

template<typename T>
T read() {
    return FastIO::ip.rd<T>();
}

template<typename T>
void print(T value) {
    FastIO::ip.print<T>(value);
}

struct Graph {
    struct Edge {
        int next,to;
    };
    Edge edges[MAXN * 2];
    int tot,heads[MAXN];

    Graph() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }
} graph;

struct ScapeNode {
    int ch[2],father,size;
    double tagL,tagR,tag;

    ScapeNode() : size(0) {
        tagL = 0;
        tagR = 0;
        tag = 0;
        ch[0] = 0;
        ch[1] = 0;
    }

    ScapeNode(int father,double tagL,double tagR) : father(father) , size(1) , tagL(tagL) , tagR(tagR) , tag((tagL + tagR) / 2.0) {
        ch[0] = 0;
        ch[1] = 0;
    }

} sn[MAX_SCAPE_NODE_SIZE];

int scapeSize = 0,travelPos[MAX_SCAPE_NODE_SIZE],travelCnt = 0;

struct ScapeTree {

    const static double alpha = 0.75;

    int root;

    static int newNode(int father,double tagL,double tagR) {
        sn[++scapeSize] = ScapeNode(father,tagL,tagR);
        return scapeSize;
    }

    void updateInfo(int now) {
        sn[now].size = sn[sn[now].ch[0]].size + sn[sn[now].ch[1]].size + 1;
    }

    int buildTree(int father,int left,int right,double tagL,double tagR) {
        if(left > right) return 0;
        int mid = (left + right) >> 1;
        int now = travelPos[mid];
        sn[now] = ScapeNode(father,tagL,tagR);
        sn[now].ch[0] = buildTree(now,left,mid - 1,tagL,sn[now].tag);
        sn[now].ch[1] = buildTree(now,mid + 1,right,sn[now].tag,tagR);
        updateInfo(now);
        return now;
    }

    void init() {
        root = buildTree(0,1,travelCnt,MIN_TAG_RANGE,MAX_TAG_RANGE);
        scapeSize += travelCnt;
        travelCnt = 0;
    }

    int getKth(int k) {
        int now = root;
        while(now != 0) {
            int leftChildSize = sn[sn[now].ch[0]].size;
            if(leftChildSize + 1 == k) {
                break;
            }else if(leftChildSize + 1 < k) {
                k -= leftChildSize + 1;
                now = sn[now].ch[1];
            }else {
                now = sn[now].ch[0];
            }
        }
        return now;
    }

    bool check(int now) {
        if(now == 0) return false;
        return (sn[sn[now].ch[0]].size > sn[now].size * alpha) || (sn[sn[now].ch[1]].size > sn[now].size * alpha);
    }

    int updateAndCheckGoat(int now) {
        int goat = 0;
        while(now != 0) {
            updateInfo(now);
            if(check(now)) {
                goat = now;
            }
            now = sn[now].father;
        }
        return goat;
    }

    int insertAfter(int now) {
        if(now == 0) return 0;
        int goat = 0,result = 0;
        if(sn[now].ch[1] == 0) {
            sn[now].ch[1] = newNode(now,sn[now].tag,sn[now].tagR);
            result = sn[now].ch[1];
            goat = updateAndCheckGoat(now);
        }else {
            now = sn[now].ch[1];
            while(sn[now].ch[0] != 0) {
                now = sn[now].ch[0];
            }
            sn[now].ch[0] = newNode(now,sn[now].tagL,sn[now].tag);
            result = sn[now].ch[0];
            goat = updateAndCheckGoat(now);
        }
        if(goat != 0) {
            rebuild(goat);
        }
        return result;
    }

    void travel(int now) {
        if(now == 0) return;
        travel(sn[now].ch[0]);
        travelPos[++travelCnt] = now;
        travel(sn[now].ch[1]);
    }

    void rebuild(int now) {
        int father = sn[now].father;
        int direction = (father == 0) ? -1 : (sn[father].ch[1] == now);
        double tagL = sn[now].tagL,tagR = sn[now].tagR;
        travel(now);
        int newNodeSign = buildTree(father,1,travelCnt,tagL,tagR);
        if(father != 0) {
            sn[father].ch[direction] = newNodeSign;
            updateInfo(father);
        }else {
            root = newNodeSign;
        }
        travelCnt = 0;
    }
};

struct TreapNode {
    int ch[2];
    int value,priority,size;

    TreapNode() : value(0) , priority(0) , size(0) {
        ch[0] = 0;
        ch[1] = 0;
    }

    TreapNode(int value) : value(value) , priority(rand()) , size(1) {
        ch[0] = 0;
        ch[1] = 0;
    }

} tn[MAX_TREAP_NODE_SIZE];

int treapSize = 0;

bool compLess(int a,int b) {
    return sn[a].tag < sn[b].tag;
}

bool compNotGreater(int a,int b) {
    if(a == b) return true;
    return sn[a].tag < sn[b].tag;
}

struct Treap {

    typedef pair<int,int> DRoot;

    int root;

    Treap() : root(0) { }

    static int newNode(int value) {
        tn[++treapSize] = TreapNode(value);
        return treapSize;
    }

    void updateInfo(int now) {
        if(now == 0) return;
        tn[now].size = tn[tn[now].ch[0]].size + tn[tn[now].ch[1]].size + 1;
    }

    int merge(int a,int b) {
        if(a == 0) return b;
        if(b == 0) return a;
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
            if(compLess(tn[now].value,value)) {
                result += tn[tn[now].ch[0]].size + 1;
                now = tn[now].ch[1];
            }else {
                now = tn[now].ch[0];
            }
        }
        return result;
    }

    int upperCount(int value) {
        int result = 0,now = root;
        while(now != 0) {
            if(compNotGreater(tn[now].value,value)) {
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
        DRoot tmp1 = split(root,cnt),tmp2 = split(tmp1.second,1);
        root = merge(tmp1.first,tmp2.second);
    }

    int getCount(int left,int right) {
        return upperCount(right) - lowerCount(left);
    }

    void print() {
        print(root);
        printf("\n");
    }

    void print(int now) {
        if(now == 0) return;
        print(tn[now].ch[0]);
        printf("%d ",tn[now].value);
        print(tn[now].ch[1]);
    }

};

struct SegmentNode {
    int ch[2];
    Treap treap;

    SegmentNode() : treap(Treap()) {
        ch[0] = 0;
        ch[1] = 0;
    }
} segn[MAX_SEGMENT_NDOE_SIZE];

int segSize = 0;

struct SegmentTree {
    int root;

    static int newNode() {
        segn[++segSize] = SegmentNode();
        return segSize;
    }

    SegmentTree() {
        root = newNode();
    }


    void insert(int pos,int value) {
        insert(root,MIN_VAL_RANGE,MAX_VAL_RANGE,pos,value);
    }

    void insert(int now,int left,int right,int pos,int value) {
        segn[now].treap.insert(value);
        if(left == right) return;
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            if(segn[now].ch[0] == 0) {
                segn[now].ch[0] = newNode();
            }
            insert(segn[now].ch[0],left,mid,pos,value);
        }else {
            if(segn[now].ch[1] == 0) {
                segn[now].ch[1] = newNode();
            }
            insert(segn[now].ch[1],mid + 1,right,pos,value);
        }
    }

    void remove(int pos,int value) {
        remove(root,MIN_VAL_RANGE,MAX_VAL_RANGE,pos,value);
    }

    void remove(int now,int left,int right,int pos,int value) {
        segn[now].treap.remove(value);
        if(left == right) return;
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            remove(segn[now].ch[0],left,mid,pos,value);
        }else {
            remove(segn[now].ch[1],mid + 1,right,pos,value);
        }
    }

    int getGreaterThan(int x,int l,int r) {
        return getGreaterThan(root,MIN_VAL_RANGE,MAX_VAL_RANGE,x + 1,MAX_VAL_RANGE,l,r);
    }

    int getGreaterThan(int now,int left,int right,int l,int r,int queryL,int queryR) {
        if(now == 0) return 0;
        if(left == l && right == r) {
            return segn[now].treap.getCount(queryL,queryR);
        }
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                return getGreaterThan(segn[now].ch[0],left,mid,l,r,queryL,queryR);
            }else {
                return getGreaterThan(segn[now].ch[0],left,mid,l,mid,queryL,queryR) + getGreaterThan(segn[now].ch[1],mid + 1,right,mid + 1,r,queryL,queryR);
            }
        }else {
            return getGreaterThan(segn[now].ch[1],mid + 1,right,l,r,queryL,queryR);
        }
    }

};

ScapeTree scapeTree;
SegmentTree stree;

int values[MAXN],startSigns[MAXN],endSigns[MAXN];

void dfs(int now,int father) {
    ++travelCnt;
    travelPos[travelCnt] = travelCnt;
    startSigns[now] = travelCnt;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        dfs(tmpEdge.to,now);
    }
    ++travelCnt;
    travelPos[travelCnt] = travelCnt;
    endSigns[now] = travelCnt;
}

int main() {
    srand(654321);
    int n = read<int>();
    for(int i = 0;i < n - 1;i++) {
        int u = read<int>(),v = read<int>();
        graph.addEdge(u,v);
        graph.addEdge(v,u);
    }
    for(int i = 1;i <= n;i++) {
        values[i] = read<int>();
    }
    dfs(1,0);
    scapeTree.init();
    for(int i = 1;i <= n;i++) {
        stree.insert(values[i],startSigns[i]);
    }
    int m = read<int>(),lastAns = 0,nowIndex = n;
    while(m--) {
        int opt = read<int>(),u = read<int>() ^ lastAns,x = read<int>() ^ lastAns;
        switch(opt) {
            case 0: {
                lastAns = stree.getGreaterThan(x,startSigns[u],endSigns[u]);
                print(lastAns);
                break;
            }
            case 1: {
                stree.remove(values[u],startSigns[u]);
                values[u] = x;
                stree.insert(values[u],startSigns[u]);
                break;
            }
            case 2: {
                ++nowIndex;
                int sign = nowIndex;
                int startSign = scapeTree.insertAfter(startSigns[u]);
                int endSign = scapeTree.insertAfter(startSign);
                startSigns[sign] = startSign;
                endSigns[sign] = endSign;
                values[sign] = x;
                stree.insert(values[sign],startSigns[sign]);
                break;
            }
        }
    }
    return 0;
}
