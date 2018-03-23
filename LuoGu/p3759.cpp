#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_TREAP_NODE_SIZE = 4e6;
const int MAX_SEGMENT_NODE_SIZE = 2e6;
const int MAXN = 50010;
const int MODDER = 1e9 + 7;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct TreapNode {
    int ch[2],value,weight,priority,size;
    long long sumWeight;

    TreapNode() : value(0) , weight(0) , sumWeight(0) , priority(0) , size(0) {
        ch[0] = 0;
        ch[1] = 0;
    }

    TreapNode(int value,int weight) : value(value) , weight(weight) , sumWeight(weight) , priority(rand()) , size(1) {
        ch[0] = 0;
        ch[1] = 0;
    }

} tn[MAX_TREAP_NODE_SIZE];;

int treapSize = 0;

struct Result {
    int cnt1,cnt2;
    long long weight1,weight2;

    Result() : cnt1(0) , weight1(0) , cnt2(0) , weight2(0) { }
    Result(int cnt1,long long weight1,int cnt2,long long weight2) : cnt1(cnt1) , weight1(weight1) , cnt2(cnt2) , weight2(weight2) { }

    void operator += (const Result &otherResult) {
        cnt1 += otherResult.cnt1;
        weight1 = (weight1 + otherResult.weight1) % MODDER;
        cnt2 += otherResult.cnt2;
        weight2 = (weight2 + otherResult.weight2) % MODDER;
    }

};

struct Treap {

    typedef pair<int,int> DRoot;

    int root;

    Treap() : root(0) { }

    static int newNode(int value,int weight) {
        tn[++treapSize] = TreapNode(value,weight);
        return treapSize;
    }

    void updateInfo(int now) {
        tn[now].size = tn[tn[now].ch[0]].size + tn[tn[now].ch[1]].size + 1;
        tn[now].sumWeight = (tn[tn[now].ch[0]].sumWeight + tn[tn[now].ch[1]].sumWeight + tn[now].weight) % MODDER;
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
            if(tn[now].value < value) {
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
            if(tn[now].value <= value) {
                result += tn[tn[now].ch[0]].size + 1;
                now = tn[now].ch[1];
            }else {
                now = tn[now].ch[0];
            }
        }
        return result;
    }

    void insert(int value,int weight) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        int newNodeSign = newNode(value,weight);
        root = merge(tmp.first,merge(newNodeSign,tmp.second));
    }

    void remove(int value) {
        int cnt = lowerCount(value);
        DRoot tmp1 = split(root,cnt),tmp2 = split(tmp1.second,1);
        root = merge(tmp1.first,tmp2.second);
    }

    Result getResult(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        Result result(cnt,tn[tmp.first].sumWeight,tn[tmp.second].size,tn[tmp.second].sumWeight);
        root = merge(tmp.first,tmp.second);
        return result;
    }
};

struct SegmentNode {
    int ch[2];
    Treap treap;

    SegmentNode() : treap(Treap()) {
        ch[0] = 0;
        ch[1] = 0;
    }

} sn[MAX_SEGMENT_NODE_SIZE];

int segmentSize = 0;



struct SegmentTree {
    int root,left,right;

    static int newNode() {
        sn[++segmentSize] = SegmentNode();
        return segmentSize;
    }

    SegmentTree(int left,int right) : left(left) , right(right) {
        root = newNode();
    }


    void insert(int pos,int value,int weight) {
        insert(root,left,right,pos,value,weight);
    }

    void insert(int now,int left,int right,int pos,int value,int weight) {
        sn[now].treap.insert(value,weight);
        if(left == right) return;
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            if(sn[now].ch[0] == 0) {
                sn[now].ch[0] = newNode();
            }
            insert(sn[now].ch[0],left,mid,pos,value,weight);
        }else {
            if(sn[now].ch[1] == 0) {
                sn[now].ch[1] = newNode();
            }
            insert(sn[now].ch[1],mid + 1,right,pos,value,weight);
        }
    }

    void change(int pos,int oldValue,int newValue,int newWeight) {
        change(root,left,right,pos,oldValue,newValue,newWeight);
    }

    void change(int now,int left,int right,int pos,int oldValue,int newValue,int newWeight) {
        sn[now].treap.remove(oldValue);
        sn[now].treap.insert(newValue,newWeight);
        if(left == right) return;
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            change(sn[now].ch[0],left,mid,pos,oldValue,newValue,newWeight);
        }else {
            change(sn[now].ch[1],mid + 1,right,pos,oldValue,newValue,newWeight);
        }
    }

    Result getResult(int l,int r,int value) {
        return getResult(root,left,right,l,r,value);
    }

    Result getResult(int now,int left,int right,int l,int r,int value) {
        if(now == 0) return Result();
        if(left == l && right == r) {
            return sn[now].treap.getResult(value);
        }
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                return getResult(sn[now].ch[0],left,mid,l,r,value);
            }else {
                Result tmpResult = getResult(sn[now].ch[0],left,mid,l,mid,value);
                tmpResult += getResult(sn[now].ch[1],mid + 1,right,mid + 1,r,value);
                return tmpResult;
            }
        }else {
            return getResult(sn[now].ch[1],mid + 1,right,l,r,value);
        }
    }

};

long long values[MAXN],weight[MAXN];

int main() {
    int n = read<int>(),m = read<int>();
    SegmentTree stree(1,n);
    long long result = 0;
    for(int i = 1;i <= n;i++) {
        values[i] = read<int>();
        weight[i] = read<int>();
        if(i != 1) {
            Result tmpResult = stree.getResult(1,i - 1,values[i]);
            result = (result + (tmpResult.cnt2 * weight[i]) % MODDER) % MODDER;
            result = (result + tmpResult.weight2) % MODDER;
        }
        stree.insert(i,values[i],weight[i]);
    }
    while(m--) {
        int left = read<int>(),right = read<int>();
        if(left == right) {
            printf("%lld\n",result);
            continue;
        }
        if(left > right) {
            swap(left,right);
        }
        int calLeft = left + 1,calRight = right - 1;
        if(calLeft <= calRight) {
            {
                Result tmpResult = stree.getResult(calLeft,calRight,values[left]);
                result = (result + (tmpResult.cnt2 * weight[left]) % MODDER) % MODDER;
                result = (result + tmpResult.weight2) % MODDER;
                result = ((result - (tmpResult.cnt1 * weight[left]) % MODDER) % MODDER + MODDER) % MODDER;
                result = ((result - tmpResult.weight1) % MODDER + MODDER) % MODDER;
            }
            {
                Result tmpResult = stree.getResult(calLeft,calRight,values[right]);
                result = (result + (tmpResult.cnt1 * weight[right] % MODDER)) % MODDER;
                result = (result + tmpResult.weight1) % MODDER;
                result = ((result - (tmpResult.cnt2 * weight[right]) % MODDER) % MODDER + MODDER) % MODDER;
                result = ((result - tmpResult.weight2) % MODDER + MODDER) % MODDER;
            }
        }
        if(values[left] < values[right]) {
            result = ((result + weight[left]) % MODDER + weight[right]) % MODDER;
        }else {
            result = ((result - (weight[left] + weight[right]) % MODDER) % MODDER + MODDER) % MODDER;
        }
        stree.change(left,values[left],values[right],weight[right]);
        stree.change(right,values[right],values[left],weight[left]);
        swap(values[left],values[right]);
        swap(weight[left],weight[right]);
        printf("%lld\n",result);
    }
    return 0;
}
