#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>

using namespace std;

const int MAX_SPLAY_NODE_SIZE = 1000010;
const int MAX_SEGMENT_NODE_SIZE = 100010;
const int MAXN = 50010;
const int BUFFER_SIZE = 2;
const int MAX_VAL_RANGE = 1e9;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct SplayNode {
    int father,ch[2];
    int value,cnt,size;

    SplayNode() : father(0) , value(0) , cnt(0) , size(0) {
        ch[0] = 0;
        ch[1] = 0;
    }

    void init(int father,int value) {
        this->father = father;
        this->value = value;
        this->cnt = 1;
        this->size = 1;
        this->ch[0] = 0;
        this->ch[1] = 0;
    }

} n[MAX_SPLAY_NODE_SIZE];

int size = 0,sSize = 0;

struct Splay {
    int root;

    Splay() : root(0) { }

    int newNode(int father,int value) {
        n[++size].init(father,value);
        return size;
    }

    void updateInfo(int now) {
        if(now == 0) return;
        n[now].size = n[n[now].ch[0]].size + n[n[now].ch[1]].size + n[now].cnt;
    }

    void rotate(int now) {
        int father = n[now].father,anc = n[father].father;
        if(anc != 0) {
            n[anc].ch[n[anc].ch[1] == father] = now;
        }
        int direction = n[father].ch[0] == now;
        n[now].father = anc;
        n[father].father = now;
        n[father].ch[!direction] = n[now].ch[direction];
        n[now].ch[direction] = father;
        if(n[father].ch[!direction] != 0) {
            n[n[father].ch[!direction]].father = father;
        }
        updateInfo(father);
        updateInfo(now);
        if(n[now].father == 0) {
            root = now;
        }
    }

    void splay(int now) {
        splay(now,0);
    }

    void splay(int now,int dist) {
        if(now == 0 || now == dist) return;
        while(n[now].father != dist) {
            int father = n[now].father,anc = n[father].father;
            if(anc != dist) {
                if((n[anc].ch[0] == father) ^ (n[father].ch[0] == now)) {
                    rotate(now);
                }else {
                    rotate(father);
                }
            }
            rotate(now);
        }
    }

    int find(int value) {
        int now = root,prev = 0;
        while(now != 0) {
            prev = now;
            if(n[now].value > value) {
                now = n[now].ch[0];
            }else if(n[now].value < value) {
                now = n[now].ch[1];
            }else {
                break;
            }
        }
        splay(prev);
        return now;
    }

    int searchMin(int now) {
        int father = n[now].father;
        while(n[now].ch[0] != 0) {
            now = n[now].ch[0];
        }
        splay(now,father);
        return now;
    }

    void insert(int value) {
        if(root == 0) {
            root = newNode(0,value);
            return;
        }
        int now = root,result = 0;
        while(now != 0) {
            if(n[now].value > value) {
                if(n[now].ch[0] != 0) {
                    now = n[now].ch[0];
                }else {
                    result = newNode(now,value);
                    n[now].ch[0] = result;
                    break;
                }
            }else if(n[now].value < value) {
                if(n[now].ch[1] != 0) {
                    now = n[now].ch[1];
                }else {
                    result = newNode(now,value);
                    n[now].ch[1] = result;
                    break;
                }
            }else {
                n[now].cnt++;
                updateInfo(now);
                result = now;
                break;
            }
        }
        splay(result);
    }

    void remove(int value) {
        if(find(value) == 0) return;
        if(n[root].cnt > 1) {
            n[root].cnt--;
            updateInfo(root);
            return;
        }
        int lc = n[root].ch[0],rc = n[root].ch[1];
        if(lc == 0 && rc == 0) {
            root = 0;
            return;
        }
        if(lc != 0 && rc == 0) {
            root = lc;
            n[root].father = 0;
            return;
        }
        if(lc == 0 && rc != 0) {
            root = rc;
            n[root].father = 0;
            return;
        }
        int newNode = searchMin(rc);
        n[newNode].ch[0] = n[root].ch[0];
        n[newNode].father = 0;
        n[n[newNode].ch[0]].father = newNode;
        updateInfo(newNode);
        root = newNode;
    }

