#include <cstdio>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

bool visit[1000];

int main() {
    int n = read<int>(),**nums = new int*[n];
    for(int i = 0;i < n;i++) {
        nums[i] = new int[6];
        for(int j = 0;j < 6;j++) {
            nums[i][j] = read<int>();
        }
    }
    for(int i = 0;i < n;i++) {
        for(int iIndex = 0;iIndex < 6;iIndex++) {
            int tmpValueI = nums[i][iIndex];
            visit[tmpValueI] = true;
            for(int j = i + 1;j < n;j++) {
                for(int jIndex = 0;jIndex < 6;jIndex++) {
                    int tmpValueJ = nums[j][jIndex];
                    visit[tmpValueJ * 10 + tmpValueI] = true;
                    visit[tmpValueI * 10 + tmpValueJ] = true;
                    for(int k = j + 1;k < n;k++) {
                        for(int kIndex = 0;kIndex < 6;kIndex++) {
                            int tmpValueK = nums[k][kIndex];
                            visit[tmpValueK * 100 + tmpValueJ * 10 + tmpValueI] = true;
                            visit[tmpValueK * 100 + tmpValueI * 10 + tmpValueJ] = true;
                            visit[tmpValueI * 100 + tmpValueK * 10 + tmpValueJ] = true;
                            visit[tmpValueI * 100 + tmpValueJ * 10 + tmpValueK] = true;
                            visit[tmpValueJ * 100 + tmpValueI * 10 + tmpValueK] = true;
                            visit[tmpValueJ * 100 + tmpValueK * 10 + tmpValueI] = true;
                        }
                    }
                }
            }
        }
    }
    for(int i = 1;i < 1000;i++) {
        if(!visit[i]) {
            printf("%d\n",i - 1);
            return 0;
        }
    }
    return 0;
}
