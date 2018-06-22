#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 3000;
const int MAXM = 3000;

int n,m;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct BIT {
    int values[MAXN][MAXM];

    BIT() {
        memset(values,0,sizeof(values));
    }

    void update(int x,int y,int val) {
        for(int i = x;i <= n;i += lowbit(i)) {
            for(int j = y;j <= m;j += lowbit(j)) {
                values[i][j] += val;
            }
        }
    }

    int getValue(int x,int y) {
        int result = 0;
        for(int i = x;i > 0;i -= lowbit(i)) {
            for(int j = y;j > 0;j -= lowbit(j)) {
                result += values[i][j]; 
            }
        }
        return result;
    }

    int lowbit(int value) {
        return value & -value;
    }
} t1,t2,t3,t4;

void add(int x,int y,int val) {
    t1.update(x,y,val);
    t2.update(x,y,val * x);
    t3.update(x,y,val * y);
    t4.update(x,y,val * x * y);
}

int getResult(int x,int y) {
    int result = 0;
    result += t1.getValue(x,y) * (x * y + x + y + 1);
    result -= t2.getValue(x,y) * (y + 1);
    result -= t3.getValue(x,y) * (x + 1);
    result += t4.getValue(x,y);
    return result;
}

char buffer[10];

int main() {
    scanf("%s",buffer);
    n = read<int>();
    m = read<int>();
    while(~scanf("%s",buffer)) {
        if(buffer[0] == 'L') {
            int x1 = read<int>(),y1 = read<int>(),x2 = read<int>(),y2 = read<int>(),delta = read<int>();
            add(x1,y1,delta);
            add(x1,y2 + 1,-delta);
            add(x2 + 1,y1,-delta);
            add(x2 + 1,y2 + 1,delta);
        }else {
            int x1 = read<int>(),y1 = read<int>(),x2 = read<int>(),y2 = read<int>(),result = 0;
            result += getResult(x2,y2);
            result -= getResult(x1 - 1,y2);
            result -= getResult(x2,y1 - 1);
            result += getResult(x1 - 1,y1 - 1);
            printf("%d\n",result);
        }
    }
    return 0;
}
