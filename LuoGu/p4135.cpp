#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 100010;
const int MAX_BLOCK_CNT = 330;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int n,c,m,values[MAXN],l[MAX_BLOCK_CNT],r[MAX_BLOCK_CNT],belong[MAXN],sizes[MAX_BLOCK_CNT],realBlockCnt,cnts[MAX_BLOCK_CNT][MAXN],tmpCnt[MAXN],ans[MAX_BLOCK_CNT][MAX_BLOCK_CNT];

int main() {
    n = read<int>();
    c = read<int>();
    m = read<int>();

    return 0;
}
