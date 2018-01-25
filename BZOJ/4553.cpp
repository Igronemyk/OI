#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <utility>

using namespace std;

const int MAX_VAL_RANGE = 100010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Treap {

    struct Node {
        Node *ch[2];
        int value,data,maxData,priority,size;

        Node(int value,int data) : value(value) , data(data) , maxData(data) , priority(rand()) , size(1) {
            ch[0] = NULL;
            ch[1] = NULL;
        }
    };

    typedef pair<Node *,Node *> DRoot;

    Node *root;

    Treap() : root(NULL) { }

    static int getSize(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    static int getMaxData(Node *now) {
        if(now == NULL) return 0;
        return now->maxData;
    }

    static void updateInfo(Node *now) {
        now->size = getSize(now->ch[0]) + getSize(now->ch[1]) + 1;
        now->maxData = max(max(getMaxData(now->ch[0]),getMaxData(now->ch[1])),now->data);
    }

    static Node *merge(Node *a,Node *b) {
        if(a == NULL) return b;
        if(b == NULL) return a;
        if(a->priority > b->priority) {
            a->ch[1] = merge(a->ch[1],b);
            updateInfo(a);
            return a;
        }else {
            b->ch[0] = merge(a,b->ch[0]);
            updateInfo(b);
            return b;
        }
    }

    static DRoot split(Node *now,int k) {
        DRoot result(NULL,NULL);
        if(now == NULL) return result;
        if(k <= getSize(now->ch[0])) {
            result = split(now->ch[0],k);
            now->ch[0] = result.second;
            updateInfo(now);
            result.second = now;
        }else {
            result = split(now->ch[1],k - getSize(now->ch[0]) - 1);
            now->ch[1] = result.first;
            updateInfo(now);
            result.first = now;
        }
        return result;
    }

    int lowerCount(int value) {
        int result = 0;
        Node *now = root;
        while(now != NULL) {
            if(now->value < value) {
                result += getSize(now->ch[0]) + 1;
                now = now->ch[1];
            }else {
                now = now->ch[0];
            }
        }
        return result;
    }

    int upperCount(int value) {
        int result = 0;
        Node *now = root;
        while(now != NULL) {
            if(now->value <= value) {
                result += getSize(now->ch[0]) + 1;
                now = now->ch[1];
            }else {
                now = now->ch[0];
            }
        }
        return result;
    }

    void insert(int value,int data) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        Node *newNode = new Node(value,data);
        root = merge(tmp.first,merge(newNode,tmp.second));
    }

    int getMaxData(int value) {
        int cnt = upperCount(value);
        DRoot tmp = split(root,cnt);
        int result = getMaxData(tmp.first);
        root = merge(tmp.first,tmp.second);
        return result;
    }
};

struct SegmentTree {
    struct Node {
        Node *ch[2];
        int left,right;
        Treap *treap;

        Node(int left,int right) : left(left) , right(right) {
            ch[0] = NULL;
            ch[1] = NULL;
            treap = new Treap();
        }

        bool isLeafNode() {
            return left == right;
        }

    };

    Node *root;

    SegmentTree() {
        root = new Node(0,MAX_VAL_RANGE);
    }

    void insert(int pos,int val,int data) {
        insert(root,pos,val,data);
    }

    void insert(Node *now,int pos,int val,int data) {
        now->treap->insert(val,data);
        if(now->isLeafNode()) return;
        int mid = (now->left + now->right) >> 1;
        if(pos <= mid) {
            if(now->ch[0] == NULL) {
                now->ch[0] = new Node(now->left,mid);
            }
            insert(now->ch[0],pos,val,data);
        }else {
            if(now->ch[1] == NULL) {
                now->ch[1] = new Node(mid + 1,now->right);
            }
            insert(now->ch[1],pos,val,data);
        }
    }

    int query(int left,int right,int value) {
        return query(root,left,right,value);
    }

    int query(Node *now,int left,int right,int value) {
        if(now == NULL) return 0;
        if(now->left == left && now->right == right) {
            return now->treap->getMaxData(value);
        }
        int mid = (now->left + now->right) >> 1;
        if(left <= mid) {
            if(right <= mid) {
                return query(now->ch[0],left,right,value);
            }else {
                return max(query(now->ch[0],left,mid,value),query(now->ch[1],mid + 1,right,value));
            }
        }else {
            return query(now->ch[1],left,right,value);
        }
    }
};

int main() {
    int n = read<int>(),m = read<int>(),*values = new int[n + 1],*maxValues = new int[n + 1],*minValues = new int[n + 1],*dp = new int[n + 1];
    memset(dp,0,sizeof(int) * n);
    for(int i = 1;i <= n;i++) {
        values[i] = read<int>();
        maxValues[i] = values[i];
        minValues[i] = values[i];
    }
    while(m--) {
        int pos = read<int>(),tmpValue = read<int>();
        maxValues[pos] = max(maxValues[pos],tmpValue);
        minValues[pos] = min(minValues[pos],tmpValue);
    }
    SegmentTree stree;
    int result = 0;
    for(int i = 1;i <= n;i++) {
        dp[i] = stree.query(0,values[i],minValues[i]) + 1;
        result = max(result,dp[i]);
        stree.insert(maxValues[i],values[i],dp[i]);
    }
    printf("%d\n",result);
    return 0;
}
