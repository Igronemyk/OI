#include <cstdio>
#include <cstring>

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

    void update(int pos,T val) {
        for(int i = pos;i <= size;i += lowbit(i)) {
            values[i] += val;
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

    int lowbit(int val) {
        return val & -val;
    }
};


int main() {
    int N = read<int>(),M = read<int>(),*values = new int[N + 1];
    BIT<int> bitree(N);
    for(int i = 1;i <= N;i++) {
        values[i] = read<int>();
    }
    while(M--) {
        int opt = read<int>();
        if(opt == 1) {
            int x = read<int>(),y = read<int>(),k = read<int>();
            bitree.update(x,k);
            bitree.update(y + 1,-k);
        }else {
            int x = read<int>();
            printf("%d\n",values[x] + bitree.getSum(x));
        }
    }
    return 0;
}
