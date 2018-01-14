#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>
#include <functional>

using namespace std;

const int INF = 0x3f3f3f3f;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c- '0';c = getchar();}
    return result * f;
}

struct Info {
    int v,p;
    Info() : v(-1) , p(-1) { }
    Info(int v,int p) : v(v) , p(p) { }
};
int main() {
    int n = read<int>(),W = read<int>();
    Info *infos = new Info[n];
    int minV = INF;
    for(int i = 0;i < n;i++) {
        infos[i].v = read<int>();
        infos[i].p = read<int>();
        minV = min(minV,infos[i].v);
    }
    int *countItem = new int[4],**countValues = new int*[4];
    long long **indexValues = new long long*[4];
    fill(countItem,countItem + 4,0);
    for(int i = 0;i < 4;i++) {
        countValues[i] = new int[n];
        memset(countValues[i],0,sizeof(int) * n);
        indexValues[i] = new long long[n + 1];
        indexValues[i][0] = 0;
    }
    for(int i = 0;i < n;i++) {
        Info &tmpInfo = infos[i];
        if(tmpInfo.v == minV) {
            countValues[0][countItem[0]++] = tmpInfo.p;
        }else if(tmpInfo.v == minV + 1) {
            countValues[1][countItem[1]++] = tmpInfo.p;
        }else if(tmpInfo.v == minV + 2) {
            countValues[2][countItem[2]++] = tmpInfo.p;
        }else if(tmpInfo.v == minV + 3) {
            countValues[3][countItem[3]++] = tmpInfo.p;
        }
    }
    greater<int> great;
    for(int i = 0;i < 4;i++) {
        sort(countValues[i],countValues[i] + countItem[i],great);
    }
    for(int i = 0;i < 4;i++) {
        for(int j = 0;j < countItem[i];j++) {
            indexValues[i][j + 1] = indexValues[i][j] + countValues[i][j];
        }
    }
    long long result = 0;
    for(int i = 0;i <= countItem[0];i++) {
        for(int j = 0;j <= countItem[1];j++) {
            for(int k = 0;k <= countItem[2];k++) {
                for(int l = 0;l <= countItem[3];l++) {
                    long long tmpValue = i * 1LL * minV + j * 1LL * (minV + 1) + k * 1LL * (minV + 2) + l * 1LL * (minV + 3);
                    if(tmpValue > W) continue;
                    result = max(result,indexValues[0][i] + indexValues[1][j] + indexValues[2][k] + indexValues[3][l]);
                }
            }
        }
    }
    printf("%lld\n",result);
    return 0;
}
