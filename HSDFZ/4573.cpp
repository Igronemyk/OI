#include <cstdio>

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int N = read<int>(),K = read<int>();
    long long *values = new long long[N];
    for(int i = 0;i < N;i++) {
        values[i] = read<long long>();
    }
    for(int i = 0;i < N;i++) {
        int leftPos = i - 1,rightPos = i + 1,nowPos = -1;
        for(int j = 0;j < K;j++) {
            if(leftPos < 0) {
                nowPos = rightPos;
                rightPos++;
            }else if(rightPos >= N) {
                nowPos = leftPos;
                leftPos--;
            }else {
                if(values[i] - values[leftPos] < values[rightPos] - values[i]) {
                    nowPos = leftPos;
                    leftPos--;
                }else if(values[i] - values[leftPos] > values[rightPos] - values[i]){
                    nowPos = rightPos;
                    rightPos++;
                }else {
                    if(j != K - 1) {
                        nowPos = rightPos;
                        rightPos++;
                    }else {
                        nowPos = leftPos;
                        leftPos--;
                    }
                }
            }
        }
        printf("%lld",values[nowPos]);
        if(i != N - 1) printf(" ");
    }
    return 0;
}
