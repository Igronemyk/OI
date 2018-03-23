#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_VAL_RANGE = 5e4;

int valueLog2[MAX_VAL_RANGE + 1];

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct ST {
    int **minValues,**maxValues;

    ST(int *values,int length) {
        int calLen = valueLog2[length];
        minValues = new int*[length];
        maxValues = new int*[length];
        for(int i = 0;i < length;i++) {
            minValues[i] = new int[calLen + 1];
            maxValues[i] = new int[calLen + 1];
            minValues[i][0] = values[i];
            maxValues[i][0] = values[i];
        }
        for(int j = 1;j <= calLen;j++) {
            for(int i = 0;i + (1 << j) - 1 < length;i++) {
                minValues[i][j] = min(minValues[i][j - 1],minValues[i + (1 << (j - 1))][j - 1]);
                maxValues[i][j] = max(maxValues[i][j - 1],maxValues[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int getValue(int left,int right) {
        int length = right - left + 1,calLen = valueLog2[length];
        return max(maxValues[left][calLen],maxValues[right - (1 << calLen) + 1][calLen]) - min(minValues[left][calLen],minValues[right - (1 << calLen) + 1][calLen]);
    }
};

void initLog2() {
    for(int i = 2;i <= MAX_VAL_RANGE;i++) {
        valueLog2[i] = valueLog2[i >> 1] + 1;
    }
}

int main() {
    initLog2();
    int N = read<int>(),Q = read<int>(),*values = new int[N];
    for(int i = 0;i < N;i++) {
        values[i] = read<int>();
    }
    ST st(values,N);
    while(Q--) {
        int left = read<int>(),right = read<int>();
        left--; right--;
        printf("%d\n",st.getValue(left,right));
    }
    return 0;
}
