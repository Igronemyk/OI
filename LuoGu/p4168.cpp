#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MAXN = 40010;
const int MAX_BLOCK_CNT = 210;
const int MAX_BLOCK_SIZE = 210;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int m,n,blockSize,blockCnt,blockL[MAX_BLOCK_CNT],blockR[MAX_BLOCK_CNT],belong[MAXN],sizes[MAX_BLOCK_CNT],results[MAX_BLOCK_CNT][MAX_BLOCK_CNT],cnt[MAX_BLOCK_CNT][MAXN],types[MAXN],tmp[MAX_BLOCK_SIZE * 2],tmpCnt[MAXN],sortedValues[MAXN],sortedSize;

void initInfo() {
    sort(sortedValues,sortedValues + n);
    sortedSize = unique(sortedValues,sortedValues + n) - sortedValues;
    for(int i = 0;i < n;i++) {
        types[i] = lower_bound(sortedValues,sortedValues + sortedSize,types[i]) - sortedValues;
    }
    for(int i = 0;i < blockCnt;i++) {
        memset(tmpCnt,0,sizeof(tmpCnt));
        int result = -1,nowBlock = i;
        for(int j = blockL[i];j < n;j++) {
            tmpCnt[types[j]]++;
            if(result == -1 || tmpCnt[result] < tmpCnt[types[j]] || (tmpCnt[result] == tmpCnt[types[j]] && types[j] < result)) {
                result = types[j];
            }
            if(j == blockR[nowBlock]) {
                results[i][nowBlock] = result;
                nowBlock++;
            }
        }
    }
    for(int i = 0;i < n;i++) {
        cnt[belong[i]][types[i]]++;
    }
    for(int i = 1;i < blockCnt;i++) {
        for(int j = 0;j < sortedSize;j++) {
            cnt[i][j] += cnt[i - 1][j];
        }
    }
}

int query(int left,int right) {
    int startBlock = belong[left],endBlock = belong[right];
    if(startBlock == endBlock) {
        for(int i = left;i <= right;i++) {
            tmpCnt[types[i]] = 0;
        }
        int result = -1;
        for(int i = left;i <= right;i++) {
            tmpCnt[types[i]]++;
            if(result == -1 || tmpCnt[result] < tmpCnt[types[i]] || (tmpCnt[result] == tmpCnt[types[i]] && types[i] < result)) {
                result = types[i];
            }
        }
        return result;
    }else {
        int tmpPos = 0,result = results[startBlock + 1][endBlock - 1],resultValue = cnt[endBlock - 1][result] - cnt[startBlock][result];
        for(int i = left;i <= blockR[startBlock];i++) {
            tmp[tmpPos++] = types[i];
        }
        for(int i = blockL[endBlock];i <= right;i++) {
            tmp[tmpPos++] = types[i];
        }
        for(int i = 0;i < tmpPos;i++) {
            tmpCnt[tmp[i]] = cnt[endBlock - 1][tmp[i]] - cnt[startBlock][tmp[i]];
        }
        for(int i = 0;i < tmpPos;i++) {
            tmpCnt[tmp[i]]++;
            if(result == -1 || tmpCnt[tmp[i]] > resultValue || (tmpCnt[tmp[i]] == resultValue && tmp[i] < result)) {
                result = tmp[i];
                resultValue = tmpCnt[tmp[i]];
            }
        }
        return result;
    }
}

int main() {
    n = read<int>();m = read<int>(),blockSize = static_cast<int>(sqrt(n));
    int lastBlock = -1;
    for(int i = 0;i < n;i++) {
        int nowBlock = i / blockSize;
        if(lastBlock != nowBlock) {
            if(lastBlock != -1) {
                blockR[lastBlock] = i - 1;
            }
            blockL[nowBlock] = i;
            lastBlock = nowBlock;
            blockCnt++;
        }
        types[i] = read<int>();
        sortedValues[i] = types[i];
        belong[i] = nowBlock;
    }
    blockR[lastBlock] = n - 1;
    for(int i = 0;i < blockCnt;i++) {
        sizes[i] = blockR[i] - blockL[i] + 1;
    }
    initInfo();
    int lastAns = 0;
    while(m--) {
        int l = (read<int>() + lastAns - 1) % n + 1,r = (read<int>() + lastAns - 1) % n + 1;
        if(l > r) {
            swap(l,r);
        }
        l--; r--;
        lastAns = sortedValues[query(l,r)];
        printf("%d\n",lastAns);
    }
    return 0;
}
