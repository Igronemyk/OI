#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MODDER = 2000003;
const int ANS_MODDER = 20110520;
const int MAX_STATE = 3e6 + 10;
const int MAXN = 110;
const int MAXM = 110;

char buffer[MAXN][MAXM];

bool canVisit[MAXN][MAXM];

struct HashTable {
    struct Node {
        int next,to;
    } nodes[MAX_STATE];
    int tot,heads[MODDER];

    HashTable() {
        clear();
    }

    void addNode(int u,int v) {
        nodes[tot].next = heads[u];
        nodes[tot].to = v;
        heads[u] = tot++;
    }

    int getSign(int now) {
        int head = now % MODDER;
        for(int i = heads[head];i != -1;i = nodes[i].next) {
            if(nodes[i].to == now) {
                return i;
            }
        }
        addNode(head,now);
        return tot - 1;
    }

    void clear() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }
} stateSign;

struct Data {
    int state;
    long long result;

    Data() : state(0) , result(0) { }

    Data(int state,long long result) : state(state) , result(result) { }
};

Data *nowState,*prevState;
int nowCnt,prevCnt;

inline int getState(int now,int j) {
    return (now >> (j << 1)) & 3;
}

inline int makeState(int now,int j) {
    return now << (j << 1);
}

inline void insertState(int now,long long result) {
    int sign = stateSign.getSign(now);
    if(sign == nowCnt) {
        nowState[nowCnt++] = Data(now,result);
    }else {
        nowState[sign].result += result;
        nowState[sign].result %= ANS_MODDER;
    }
}

int main() {
    int N,M;
    scanf("%d%d",&N,&M);
    for(int i = 1;i <= N;i++) {
        scanf("%s",buffer[i] + 1);
    }
    int endX = 0,endY = 0;
    if(N < M) {
        for(int i = 1;i <= M;i++) {
            for(int j = 1;j <= N;j++) {
                canVisit[i][j] = buffer[j][i] == '_';
                if(canVisit[i][j]) {
                    endX = i;
                    endY = j;
                }
            }
        }
        swap(N,M);
    }else {
        for(int i = 1;i <= N;i++) {
            for(int j = 1;j <= M;j++) {
                canVisit[i][j] = buffer[i][j] == '_';
                if(canVisit[i][j]) {
                    endX = i;
                    endY = j;
                }
            }
        }
    }
    nowState = new Data[MAX_STATE];
    prevState = new Data[MAX_STATE];
    nowState[nowCnt++] = Data(0,1);
    long long result = 0;
    for(int i = 1;i <= N;i++) {
        for(int j = 0;j < nowCnt;j++) {
            nowState[j].state <<= 2;
        }
        for(int j = 1;j <= M;j++) {
            swap(nowState,prevState);
            swap(nowCnt,prevCnt);
            nowCnt = 0;
            stateSign.clear();
            for(int k = 0;k < prevCnt;k++) {
                Data &tmpData = prevState[k];
                int leftState = getState(tmpData.state,j - 1),rightState = getState(tmpData.state,j);
                if(!canVisit[i][j]) {
                    if(leftState == 0 && rightState == 0) {
                        insertState(tmpData.state,tmpData.result);
                    }
                }else if(leftState == 0 && rightState == 0) {
                    if(canVisit[i + 1][j] && canVisit[i][j + 1]) {
                        insertState(tmpData.state | makeState(1,j - 1) | makeState(1,j),tmpData.result);
                    }
                    if(canVisit[i][j + 1]) {
                        insertState(tmpData.state | makeState(2,j),tmpData.result);
                    }
                    if(canVisit[i + 1][j]) {
                        insertState(tmpData.state | makeState(2,j - 1),tmpData.result);
                    }
                }else if(leftState == 1 && rightState == 0) {
                    if(canVisit[i][j + 1]) {
                        insertState(tmpData.state ^ makeState(leftState,j - 1) ^ makeState(leftState,j),tmpData.result);
                    }
                    if(i == endX && j == endY) {
                        result = (result + tmpData.result) % ANS_MODDER;
                    }
                    insertState(tmpData.state ^ makeState(leftState,j - 1),tmpData.result);
                }else if(leftState == 2 && rightState == 0) {
                    if(canVisit[i + 1][j]) {
                        insertState(tmpData.state ^ makeState(leftState,j - 1) ^ makeState(1,j - 1),tmpData.result);
                    }
                    if(canVisit[i][j + 1]) {
                        insertState(tmpData.state ^ makeState(leftState,j - 1) ^ makeState(leftState,j),tmpData.result);
                    }
                }else if(leftState == 0 && rightState == 1) {
                    if(canVisit[i + 1][j]) {
                        insertState(tmpData.state ^ makeState(rightState,j) ^ makeState(rightState,j - 1),tmpData.result);
                    }
                    if(i == endX && j == endY) {
                        result = (result + tmpData.result) % ANS_MODDER;
                    }
                    insertState(tmpData.state ^ makeState(rightState,j),tmpData.result);
                }else if(leftState == 0 && rightState == 2) {
                    if(canVisit[i + 1][j]) {
                        insertState(tmpData.state ^ makeState(rightState,j) ^ makeState(rightState,j - 1),tmpData.result);
                    }
                    if(canVisit[i][j + 1]) {
                        insertState(tmpData.state ^ makeState(rightState,j) ^ makeState(1,j),tmpData.result);
                    }
                }else if(leftState == 2 && rightState == 2) {
                    if(i == endX && j == endY) {
                        result = (result + tmpData.result) % ANS_MODDER;
                    }
                    insertState(tmpData.state ^ makeState(leftState,j - 1) ^ makeState(rightState,j),tmpData.result);
                }
            }
        }
    }
    printf("%lld\n",result);
    return 0;
}
