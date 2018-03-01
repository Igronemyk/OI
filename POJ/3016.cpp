#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>

using namespace std;

const int MAX_TREAP_NODE_SIZE = 1010;
const int INF = 0x3f3f3f3f;
const int MAXN = 1010;
const int MAXK = 11;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct TreapNode {
    int ch[2],value,sum,priority,size;

    TreapNode() : value(0) , sum(0) , priority(0) , size(0) {
        ch[0] = 0;
        ch[1] = 0;
    }

    TreapNode(int value) : value(value) , sum(value) , priority(rand()) , size(1) {
        ch[0] = 0;
        ch[1] = 0;
    }
} tn[MAX_TREAP_NODE_SIZE];

int treapSize = 0;

struct Treap {
    int root;

    typedef pair<int,int> DRoot;

    Treap() : root(0) { }

    static int newNode(int value) {
        ++treapSize;
        tn[treapSize] = TreapNode(value);
        return treapSize;
    }

    static void updateInfo(int now) {
        tn[now].sum = tn[tn[now].ch[0]].sum + tn[tn[now].ch[1]].sum + tn[now].value;
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

    int getResult() {
        DRoot tmp1 = split(root,tn[root].size / 2),tmp2 = split(tmp1.second,1);
        int midValue = tn[tmp2.first].value;
        int result = tn[tmp1.first].size * midValue - tn[tmp1.first].sum + tn[tmp2.second].sum - tn[tmp2.second].size * midValue;
        root = merge(tmp1.first,merge(tmp2.first,tmp2.second));
        return result;
    }

};
void getCost(int n) {
    for(int i = 1;i <= n;i++) {
        Treap treap;
        for(int j = i;j <= n;j++) {
            treap.insert(tmpValue[j]);
            costs[i][j] = min(treap.getResult(),costs[i][j]);
        }
    }
}


int main() {
    srand(123456);
    int n,k;
    while(~scanf("%d%d",&n,&k)) {
        if(n == 0 && k == 0) break;
        memset(costs,INF,sizeof(costs));
        memset(dp,INF,sizeof(dp));
        for(int i = 1;i <= n;i++) {
            values[i] = read<int>();
        }
        memcpy(tmpValue + 1,values + 1,sizeof(int) * n);
        for(int i = 1;i <= n;i++) {
            tmpValue[i] -= i;
        }
        getCost(n);
        memcpy(tmpValue + 1,values + 1,sizeof(int) * n);
        for(int i = 1;i <= n;i++) {
            tmpValue[i] = -tmpValue[i] - i;
        }
        getCost(n);
        dp[0][0] = 0;
        for(int i = 1;i <= n;i++) {
            for(int j = 1;j <= k;j++) {
                for(int l = j - 1;l < i;l++) {
                    dp[i][j] = min(dp[i][j],dp[l][j - 1] + costs[l + 1][i]);
                }
            }
        }
        printf("%d\n",dp[n][k]);
    }
    return 0;
}