    int lowerCount(int value) {
        if(root == 0) return 0;
        find(value);
        if(n[root].value >= value) {
            return n[n[root].ch[0]].size;
        }else {
            return n[n[root].ch[0]].size + n[root].cnt;
        }
    }

};

struct SegmentNode {
    int left,right;
    int leftChild,rightChild;

    Splay splay;

    void init(int left,int right) {
        this->left = left;
        this->right = right;
        this->leftChild = 0;
        this->rightChild = 0;
        this->splay = Splay();
    }

    bool isLeafNode() {
        return left == right;
    }

} sn[MAX_SEGMENT_NODE_SIZE];

struct SegmentTree {
    int root;

    int newNode(int left,int right) {
        sn[++sSize].init(left,right);
        return sSize;
    }

    SegmentTree(int n) {
        root = newNode(0,n - 1);
        build(root);
    }

    void build(int now) {
        if(sn[now].isLeafNode()) return;
        int mid = (sn[now].left + sn[now].right) >> 1;
        sn[now].leftChild = newNode(sn[now].left,mid);
        build(sn[now].leftChild);
        sn[now].rightChild = newNode(mid + 1,sn[now].right);
        build(sn[now].rightChild);
    }

    void insert(int pos,int val) {
        insert(root,pos,val);
    }

    void insert(int now,int pos,int val) {
        sn[now].splay.insert(val);
        if(sn[now].isLeafNode()) {
            return;
        }
        int mid = (sn[now].left + sn[now].right) >> 1;
        if(pos <= mid) {
            insert(sn[now].leftChild,pos,val);
        }else {
            insert(sn[now].rightChild,pos,val);
        }
    }

    void remove(int pos,int val) {
        remove(root,pos,val);
    }

    void remove(int now,int pos,int val) {
        sn[now].splay.remove(val);
        if(sn[now].isLeafNode()) {
            return;
        }
        int mid = (sn[now].left + sn[now].right) >> 1;
        if(pos <= mid) {
            remove(sn[now].leftChild,pos,val);
        }else {
            remove(sn[now].rightChild,pos,val);
        }
    }

    int queryLessThan(int left,int right,int val) {
        return queryLessThan(root,left,right,val);
    }

    int queryLessThan(int now,int left,int right,int val) {
        if(sn[now].left == left && sn[now].right == right) {
            return sn[now].splay.lowerCount(val);
        }
        int mid = (sn[now].left + sn[now].right) >> 1;
        if(left <= mid) {
            if(right <= mid) {
                return queryLessThan(sn[now].leftChild,left,right,val);
            }else {
                return queryLessThan(sn[now].leftChild,left,mid,val) + queryLessThan(sn[now].rightChild,mid + 1,right,val);
            }
        }else {
            return queryLessThan(sn[now].rightChild,left,right,val);
        }
    }

};

int values[MAXN];
char buffer[BUFFER_SIZE];

int main() {
    int T = read<int>();
    while(T--) {
        size = 0;
        sSize = 0;
        int N = read<int>(),M = read<int>();
        SegmentTree stree(N);
        for(int i = 0;i < N;i++) {
            values[i] = read<int>();
            stree.insert(i,values[i]);
        }
        while(M--) {
            scanf("%s",buffer);
            switch(buffer[0]) {
                case 'Q': {
                    int left = read<int>(),right = read<int>(),rank = read<int>();
                    left--; right--;
                    int result = 0,begin = 0,end = MAX_VAL_RANGE;
                    while(begin <= end) {
                        int mid = (begin + end) >> 1,checkValue = stree.queryLessThan(left,right,mid);
                        if(checkValue <= rank - 1) {
                            result = mid;
                            begin = mid + 1;
                        }else {
                            end = mid - 1;
                        }
                    }
                    printf("%d\n",result);
                    break;
                }
                case 'C': {
                    int pos = read<int>(),value = read<int>();
                    pos--;
                    stree.remove(pos,values[pos]);
                    stree.insert(pos,value);
                    values[pos] = value;
                    break;
                }
            }
        }
    }
    return 0;
}
