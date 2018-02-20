#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <utility>
#include <cstddef>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int n = read<int>(),*belong = new int[n],sqrtValue = sqrt(n),*f = new int[n],*g = new int[n],*jump = new int[n];
    for(int i = 0;i < n;i++) {
        belong[i] = i / sqrtValue;
        jump[i] = read<int>();
    }
    for(int i = n - 1;i >= 0;i--) {
        int father = min(i + jump[i],n);
        if(father == n || belong[father] != belong[i]) {
           f[i] = 1;
           g[i] = father;
        }else {
            f[i] = f[father] + 1;
            g[i] = g[father];
        }
    }
    int m = read<int>();
    while(m--) {
        int opt = read<int>(),pos = read<int>();
        switch(opt) {
            case 1: {
                int now = pos,result = 0;
                while(now != n) {
                    result += f[now];
                    now = g[now];
                }
                printf("%d\n",result);
                break;
            }
            case 2: {
                int lastBlock = belong[pos];
                jump[pos] = read<int>();
                for(int i = pos;i >= 0 && belong[i] == lastBlock;i--) {
                    int father = min(i + jump[i],n);
                    if(father == n || belong[father] != belong[i]) {
                        f[i] = 1;
                        g[i] = father;
                    }else {
                        f[i] = f[father] + 1;
                        g[i] = g[father];
                    }
                    lastBlock = belong[i];
                }
                break;
            }
        }
    }
    return 0;
}
