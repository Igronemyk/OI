#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <utility>

using namespace std;

const int MAX_TREAP_NODE_SIZE = 2100000;
const int MAX_SEGMENT_NODE_SIZE = 2100000;

struct TreapNode {
    int ch[2],value,priority,size;

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

struct Treap {

    typedef pair<int,int> DRoot;

    int root;

    Treap() : root(0) { }

    static int newNode(int value) {
        tn[++treapSize] = TreapNode(value);
        return treapSize;
    }

    static void updateInfo(int now) {
        tn[now].size = tn[tn[now].ch[0]].size + tn[tn[now].ch[1]].size + 1;
    }

    static int merge(int a,int b) {
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

    static DRoot split(int now,int k) {
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
        return now;
    }

    int lowerCount(int value) {
        int now = root,result = 0;
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

    int getSize(int left,int right) {
        int leftCnt = lowerCount(left),rightCnt = lowerCount(right + 1);
        return rightCnt - leftCnt;
    }

};

struct SegmentNode {
    int ch[2],value,left,right;
    Treap treap;
} sn[MAX];

int main() {
    return 0;
}

//1800000
