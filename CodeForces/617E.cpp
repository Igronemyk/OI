#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX_VALUE_RANGE = 1048576;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Data {
    int block,x,y,sign;

    Data() : block(0) , x(0) , y(0) , sign(0) { }
    Data(int block,int x,int y,int sign) : block(block) , x(x) , y(y) , sign(sign) { }

    bool operator < (const Data &otherData) const {
        if(block != otherData.block) {
            return block < otherData.block;
        }else {
            return y < otherData.y;
        }
    }
};
int main() {
    int n = read<int>(),sqrtValue = static_cast<int>(sqrt(n)),m = read<int>(),k = read<int>(),*xorValues = new int[n + 1],*cnt = new int[MAX_VALUE_RANGE];
    long long *results = new long long[m + 1];
    memset(cnt,0,sizeof(int) * MAX_VALUE_RANGE);
    cnt[0] = 1;
    xorValues[0] = 0;
    for(int i = 1;i <= n;i++) {
        int tmpValue = read<int>();
        xorValues[i] = xorValues[i - 1] ^ tmpValue;
    }
    Data *datas = new Data[m + 1];
    for(int i = 1;i <= m;i++) {
        int x = read<int>(),y = read<int>();
        datas[i] = Data(x / sqrtValue,x,y,i);
    }
    sort(datas + 1,datas + 1 + m);
    int left = 1,right = 0;
    long long result = 0;
    for(int i = 1;i <= m;i++) {
        Data &tmpData = datas[i];
        while(left > tmpData.x) {
            left--;
            result += cnt[xorValues[left - 1] ^ k];
            cnt[xorValues[left - 1]]++;
        }
        while(left < tmpData.x) {
            cnt[xorValues[left - 1]]--;
            result -= cnt[xorValues[left - 1] ^ k];
            left++;
        }
        while(right > tmpData.y) {
            cnt[xorValues[right]]--;
            result -= cnt[xorValues[right] ^ k];
            right--;
        }
        while(right < tmpData.y) {
            right++;
            result += cnt[xorValues[right] ^ k];
            cnt[xorValues[right]]++;
        }
        results[tmpData.sign] = result;
    }
    for(int i = 1;i <= m;i++) {
        printf("%lld\n",results[i]);
    }
    return 0;
}
