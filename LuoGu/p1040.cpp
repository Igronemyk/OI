#include <cstdio>
#include <cstring>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

long long getValue(int left,int right,long long **dp) {
    if(right < left) {
        return 1;
    }
    return dp[left][right];
}

void printTree(int left,int right,int **root) {
    if(right < left) {
        return;
    }
    printf("%d ",root[left][right] + 1);
    printTree(left,root[left][right] - 1,root);
    printTree(root[left][right] + 1,right,root);
}

int main() {
    int n = read<int>();
    long long **dp = new long long*[n];
    int **root = new int*[n];
    for(int i = 0;i < n;i++) {
        dp[i] = new long long[n];
        memset(dp[i],0,sizeof(long long) * n);
        dp[i][i] = read<int>();
        root[i] = new int[n];
        memset(root[i],-1,sizeof(int) * n);
        root[i][i] = i;
    }
    for(int length = 2;length <= n;length++) {
        for(int startPos = 0;startPos + length - 1< n;startPos++) {
            int endPos = startPos + length - 1;
            for(int rootPos = startPos;rootPos <= endPos;rootPos++) {
                long long tmpCalValue = getValue(startPos,rootPos - 1,dp) * getValue(rootPos + 1,endPos,dp) + dp[rootPos][rootPos];
                if(tmpCalValue > dp[startPos][endPos]) {
                    dp[startPos][endPos] = tmpCalValue;
                    root[startPos][endPos] = rootPos;
                }
            }
        }
    }
    printf("%lld\n",dp[0][n - 1]);
    printTree(0,n - 1,root);
    printf("\n");
    return 0;
}
