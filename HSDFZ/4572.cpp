#include <cstdio>
#include <cstring>

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int MAX_RANGE_VAL = static_cast<int>(1e6 + 1);

int main() {
    int N = read<int>();
    int *values = new int[MAX_RANGE_VAL];
    memset(values,0,sizeof(int) * MAX_RANGE_VAL);
    int minLeftRange = MAX_RANGE_VAL + 1,maxRightRange = 0;
    for(int i = 0;i < N;i++) {
        int left = read<int>(),right = read<int>();
        left--; right--;
        values[left]++;
        values[right + 1]--;
        if(left < minLeftRange) minLeftRange = left;
        if(right + 1 > maxRightRange) maxRightRange = right + 1;
    }
    int maxValue = 0,nowValue = 0;
    for(int i = minLeftRange;i <= maxRightRange;i++) {
        nowValue += values[i];
        if(nowValue > maxValue) maxValue = nowValue;
    }
    printf("%d\n",maxValue);
    return 0;
}
