#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct ST {
    int **values;
    ST(int *val,int length) {
        values = new int*[length];
        int calLen = myLog2(length);
        for(int i = 0;i < length;i++) {
            values[i] = new int[calLen + 1];
            values[i][0] = val[i];
        }
        for(int j = 1;j <= calLen;j++) {
            for(int i = 0;i + (1 << j) - 1 < length;i++) {
                values[i][j] = max(values[i][j - 1],values[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int left,int right) {
        if(left > right) return -1;
        int logVal = myLog2(right - left + 1);
        return max(values[left][logVal],values[right - (1 << logVal) + 1][logVal]);
    }

    int myLog2(int val) {
        return static_cast<int>(log(static_cast<double>(val)) / log(2.0));
    }
};

int main() {
    int N = read<int>(),M = read<int>(),*values = new int[N];
    for(int i = 0;i < N;i++) values[i] = read<int>();
    ST st(values,N);
    while(M--) {
        int left = read<int>(),right = read<int>();
        left--; right--;
        printf("%d\n",st.query(left,right));
    }
    return 0;
}
