#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <queue>


using namespace std;

const int MAX_CHARSET_SIZE = 62;
const int MAX_NODE_SIZE = 410;
const int MAX_ROUND_SIZE = 110;
const int BUFFER_SIZE = 21;

int getIndex(char c) {
    if(c >= 'a' && c <= 'z') {
        return c - 'a';
    }
    if(c >= 'A' && c <= 'Z') {
        return c - 'A' + 26;
    }
    if(c >= '0' && c <= '9') {
        return c - '0' + 52;
    }
}

struct Node {
    int childs[MAX_CHARSET_SIZE],fail;
    bool isEnd;

    void clear() {
        memset(childs,0,sizeof(int) * MAX_CHARSET_SIZE);
        fail = 0;
        isEnd = false;
    }

    bool hasChild(int index) {
        return childs[index] != 0;
    }

} nodes[MAX_NODE_SIZE];

double dp[MAX_ROUND_SIZE][MAX_NODE_SIZE];

int tot;

int newNode() {
    nodes[tot].clear();
    return tot++;
}

void insert(char *str) {
    int now = 1;
    for(int i = 0;str[i];i++) {
        int index = getIndex(str[i]);
        if(!nodes[now].hasChild(index)) {
            nodes[now].childs[index] = newNode();
        }
        now = nodes[now].childs[index];
    }
    nodes[now].isEnd = true;
}

void getFail() {
    queue<int> que;
    nodes[1].fail = 1;
    for(int i = 0;i < MAX_CHARSET_SIZE;i++) {
        if(nodes[1].hasChild(i)) {
            nodes[nodes[1].childs[i]].fail = 1;
            que.push(nodes[1].childs[i]);
        }else {
            nodes[1].childs[i] = 1;
        }
    }
    while(!que.empty()) {
        int tmpNode = que.front();
        que.pop();
        for(int i = 0;i < MAX_CHARSET_SIZE;i++) {
            if(nodes[tmpNode].hasChild(i)) {
                nodes[nodes[tmpNode].childs[i]].fail = nodes[nodes[tmpNode].fail].childs[i];
                if(nodes[nodes[nodes[tmpNode].childs[i]].fail].isEnd) {
                    nodes[nodes[tmpNode].childs[i]].isEnd = true;
                }
                que.push(nodes[tmpNode].childs[i]);
            }else {
                nodes[tmpNode].childs[i] = nodes[nodes[tmpNode].fail].childs[i];
            }
        }
    }
}

int main() {
    char *buffer = new char[BUFFER_SIZE];
    int T;
    scanf("%d",&T);
    for(int nowCase = 1;nowCase <= T;nowCase++) {
        tot = 0;
        memset(dp,0,sizeof(dp));
        newNode();
        newNode();
        int K;
        scanf("%d",&K);
        for(int i = 0;i < K;i++) {
            scanf("%s",buffer);
            insert(buffer);
        }
        int N;
        scanf("%d",&N);
        pair<int,double> *trans = new pair<int,double>[N];
        for(int i = 0;i < N;i++) {
            scanf("%s",buffer);
            trans[i].first = getIndex(buffer[0]);
            double p;
            scanf("%lf",&p);
            trans[i].second = p;
        }
        getFail();
        int L;
        scanf("%d",&L);
        dp[0][1] = 1;
        for(int i = 0;i < L;i++) {
            for(int j = 1;j < tot;j++) {
                if(nodes[j].isEnd) continue;
                for(int k = 0;k < N;k++) {
                    pair<int,double> &tmpTrans = trans[k];
                    dp[i + 1][nodes[j].childs[tmpTrans.first]] += dp[i][j] * tmpTrans.second;
                }
            }
        }
        double countResult = 0;
        for(int i = 1;i < tot;i++) {
            if(!nodes[i].isEnd) {
                countResult += dp[L][i];
            }
        }
        printf("Case #%d: %.6lf\n",nowCase,countResult);
    }
    return 0;
}
