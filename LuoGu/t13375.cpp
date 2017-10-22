#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MODDER = 19260817;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int n = read<int>(),m = read<int>();
    int *dis = new int[n],*index = new int[n + 1];
    dis[0] = 0;
    index[0] = 0;
    index[1] = 0;
    for(int i = 1;i < n;i++) {
        dis[i] = read<int>();
        dis[i] %= MODDER;
        index[i + 1] = (index[i] + dis[i]) % MODDER;
    }
    int *weight = new int[n],*weightIndex = new int[n + 1];
    long long *addWeightIndex = new long long[n + 1];
    weightIndex[0] = 0;
    addWeightIndex[0] = 0;
    for(int i = 0;i < n;i++) {
        weight[i] = read<int>();
        weight[i] %= MODDER;
        weightIndex[i + 1] = (weightIndex[i] + weight[i]) % MODDER;
        addWeightIndex[i + 1] = (addWeightIndex[i] + weight[i] * 1LL * index[i + 1]) % MODDER;
    }
    while(m--) {
        int x = read<int>(),l = read<int>(),r = read<int>();
        if(x <= l) {
            long long nowAddWeight = addWeightIndex[r] - addWeightIndex[l - 1];
            if(nowAddWeight < 0) nowAddWeight += MODDER;
            int nowWeight = weightIndex[r] - weightIndex[l - 1];
            if(nowWeight < 0) nowWeight += MODDER;
            int result = nowAddWeight - (nowWeight * 1LL * index[x]) % MODDER;
            if(result < 0) result += MODDER;
            printf("%d\n",result % MODDER);
        }else if(x >= r) {
            long long nowAddWeight = addWeightIndex[r] - addWeightIndex[l - 1];
            if(nowAddWeight < 0) nowAddWeight += MODDER;
            int nowWeight = weightIndex[r] - weightIndex[l - 1];
            if(nowWeight < 0) nowWeight += MODDER;
            int result = (nowWeight * 1LL * index[x]) % MODDER - nowAddWeight;
            if(result < 0) result += MODDER;
            printf("%d\n",result % MODDER);
        }else if(x > l && x < r) {
            int left1 = l,right1 = x - 1,left2 = x + 1,right2 = r;
            long long nowAddWeight1 = addWeightIndex[right1] - addWeightIndex[left1 - 1],nowAddWeight2 = addWeightIndex[right2] - addWeightIndex[left2 - 1];
            if(nowAddWeight1 < 0) nowAddWeight1 += MODDER;
            if(nowAddWeight2 < 0) nowAddWeight2 += MODDER;
            int nowWeight1 = weightIndex[right1] - weightIndex[left1 - 1],nowWeight2 = weightIndex[right2] - weightIndex[left2 - 1];
            if(nowWeight1 < 0) nowWeight1 += MODDER;
            if(nowWeight2 < 0) nowWeight2 += MODDER;
            int result1 = (nowWeight1 * 1LL * index[x]) % MODDER - nowAddWeight1,result2 = nowAddWeight2 - (nowWeight2 * 1LL * index[x]) % MODDER;
            if(result1 < 0) result1 += MODDER;
            if(result2 < 0) result2 += MODDER;
            printf("%d\n",(result1 + result2) % MODDER);
        }else {
            printf("Vaild Data!\n");
        }
    }

    return 0;
}
