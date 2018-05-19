#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>
#include <unordered_map>

using namespace std;

const int MAXN = 10;
const int MAXM = 10;

typedef unsigned long long ull;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}
int n,m,endSign;
ull maxState;
ull startState;

int getSign(int x,int y) {
    return x * m + y;
}

//定义0是向上 1是向左 2是向下 3是向右

inline int toDirection(int sign,int dir) {
    switch(dir) {
        case 0: {
            if(sign < m) return -1;
            return sign - m;
        }
        case 1: {
            if(sign % m == 0) return -1;
            return sign - 1;
        }
        case 2: {
            if((sign / m) == n - 1) return -1;
            return sign + m;
        }
        case 3: {
            if((sign % m) == m - 1) return -1;
            return sign + 1;
        }
        default: {
            return -1;
        }
    }
}

inline bool contains(ull nowState,int now) {
    return (nowState >> now) & 1;
}

inline ull makeState(int now) {
    return 1ULL << now;
}

unordered_map<ull,int> memValue;

int dfs(int,ull);

//|  |
//|--|形
int dfs1(int now,ull nowState) {
    nowState |= makeState(now);
    int result = 0;
    int nowSign1 = toDirection(now,2);
    ull nowState1 = nowState;
    while(nowSign1 != -1 && !(contains(nowState1,nowSign1))) {
        nowState1 |= makeState(nowSign1);
        int nowSign2 = toDirection(nowSign1,3);
        ull nowState2 = nowState1;
        if(nowSign2 == -1 || (contains(nowState2,nowSign2))) {
            nowSign1 = toDirection(nowSign1,2);
            continue;
        }
        nowState2 |= makeState(nowSign2);
        nowSign2 = toDirection(nowSign2,3);
        while(nowSign2 != -1 && !(contains(nowState2,nowSign2))) {
            nowState2 |= makeState(nowSign2);
            int nowSign3 = toDirection(nowSign2,0);
            ull nowState3 = nowState2;
            while(nowSign3 != -1 && !(contains(nowState3,nowSign3))) {
                nowState3 |= makeState(nowSign3);
                result += dfs(now + 1,nowState3);
                nowSign3 = toDirection(nowSign3,0);
            }
            nowSign2 = toDirection(nowSign2,3);
        }
        nowSign1 = toDirection(nowSign1,2);
    }
    return result;
}

//--
//|
//--形
int dfs2(int now,ull nowState) {
    nowState |= makeState(now);
    int result = 0;
    int nowSign1 = toDirection(now,3);
    ull nowState1 = nowState;
    while(nowSign1 != -1 && !(contains(nowState1,nowSign1))) {
        nowState1 |= makeState(nowSign1);
        int nowSign2 = toDirection(now,2);
        ull nowState2 = nowState1;
        if(nowSign2 == -1 || contains(nowState2,nowSign2)) {
            nowSign1 = toDirection(nowSign1,3);
            continue;
        }
        nowState2 |= makeState(nowSign2);
        nowSign2 = toDirection(nowSign2,2);
        while(nowSign2 != -1 && !(contains(nowState2,nowSign2))) {
            nowState2 |= makeState(nowSign2);
            int nowSign3 = toDirection(nowSign2,3);
            ull nowState3 = nowState2;
            while(nowSign3 != -1 && !(contains(nowState3,nowSign3))) {
                nowState3 |= makeState(nowSign3);
                result += dfs(now + 1,nowState3);
                nowSign3 = toDirection(nowSign3,3);
            }
            nowSign2 = toDirection(nowSign2,2);
        }
        nowSign1 = toDirection(nowSign1,3);
    }
    return result;
}

//|--|
//|  |形
int dfs3(int now,ull nowState) {
    nowState |= makeState(now);
    int result = 0;
    int nowSign1 = toDirection(now,2);
    ull nowState1 = nowState;
    while(nowSign1 != -1 && !(contains(nowState1,nowSign1))) {
        nowState1 |= makeState(nowSign1);
        int nowSign2 = toDirection(now,3);
        ull nowState2 = nowState1;
        if(nowSign2 == -1 || contains(nowState2,nowSign2)) {
            nowSign1 = toDirection(nowSign1,2);
            continue;
        }
        nowState2 |= makeState(nowSign2);
        nowSign2 = toDirection(nowSign2,3);
        while(nowSign2 != -1 && !(contains(nowState2,nowSign2))) {
            nowState2 |= makeState(nowSign2);
            int nowSign3 = toDirection(nowSign2,2);
            ull nowState3 = nowState2;
            while(nowSign3 != -1 && !(contains(nowState3,nowSign3))) {
                nowState3 |= makeState(nowSign3);
                result += dfs(now + 1,nowState3);
                nowSign3 = toDirection(nowSign3,2);
            }
            nowSign2 = toDirection(nowSign2,3);
        }
        nowSign1 = toDirection(nowSign1,2);
    }
    return result;
}

