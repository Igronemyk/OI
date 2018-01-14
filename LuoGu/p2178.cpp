#include <cstdio>
#include <cstring>
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f= 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int MAX_CHARSET_SIZE = 26;
const int BUFFER_SIZE = 1e6 + 1;
const int INF = 0x3f3f3f3f;

struct Info {
    int weight,i;
    bool operator < (const Info &otherInfo) const {
        return this->weight > otherInfo.weight;
    }
};

struct BCS {
    int *father,*treeSize,*firstMax,*secondMax,*firstMin,*secondMin;
    long long maxResult,countSize;
    BCS(int *values,int size) {
        father = new int[size];
        treeSize = new int[size];
        firstMax = new int[size];
        secondMax = new int[size];
        firstMin = new int[size];
        secondMin = new int[size];
        for(int i = 0;i < size;i++) {
            father[i] = i;
            treeSize[i] = 1;
            secondMax[i] = -INF;
        }
        memcpy(firstMax,values,sizeof(int) * size);
        memcpy(firstMin,values,sizeof(int) * size);
        memset(secondMin,INF,sizeof(int) * size);
        maxResult = LLONG_MIN;
        countSize = 0;
    }

    int getFather(int pos) {
        if(father[pos] == pos) return pos;
        father[pos] = getFather(father[pos]);
        return father[pos];
    }

    void merge(int u,int v) {
        int faU = getFather(u),faV = getFather(v);
        if(faU == faV) return;
        father[faU] = faV;
        updateInfo(faU,faV);
    }

    void updateInfo(int child,int father) {
        if(firstMax[child] > firstMax[father]) {
            int tmp = firstMax[father];
            firstMax[father] = firstMax[child];
            secondMax[father] = tmp;
        }else if(firstMax[child] > secondMax[father]) {
            secondMax[father] = firstMax[child];
        }
        if(secondMax[child] > firstMax[father]) {
            int tmp = firstMax[father];
            firstMax[father] = secondMax[child];
            secondMax[father] = tmp;
        }else if(secondMax[child] > secondMax[father]) {
            secondMax[father] = secondMax[child];
        }
        if(firstMin[child] < firstMin[father]) {
            int tmp = firstMin[father];
            firstMin[father] = firstMin[child];
            secondMin[father] = tmp;
        }else if(firstMin[child] < secondMin[father]) {
            secondMin[father] = firstMin[child];
        }
        if(secondMin[child] < firstMin[father]) {
            int tmp = firstMin[father];
            firstMin[father] = secondMin[child];
            secondMin[father] = tmp;
        }else if(secondMin[child] < secondMin[father]) {
            secondMin[father] = secondMin[child];
        }
        if(firstMin[father] * 1LL * secondMin[father] > maxResult) {
            maxResult = firstMin[father] * 1LL * secondMin[father];
        }
        if(firstMax[father] * 1LL * secondMax[father] > maxResult) {
            maxResult = firstMax[father] * 1LL * secondMax[father];
        }
        countSize -= treeSize[child] * 1LL * (treeSize[child] - 1) / 2;
        countSize -= treeSize[father] * 1LL * (treeSize[father] - 1) / 2;
        treeSize[father] += treeSize[child];
        countSize += treeSize[father] * 1LL * (treeSize[father] - 1) / 2;
    }
};

void buildSA(char *str,int length,int *sa,int *rank,int *height) {
    int nowRange = MAX_CHARSET_SIZE,*x = rank,*y = height,*cnt = new int[length];
    memset(cnt,0,sizeof(int) * (nowRange + 1));
    for(int i = 0;i < length;i++) {
        cnt[x[i] = str[i] - 'a']++;
    }
    for(int i = 1;i <= nowRange;i++) {
        cnt[i] += cnt[i - 1];
    }
    for(int i = 0;i < length;i++) {
        sa[--cnt[x[i]]] = i;
    }
    for(int nowLen = 1;nowLen <= length;nowLen <<= 1) {
        int tmpPos = 0;
        for(int i = length - nowLen;i < length;i++) {
            y[tmpPos++] = i;
        }
        for(int i = 0;i < length;i++) {
            if(sa[i] >= nowLen) {
                y[tmpPos++] = sa[i] - nowLen;
            }
        }
        memset(cnt,0,sizeof(int) * (nowRange + 1));
        for(int i = 0;i < length;i++) {
            cnt[x[i]]++;
        }
        for(int i = 1;i <= nowRange;i++) {
            cnt[i] += cnt[i - 1];
        }
        for(int i = length - 1;i >= 0;i--) {
            sa[--cnt[x[y[i]]]] = y[i];
        }
        memcpy(y,x,sizeof(int) * length);
        int tmpRank = 0;
        x[sa[0]] = 0;
        for(int i = 1;i < length;i++) {
            x[sa[i]] = x[sa[i - 1]];
            if(y[sa[i]] != y[sa[i - 1]] || (sa[i] + nowLen >= length && sa[i - 1] + nowLen < length) || (sa[i] + nowLen < length && sa[i - 1] + nowLen >= length) || y[sa[i] + nowLen] != y[sa[i - 1] + nowLen]) {
                x[sa[i]]++;
            }
        }
        nowRange = x[sa[length - 1]];
        if(nowRange >= length - 1) break;
    }
    for(int i = 0;i < length;i++) {
        rank[sa[i]] = i;
    }
    int tmpHeight = 0;
    for(int i = 0;i < length;i++) {
        if(rank[i] == 0) {
            height[rank[i]] = 0;
            tmpHeight = 0;
            continue;
        }
        if(tmpHeight > 0) {
            tmpHeight--;
        }
        int tmpPos = sa[rank[i] - 1];
        while(tmpPos + tmpHeight < length && i + tmpHeight < length && str[i + tmpHeight] == str[tmpPos + tmpHeight]) {
            tmpHeight++;
        }
        height[rank[i]] = tmpHeight;
    }
}

int main() {
    int n = read<int>();
    char *buffer = new char[BUFFER_SIZE];
    scanf("%s",buffer);
    int length = n;
    int *sa = new int[length],*rank = new int[length],*height = new int[length];
    buildSA(buffer,length,sa,rank,height);
    int *values = new int[n],*oldValues = new int[n];
    for(int i = 0;i < n;i++) {
        oldValues[i] = read<int>();
    }
    for(int i = 0;i < n;i++) {
        values[i] = oldValues[sa[i]];
    }
    BCS bcset(values,n);
    Info *infos = new Info[n];
    pair<long long,long long> *results = new pair<long long,long long>[n];
    for(int i = 0;i < n;i++) {
        infos[i].weight = height[i];
        infos[i].i = i;
        results[i].first = 0;
        results[i].second = 0;
    }
    sort(infos,infos + n);
    int lastValue = infos[0].weight;
    for(int i = 0;i < n;i++) {
        if(lastValue != infos[i].weight) {
            results[lastValue].first = bcset.countSize;
            results[lastValue].second = bcset.maxResult == LLONG_MIN ? 0 : bcset.maxResult;
        }
        if(infos[i].i != 0) {
            bcset.merge(infos[i].i,infos[i].i - 1);
        }
        lastValue = infos[i].weight;
    }
    results[lastValue].first = bcset.countSize;
    results[lastValue].second = bcset.maxResult == LLONG_MIN ? 0 : bcset.maxResult;
    lastValue--;
    for(int i = lastValue;i >= 0;i--) {
        results[i] = results[i + 1];
    }
    for(int i = 0;i < n;i++) {
        printf("%lld %lld\n",results[i].first,results[i].second);
    }
    return 0;
}
