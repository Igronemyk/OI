#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int INF = 0x3f3f3f3f;

struct RMQ {
    int **valuesMax,**valuesMin,*nums;
    RMQ(int *nums,int n) {
        this->nums = nums;
        valuesMax = new int*[n];
        valuesMin = new int*[n];
        int range = log2(n) + 1;
        for(int i = 0;i < n;i++) {
            valuesMax[i] = new int[range];
            valuesMin[i] = new int[range];
            memset(valuesMax[i],0,sizeof(int) * range);
            memset(valuesMin[i],0,sizeof(int) * range);
        }
        for(int i = 0;i < n;i++) {
            valuesMax[i][0] = i;
            valuesMin[i][0] = i;
        }
        for(int j = 1;(1 << j) <= n;j++) {
            for(int i = 0;i + (1 << j) - 1 < n;i++) {
                if(nums[valuesMax[i][j - 1]] > nums[valuesMax[i + (1 << (j - 1))][j - 1]]) {
                    valuesMax[i][j] = valuesMax[i][j - 1];
                }else {
                    valuesMax[i][j] = valuesMax[i + (1 << (j - 1))][j - 1];
                }
                if(nums[valuesMin[i][j - 1]] < nums[valuesMin[i + (1 << (j - 1))][j - 1]]) {
                    valuesMin[i][j] = valuesMin[i][j - 1];
                }else {
                    valuesMin[i][j] = valuesMin[i + (1 << (j - 1))][j - 1];
                }
            }
        }
    }

    int getMax(int left,int right) {
        if(left > right) return 0;
        int k = log2(right - left + 1);
        return max(nums[valuesMax[left][k]],nums[valuesMax[right - (1 << k) + 1][k]]);
    }

    int getMin(int left,int right) {
        if(left > right) return INF;
        int k = log2(right - left + 1);
        return min(nums[valuesMin[left][k]],nums[valuesMin[right - (1 << k) + 1][k]]);
    }
};

int n,m,result = INF;

void dfs(RMQ **rmqs,int nowRow,int lastSelect,int *selectValue,int nowMax,int nowMin) {
    if(nowMax - nowMin > result) return;
    if(nowRow == n) {
        int otherMax = 0,otherMin = INF;
        for(int i = 0;i < n;i++) {
            int left = selectValue[i] + 1,right = m - 1;
            if(left > right) continue;
            otherMax = max(otherMax,rmqs[i]->getMax(left,right));
            otherMin = min(otherMin,rmqs[i]->getMin(left,right));
        }
        result = min(result,max(nowMax - nowMin,otherMax - otherMin));
        return;
    }
    for(int i = -1;i <= lastSelect;i++) {
        selectValue[nowRow] = i;
        dfs(rmqs,nowRow + 1,i,selectValue,max(nowMax,rmqs[nowRow]->getMax(0,i)),min(nowMin,rmqs[nowRow]->getMin(0,i)));
    }
}

void dfs1(RMQ **rmqs,int nowRow,int lastSelect,int *selectValue,int nowMax,int nowMin) {
    if(nowMax - nowMin > result) return;
    if(nowRow == n) {
        int otherMax = 0,otherMin = INF;
        for(int i = 0;i < n;i++) {
            int left = selectValue[i] + 1,right = m - 1;
            if(left > right) continue;
            otherMax = max(otherMax,rmqs[i]->getMax(left,right));
            otherMin = min(otherMin,rmqs[i]->getMin(left,right));
        }
        result = min(result,max(nowMax - nowMin,otherMax - otherMin));
        return;
    }
    for(int i = lastSelect;i < m;i++) {
        selectValue[nowRow] = i;
        dfs1(rmqs,nowRow + 1,i,selectValue,max(nowMax,rmqs[nowRow]->getMax(0,i)),min(nowMin,rmqs[nowRow]->getMin(0,i)));
    }
}

int main() {
    n = read<int>();m = read<int>();
    if(n == 1 && m == 1) {
        printf("0\n");
    }else {
        int **values = new int*[n];
        RMQ **rmqs = new RMQ*[n];
        for(int i = 0;i < n;i++) {
            values[i] = new int[m];
            for(int j = 0;j < m;j++) {
                values[i][j] = read<int>();
            }
            rmqs[i] = new RMQ(values[i],m);
        }
        int *selectValue = new int[n];
        dfs(rmqs,0,m - 1,selectValue,0,INF);
        dfs1(rmqs,0,-1,selectValue,0,INF);
        printf("%d\n",result);
    }
    return 0;
}
