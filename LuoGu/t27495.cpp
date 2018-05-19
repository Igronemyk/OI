#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <utility>
#include <unordered_map>

using namespace std;

const int MAXN = 15;
const int MAXM = 15;
const int MODDER = 2000003;
const int MAX_STATE = 300100;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

typedef pair<int,long long> Info;

vector<Info> nowState,prevState;

struct HashTable {
    struct Node {
        int next,to;
    } nodes[MAX_STATE];
    int tot,heads[MODDER];

    HashTable() : tot(0) {
        memset(heads,-1,sizeof(heads));
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

bool canVisit[MAXN][MAXM];

inline int getState(int now,int j) {
    return (now >> (j << 1)) & 3;
}

inline int makeState(int now,int j) {
    return now << (j << 1);
}

inline void insertState(int now,long long result) {
    int sign = stateSign.getSign(now);
    if(sign == nowState.size()) {
        nowState.push_back(make_pair(now,result));
    }else {
        nowState[sign].second += result;
    }
}

int main() {
    int n = read<int>(),m = read<int>();
    char *buffer = new char[MAXM];
    int endX = 0,endY = 0;
    for(int i = 1;i <= n;i++) {
        scanf("%s",buffer);
        for(int j = 1;j <= m;j++) {
            canVisit[i][j] = buffer[j - 1] == '.';
            if(canVisit[i][j]) {
                endX = i;
                endY = j;
            }
        }
    }
    long long result = 0;
    nowState.push_back(make_pair(0,1));
    for(int i = 1;i <= n;i++) {
        for(vector<Info>::iterator it = nowState.begin();it != nowState.end();it++) {
            if(getState(it->first,m) != 0) {
                return 0;
            }
            it->first <<= 2;
        }
        for(int j = 1;j <= m;j++) {
            prevState.swap(nowState);
            nowState.clear();
            stateSign.clear();
            for(vector<Info>::iterator it = prevState.begin();it != prevState.end();it++) {
                Info &tmpInfo = *it;
                int leftState = getState(tmpInfo.first,j - 1),rightState = getState(tmpInfo.first,j);
                if(!canVisit[i][j]) {
                    if(leftState == 0 && rightState == 0) {
                        insertState(tmpInfo.first,tmpInfo.second);
                    }
                }else if(leftState == 0 && rightState == 0) {
                    if(canVisit[i + 1][j] && canVisit[i][j + 1]) insertState(tmpInfo.first | makeState(1,j - 1) | makeState(2,j),tmpInfo.second);
                }else if(leftState > 0 && rightState == 0) {
                    if(canVisit[i + 1][j]) {
                        insertState(tmpInfo.first,tmpInfo.second);
                    }
                    if(canVisit[i][j + 1]) {
                        insertState(tmpInfo.first ^ makeState(leftState,j - 1) ^ makeState(leftState,j),tmpInfo.second);
                    }
                }else if(leftState == 0 && rightState > 0) {
                    if(canVisit[i][j + 1]) {
                        insertState(tmpInfo.first,tmpInfo.second);
                    }
                    if(canVisit[i + 1][j]) {
                        insertState(tmpInfo.first ^ makeState(rightState,j - 1) ^ makeState(rightState,j),tmpInfo.second);
                    }
                }else if(leftState == 2 && rightState == 1) {
                    insertState(tmpInfo.first ^ makeState(leftState,j - 1) ^ makeState(rightState,j),tmpInfo.second);
                }else if(leftState == 1 && rightState == 2) {
                    if(i == endX && j == endY) result += tmpInfo.second;
                }else if(leftState == 1 && rightState == 1) {
                    int nowCnt = 1;
                    for(int nowCheckSign = j + 1;nowCheckSign <= m;nowCheckSign++) {
                        int nowState = getState(tmpInfo.first,nowCheckSign);
                        if(nowState == 1) {
                            nowCnt++;
                        }else if(nowState == 2) {
                            nowCnt--;
                        }
                        if(nowCnt == 0) {
                            insertState((tmpInfo.first ^ makeState(leftState,j - 1) ^ makeState(rightState,j)) - makeState(1,nowCheckSign),tmpInfo.second);
                            break;
                        }
                    }
                }else if(leftState == 2 && rightState == 2) {
                    int nowCnt = 1;
                    for(int nowCheckSign = j - 2;nowCheckSign >= 0;nowCheckSign--) {
                        int nowState = getState(tmpInfo.first,nowCheckSign);
                        if(nowState == 1) {
                            nowCnt--;
                        }else if(nowState == 2) {
                            nowCnt++;
                        }
                        if(nowCnt == 0) {
                            insertState((tmpInfo.first ^ makeState(leftState,j - 1) ^ makeState(rightState,j)) + makeState(1,nowCheckSign),tmpInfo.second);
                            break;
                        }
                    }
                }
            }
        }
    }
    printf("%lld\n",result);
    return 0;
}
