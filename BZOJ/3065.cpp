#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_SCAPE_NODE_SIZE = 1e5;
const int MAX_TREAP_NODE_SIZE = 4e6;
const int MAX_SEGMENT_NDOE_SIZE = 4e6;
const int MAX_VAL_RANGE = 70010;
const int MIN_VAL_RANGE = 0 ;
const double MIN_TAG_RANGE = -1e9;
const double MAX_TAG_RANGE = 1e9;
const int MAXN = 35010;
const int BUFFER_SIZE = 1;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct ScapeNode {
    int ch[2],father,value,size;
    double tagL,tagR,tag;

    ScapeNode() : value(0) , size(0) {
        tagL = 0;
        tagR = 0;
        tag = 0;
        ch[0] = 0;
        ch[1] = 0;
    }

    ScapeNode(int father,int value,double tagL,double tagR) : father(father) , value(value) , size(1) , tagL(tagL) , tagR(tagR) , tag((tagL + tagR) / 2.0) {
        ch[0] = 0;
        ch[1] = 0;
    }

} sn[MAX_SCAPE_NODE_SIZE];

int scapeSize = 0,travelPos[MAX_SCAPE_NODE_SIZE],travelValue[MAX_SCAPE_NODE_SIZE],travelCnt = 0;

struct ScapeTree {

    const static double alpha = 0.75;

    int root;

    static int newNode(int father,int value,double tagL,double tagR) {
        sn[++scapeSize] = ScapeNode(father,value,tagL,tagR);
        return scapeSize;
    }

    void updateInfo(int now) {
        sn[now].size = sn[sn[now].ch[0]].size + sn[sn[now].ch[1]].size + 1;
    }

    int buildTree(int father,int left,int right,double tagL,double tagR) {
        if(left > right) return 0;
        int mid = (left + right) >> 1;
        int now = travelPos[mid];
        sn[now] = ScapeNode(father,travelValue[mid],tagL,tagR);
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

    int insertBefore(int value,int k) {
        int now = getKth(k),goat = 0,result = 0;
        if(now == 0) {
            now = root;
            while(sn[now].ch[1] != 0) {
                now = sn[now].ch[1];
            }
            sn[now].ch[1] = newNode(now,value,sn[now].tag,sn[now].tagR);
            result = sn[now].ch[1];
            goat = updateAndCheckGoat(now);
        }else if(sn[now].ch[0] == 0) {
            sn[now].ch[0] = newNode(now,value,sn[now].tagL,sn[now].tag);
            result = sn[now].ch[0];
            goat = updateAndCheckGoat(now);
        }else {
            now = sn[now].ch[0];
            while(sn[now].ch[1] != 0) {
                now = sn[now].ch[1];
            }
            sn[now].ch[1] = newNode(now,value,sn[now].tag,sn[now].tagR);
            result = sn[now].ch[1];
            goat = updateAndCheckGoat(now);
        }
        if(goat != 0) {
            rebuild(goat);
        }
        return result;
    }

    int getValue(int sign) {
        return sn[sign].value;
    }

    void setValue(int sign,int value) {
        sn[sign].value = value;
    }

    void travel(int now) {
        if(now == 0) return;
        travel(sn[now].ch[0]);
        travelPos[++travelCnt] = now;
        travelValue[travelCnt] = sn[now].value;
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

    void print() {
        //print(root);
        //printf("\n");
    }

    void print(int now) {
        if(now == 0) return;
        printf("(%d,%d,%.3lf) ",sn[now].value,now,sn[now].tag);
        print(sn[now].ch[1]);
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
    //return sn[a].tag <= sn[b].tag;
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

    int getKth(int l,int r,int k) {
        return getKth(root,MIN_VAL_RANGE,MAX_VAL_RANGE,l,r,k);
    }

    int getKth(int now,int left,int right,int l,int r,int k) {
        if(left == right) return left;
        int mid = (left + right) >> 1,cnt = segn[segn[now].ch[0]].treap.getCount(l,r);
        if(cnt < k) {
            k -= cnt;
            return getKth(segn[now].ch[1],mid + 1,right,l,r,k);
        }else {
            return getKth(segn[now].ch[0],left,mid,l,r,k);
        }
    }

};

int values[MAXN];

int main() {
    int n = read<int>();
    SegmentTree stree;
    for(int i = 1;i <= n;i++) {
        values[i] = read<int>();
        travelPos[++travelCnt] = i;
        travelValue[travelCnt] = values[i];
    }
    ScapeTree scapeTree;
    scapeTree.init();
    for(int i = 1;i <= n;i++) {
        stree.insert(values[i],i);
    }
    int q = read<int>();
    char *buffer = new char[BUFFER_SIZE + 1];
    int lastAns = 0;
    while(q--) {
        scanf("%s",buffer);
        switch(buffer[0]) {
            case 'Q': {
                int x = read<int>() ^ lastAns,y = read<int>() ^ lastAns,k = read<int>() ^ lastAns;
                x = scapeTree.getKth(x);
                y = scapeTree.getKth(y);
                lastAns = stree.getKth(x,y,k);
                printf("%d\n",lastAns);
                break;
            }
            case 'M': {
                int x = read<int>() ^ lastAns,val = read<int>() ^ lastAns;
                int sign = scapeTree.getKth(x);
                int value = scapeTree.getValue(sign);
                scapeTree.setValue(sign,val);
                stree.remove(value,sign);
                stree.insert(val,sign);
                break;
            }
            case 'I': {
                int x = read<int>() ^ lastAns,val = read<int>() ^ lastAns;
                int sign = scapeTree.insertBefore(val,x);
                stree.insert(val,sign);
                break;
            }
        }
    }
    return 0;
}