//--|
//  |
//--|形
int dfs4(int now,ull nowState) {
    nowState |= makeState(now);
    int result = 0;
    int nowSign1 = toDirection(now,3);
    ull nowState1 = nowState;
    while(nowSign1 != -1 && !(contains(nowState1,nowSign1))) {
        nowState1 |= makeState(nowSign1);
        int nowSign2 = toDirection(nowSign1,2);
        ull nowState2 = nowState1;
        if(nowSign2 == -1 || (contains(nowState2,nowSign2))) {
            nowSign1 = toDirection(nowSign1,3);
            continue;
        }
        nowState2 |= makeState(nowSign2);
        nowSign2 = toDirection(nowSign2,2);
        while(nowSign2 != -1 && !(contains(nowState2,nowSign2))) {
            nowState2 |= makeState(nowSign2);
            int nowSign3 = toDirection(nowSign2,1);
            ull nowState3 = nowState2;
            while(nowSign3 != -1 && !(contains(nowState3,nowSign3))) {
                nowState3 |= makeState(nowSign3);
                result += dfs(now + 1,nowState3);
                nowSign3 = toDirection(nowSign3,1);
            }
            nowSign2 = toDirection(nowSign2,2);
        }
        nowSign1 = toDirection(nowSign1,3);
    }
    return result;
}

//|  |
//|--|形2
int dfs5(int now,ull nowState) {
    nowState |= makeState(now);
    int result = 0;
    int nowSign1 = toDirection(now,2);
    ull nowState1 = nowState;
    while(nowSign1 != -1 && !(contains(nowState1,nowSign1))) {
        nowState1 |= makeState(nowSign1);
        int nowSign2 = toDirection(nowSign1,1);
        ull nowState2 = nowState1;
        if(nowSign2 == -1 || (contains(nowState2,nowSign2))) {
            nowSign1 = toDirection(nowSign1,2);
            continue;
        }
        nowState2 |= makeState(nowSign2);
        nowSign2 = toDirection(nowSign2,1);
        while(nowSign2 != -1 && !(contains(nowState2,nowSign2))) {
            nowState2 |= makeState(nowSign2);
            int nowSign3 = toDirection(nowSign2,0);
            ull nowState3 = nowState2;
            while(nowSign3 != -1 && !(contains(nowState3,nowSign3))) {
                nowState3 |= makeState(nowSign3);
                result += dfs(now + 1,nowState3);
                nowSign3 = toDirection(nowSign3,0);
            }
            nowSign2 = toDirection(nowSign2,1);
        }
        nowSign1 = toDirection(nowSign1,2);
    }
    return result;
}

int dfs(int now,ull nowState) {
    if(memValue.count(nowState) != 0) return memValue[nowState];
    if(now == endSign) {
        return 1;
    }
    if((nowState >> now) & 1) return dfs(now + 1,nowState);
    int result = 0;
    int result1 = dfs1(now,nowState);
    int result2 = dfs2(now,nowState);
    int result3 = dfs3(now,nowState);
    int result4 = dfs4(now,nowState);
    int result5 = dfs5(now,nowState);
    result = result1 + result2 + result3 + result4 + result5;
    memValue[nowState] = result;
    return result;
}

int main() {
    n = read<int>(); m = read<int>();
    endSign = n * m;
    if(n == 8 && m == 8) {
        maxState = ULLONG_MAX;
    }else {
        maxState = (1ULL << (n * m)) - 1;
    }
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < m;j++) {
            int sign = getSign(i,j),tmpValue = read<int>();
            if(tmpValue == 1) {
                startState |= 1ULL << sign;
            }
        }
    }
    printf("%d\n",dfs(0,startState));
    return 0;
}
