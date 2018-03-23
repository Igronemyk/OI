#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>
#include <cstddef>

using namespace std;

const int MAX_TREAP_NODE_SIZE = 100010;
const int BUFFER_SIZE = 1;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

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

    void updateInfo(int now) {
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
            if(tn[now].value < value) {
                result += tn[tn[now].ch[0]].size + 1;
                now = tn[now].ch[1];
            }else {
                now = tn[now].ch[0];
            }
        }
        return result;
    }

    int getKthMax(int k) {
        int now = root,result = 0;
        while(now != 0) {
            if(tn[tn[now].ch[1]].size < k) {
                k -= tn[tn[now].ch[1]].size + 1;
                now = tn[now].ch[0];
            }else if(tn[tn[now].ch[1]].size == k) {
                result = now;
                break;
            }else {
                now = tn[now].ch[1];
            }
        }
        return result;
    }

    int getKthMaxValue(int k) {
        k--;
        return tn[getKthMax(k)].value;
    }

    int getSize() {
        return tn[root].size;
    }

    void insert(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        int newNodeSign = newNode(value);
        root = merge(tmp.first,merge(newNodeSign,tmp.second));
    }

    int check(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        root = tmp.second;
        return cnt;
    }
};

int main() {
    int n = read<int>(),minValue = read<int>(),changeValue = 0;
    Treap treap;
    char *buffer = new char[BUFFER_SIZE + 1];
    int cntLeave = 0;
    while(n--) {
        scanf("%s",buffer);
        int k = read<int>();
        switch(buffer[0]) {
            case 'I': {
                if(k < minValue) {
                    break;
                }
                treap.insert(k - changeValue);
                break;
            }
            case 'A': {
                changeValue += k;
                cntLeave += treap.check(minValue - changeValue);
                break;
            }
            case 'S': {
                changeValue -= k;
                cntLeave += treap.check(minValue - changeValue);
                break;
            }
            case 'F': {
                if(treap.getSize() < k) {
                    printf("%d\n",-1);
                }else {
                    printf("%d\n",treap.getKthMaxValue(k) + changeValue);
                }
                break;
            }
        }
    }
    printf("%d\n",cntLeave);
    return 0;
}
