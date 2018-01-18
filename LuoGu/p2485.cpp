#include <cstdio>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c >= '0' && c <= '9') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int quickPow(int a,int b,int p) {
    long long result = 1,base = a;
    while(b) {
        if(b & 1) result = (result * base) % p;
        base = (base * base) % p;
        b >>= 1;
    }
    return result;
}

int inv(int value,int p) {
    return quickPow(value % p,p - 2,p);
}

void BSGS(int y,int z,int p) {
    if(y == 0 && z == 0) {
        printf("1\n");
        return;
    }
    if(y == 0 && z != 0) {
        printf("Orz, I cannot find x!\n");
        return;
    }
    map<int,int> values;
    int m = static_cast<int>(ceil(sqrt(p)));
    long long nowValue;
    for(int j = 0;j <= m;j++) {
        if(j == 0) {
            nowValue = z % p;
            values[nowValue] = j;
            continue;
        }
        nowValue = (nowValue * y) % p;
        values[nowValue] = j;
    }
    nowValue = 1;
    long long addValue = quickPow(y,m,p);
    for(int i = 1;i <= m;i++) {
        nowValue = (nowValue * addValue) % p;
        if(values.count(nowValue) != 0) {
            long long result = (i * m) - values[nowValue];
            printf("%d\n",(result % p + p) % p);
            return;
        }
    }
    printf("Orz, I cannot find x!\n");
}

int main() {
    int T = read<int>(),K = read<int>();
    while(T--) {
        int y = read<int>(),z = read<int>(),p = read<int>();
        y %= p;
        switch(K) {
            case 1: {
                printf("%d\n",quickPow(y,z,p));
                break;
            }
            case 2: {
                z %= p;
                if(y == 0 && z != 0) {
                    printf("Orz, I cannot find x!\n");
                    break;
                }
                printf("%d\n",((z % p) * 1LL * inv(y,p)) % p);
                break;
            }
            case 3: {
                BSGS(y,z,p);
                break;
            }
        }
    }
    return 0;
}
