#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 26;
const int MAX_STATE_SIZE = (1 << 10);
const int MAX_AC_NODE_SIZE = 110;
const int MAX_CHARSET_SIZE = 26;
const int FIRST_CHAR = 'a';
const int BUFFER_SIZE = 11;
const int MODDER = 20090717;

struct ACNode {
    int trans[MAX_CHARSET_SIZE],fail,status;
} an[MAX_AC_NODE_SIZE];

int acSize = 0;

struct ACAM {
    int root;

    static int newNode() {
        for(int i = 0;i < MAX_CHARSET_SIZE;i++) an[acSize].trans[i] = -1;
        an[acSize].fail = -1;
        an[acSize].status = 0;
        return acSize++;
    }

    ACAM() {
        root = newNode();
    }

    void insert(char *str,int status) {
        int now = root;
        for(int i = 0;str[i];i++) {
            int index = str[i] - FIRST_CHAR;
            if(an[now].trans[index] == -1) {
                an[now].trans[index] = newNode();
            }
            now = an[now].trans[index];
        }
        an[now].status |= status;
    }

    void build() {
        queue<int> que;
        for(int i = 0;i < MAX_CHARSET_SIZE;i++) {
            if(an[root].trans[i] == -1) {
                an[root].trans[i] = root;
            }else {
                an[an[root].trans[i]].fail = root;
                que.push(an[root].trans[i]);
            }
        }
        while(!que.empty()) {
            int tmpNode = que.front();
            que.pop();
            for(int i = 0;i < MAX_CHARSET_SIZE;i++) {
                if(an[tmpNode].trans[i] == -1) {
                    an[tmpNode].trans[i] = an[an[tmpNode].fail].trans[i];
                }else {
                    an[an[tmpNode].trans[i]].fail = an[an[tmpNode].fail].trans[i];
                    an[an[tmpNode].trans[i]].status |= an[an[an[tmpNode].trans[i]].fail].status;
                    que.push(an[tmpNode].trans[i]);
                }
            }
        }
    }
};

int dp[MAXN][MAX_AC_NODE_SIZE][MAX_STATE_SIZE];

int main() {
    int n,m,k;
    char *buffer = new char[BUFFER_SIZE];
    while(~scanf("%d%d%d",&n,&m,&k)) {
        if(n == 0 && m == 0 && k == 0) break;
        acSize = 0;
        ACAM acAutoMachine;
        for(int i = 0;i < m;i++) {
            scanf("%s",buffer);
            acAutoMachine.insert(buffer,(1 << i));
        }
        acAutoMachine.build();
        int maxState = (1 << m);
        for(int i = 0;i <= n;i++) {
            for(int j = 0;j < acSize;j++) {
                for(int k = 0;k < maxState;k++) {
                    dp[i][j][k] = 0;
                }
            }
        }
        dp[0][0][0] = 1;
        for(int i = 0;i < n;i++) {
            for(int j = 0;j < acSize;j++) {
                for(int k = 0;k < maxState;k++) {
                    if(dp[i][j][k] == 0) continue;
                    for(int l = 0;l < MAX_CHARSET_SIZE;l++) {
                        dp[i + 1][an[j].trans[l]][k | an[an[j].trans[l]].status] = (dp[i + 1][an[j].trans[l]][k | an[an[j].trans[l]].status] + dp[i][j][k]) % MODDER;
                    }
                }
            }
        }
        int result = 0;
        for(int i = 0;i < maxState;i++) {
            int countOne = 0;
            for(int j = 0;j < m;j++) {
                if((1 << j) & i) countOne++;
            }
            if(countOne < k) continue;
            for(int j = 0;j < acSize;j++) {
                result = (result + dp[n][j][i]) % MODDER;
            }
        }
        printf("%d\n",result);
    }
    return 0;
}
