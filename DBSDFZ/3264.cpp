#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int BUFFER_SIZE = 1;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

template<typename T>
struct BIT {
    T *values;
    int size;


    BIT(int size) : size(size) {
        values = new T[size + 1];
        memset(values,0,sizeof(T) * (size + 1));
    }

    void update(int pos,T value) {
        for(int i = pos;i <= size;i += lowbit(i)) {
            values[i] += value;
        }
    }

    T getSum(int pos) {
        T result = 0;
        while(pos) {
            result += values[pos];
            pos -= lowbit(pos);
        }
        return result;
    }

    int lowbit(int value) {
        return value & -value;
    }
};

int main() {
    int N = read<int>(),*values = new int[N + 1];
    memset(values,0,sizeof(int) * (N + 1));
    BIT<int> bitree(N);
    for(int i = 1;i <= N;i++) {
        values[i] = read<int>();
        bitree.update(i,values[i]);
    }
    char *buffer = new char[BUFFER_SIZE + 1];
    int M = read<int>();
    while(M--) {
        scanf("%s",buffer);
        if(buffer[0] == 'C') {
            int pos = read<int>(),value = read<int>();
            bitree.update(pos,value - values[pos]);
            values[pos] = value;
        }else {
            int left = read<int>(),right = read<int>();
            printf("%d\n",bitree.getSum(right) - bitree.getSum(left - 1));
        }
    }
    return 0;
}
