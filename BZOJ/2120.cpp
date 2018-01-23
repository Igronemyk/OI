#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <utility>
#include <set>

using namespace std;

const int MAX_TREAP_NODE_SIZE = 200010;
const int MAX_SEGMENT_NODE_SIZE = 40010;
const int MAX_COLOR_RANGE = 1000010;
const int BUFFER_SIZE = 2;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= - 1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

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
} n[MAX_TREAP_NODE_SIZE];

int treapNodeSize = 0;

struct Treap {
    int root;

    typedef pair<int,int> DRoot;

    Treap() : root(0) { }

    static int newNode(int value) {
        n[++treapNodeSize] = TreapNode(value);
        return treapNodeSize;
    }

    static void updateInfo(int now) {
        if(now == 0) return;
        n[now].size = n[n[now].ch[0]].size + n[n[now].ch[1]].size + 1;
    }

    static int merge(int a,int b) {
        if(a == 0) return b;
        if(b == 0) return a;
        if(n[a].priority > n[b].priority) {
            n[a].ch[1] = merge(n[a].ch[1],b);
            updateInfo(a);
            return a;
        }else {
            n[b].ch[0] = merge(a,n[b].ch[0]);
            updateInfo(b);
            return b;
        }
    }

    static DRoot split(int now,int k) {
        DRoot result(0,0);
        if(now == 0) return result;
        if(k <= n[n[now].ch[0]].size) {
            result = split(n[now].ch[0],k);
            n[now].ch[0] = result.second;
            updateInfo(now);
            result.second = now;
        }else {
            result = split(n[now].ch[1],k - n[n[now].ch[0]].size - 1);
            n[now].ch[1] = result.first;
            updateInfo(now);
            result.first = now;
        }
        return result;
    }

    int lowerCount(int value) {
        int result = 0,now = root;
        while(now != 0) {
            if(n[now].value < value) {
                result += n[n[now].ch[0]].size + 1;
                now = n[now].ch[1];
            }else {
                now = n[now].ch[0];
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

    void print() {
        print(root);
        printf("\n");
    }

    void print(int now) {
        if(now == 0) return;
        print(n[now].ch[0]);
        printf("%d ",n[now].value);
        print(n[now].ch[1]);
    }

};

struct SegmentNode {
    int left,right,ch[2];
    Treap treap;

    void init(int left,int right) {
        this->left = left;
        this->right = right;
        this->ch[0] = 0;
        this->ch[1] = 0;
        this->treap = Treap();
    }

    bool isLeafNode() {
        return left == right;
    }
 } sn[MAX_SEGMENT_NODE_SIZE];

int segmentNodeSize = 0;

struct SegmentTree {
    int root;

    static int newNode(int left,int right) {
        sn[++segmentNodeSize].init(left,right);
        return segmentNodeSize;
    }

    SegmentTree(int size) {
        root = newNode(1,size);
        build(root);
    }

    void build(int now) {
        if(sn[now].isLeafNode()) return;
        int mid = (sn[now].left + sn[now].right) >> 1;
        sn[now].ch[0] = newNode(sn[now].left,mid);
        build(sn[now].ch[0]);
        sn[now].ch[1] = newNode(mid + 1,sn[now].right);
        build(sn[now].ch[1]);
    }

    void remove(int pos,int val) {
        remove(root,pos,val);
    }

    void remove(int now,int pos,int val) {
        sn[now].treap.remove(val);
        if(sn[now].isLeafNode()) {
            return;
        }
        int mid = (sn[now].left + sn[now].right) >> 1;
        if(pos <= mid) {
            remove(sn[now].ch[0],pos,val);
        }else {
            remove(sn[now].ch[1],pos,val);
        }
    }

    void insert(int pos,int val) {
        insert(root,pos,val);
    }

    void insert(int now,int pos,int val) {
        sn[now].treap.insert(val);
        if(sn[now].isLeafNode()) {
            return;
        }
        int mid = (sn[now].left + sn[now].right) >> 1;
        if(pos <= mid) {
            insert(sn[now].ch[0],pos,val);
        }else {
            insert(sn[now].ch[1],pos,val);
        }
    }

    int queryLessThan(int left,int right,int val) {
        return queryLessThan(root,left,right,val);
    }

    int queryLessThan(int now,int left,int right,int val) {
        if(sn[now].left == left && sn[now].right == right) {
            return sn[now].treap.lowerCount(val);
        }
        int mid = (sn[now].left + sn[now].right) >> 1;
        if(left <= mid) {
            if(right <= mid) {
                return queryLessThan(sn[now].ch[0],left,right,val);
            }else {
                return queryLessThan(sn[now].ch[0],left,mid,val) + queryLessThan(sn[now].ch[1],mid + 1,right,val);
            }
        }else {
            return queryLessThan(sn[now].ch[1],left,right,val);
        }
    }
};

set<int> colorsIndex[MAX_COLOR_RANGE];

int main() {
    for(int i = 1;i < MAX_COLOR_RANGE;i++) {
        colorsIndex[i].insert(0);
    }
    int N = read<int>(),M = read<int>(),*colors = new int[N + 1],*nowValues = new int[N + 1];
    SegmentTree stree(N);
    for(int i = 1;i <= N;i++) {
        int tmpValue = read<int>();
        int preValue = *(colorsIndex[tmpValue].rbegin());
        nowValues[i] = preValue;
        stree.insert(i,preValue);
        colorsIndex[tmpValue].insert(i);
        colors[i] = tmpValue;
    }
    char *buffer = new char[BUFFER_SIZE];
    while(M--) {
        scanf("%s",buffer);
        if(buffer[0] == 'Q') {
            int left = read<int>(),right = read<int>();
            printf("%d\n",stree.queryLessThan(left,right,left));
        }else {
            int pos = read<int>(),val = read<int>();
            if(colors[pos] == val) continue;
            {
                set<int> &tmpSet = colorsIndex[colors[pos]];
                set<int>::iterator it = tmpSet.lower_bound(pos),pre = it,suc = it;
                pre--; suc++;
                stree.remove(pos,nowValues[pos]);
                if(suc != tmpSet.end()) {
                    stree.remove(*suc,nowValues[*suc]);
                    stree.insert(*suc,*pre);
                    nowValues[*suc] = *pre;
                }
                tmpSet.erase(it);
            }
            {
                set<int> &tmpSet = colorsIndex[val];
                tmpSet.insert(pos);
                set<int>::iterator it = tmpSet.lower_bound(pos),pre = it,suc = it;
                pre--; suc++;
                stree.insert(pos,*pre);
                nowValues[pos] = *pre;
                if(suc != tmpSet.end()) {
                    stree.remove(*suc,nowValues[*suc]);
                    stree.insert(*suc,pos);
                    nowValues[*suc] = pos;
                }
            }
            colors[pos] = val;
        }
    }
    delete[] colors;
    delete[] nowValues;
    delete[] buffer;
    return 0;
}

