#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

const int BUFFER_SIZE = 2;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

template<typename T>
struct BIT {
    T **values;
    int size;

    BIT(int size) : size(size) {
        values = new T*[size + 1];
        for(int i = 0;i <= size;i++) {
            values[i] = new T[size + 1];
            memset(values[i],0,sizeof(int) * (size + 1));
        }
    }

    T getSum(int x,int y) {
        T result = 0;
        while(x) {
            int pos = y;
            while(pos) {
                result += values[x][pos];
                pos -= lowbit(pos);
            }
            x -= lowbit(x);
        }
        return result;
    }

    void update(int x,int y,T val) {
        for(int i = x;i <= size;i += lowbit(i)) {
            for(int j = y;j <= size;j += lowbit(j)) {
                values[i][j] += val;
            }
        }
    }

    int lowbit(int val) {
        return val & -val;
    }

    ~BIT() {
        for(int i = 0;i <= size;i++) {
            delete[] values[i];
        }
        delete[] values;
    }
};

int main() {
    int T = read<int>();
    char *buffer = new char[BUFFER_SIZE];
    while(T--) {
        int N = read<int>(),T = read<int>();
        BIT<int> bitree(N + 1);
        while(T--) {
            scanf("%s",buffer);
            if(buffer[0] == 'C') {
                int x1 = read<int>(),y1 = read<int>(),x2 = read<int>(),y2 = read<int>();
                bitree.update(x1,y1,1);
                bitree.update(x1,y2 + 1,-1);
                bitree.update(x2 + 1,y1,-1);
                bitree.update(x2 + 1,y2 + 1,1);
            }else {
                int x = read<int>(),y = read<int>();
                printf("%d\n",bitree.getSum(x,y) % 2);
            }
        }
        printf("\n");
    }
    return 0;
}
