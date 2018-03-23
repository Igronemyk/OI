#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Data {
    int id,left,right,block;

    Data() : id(-1) , left(-1) , right(-1) , block(-1) { }

    Data(int id,int left,int right,int block) : id(id) , left(left) , right(right) , block(block) { }

    bool operator < (const Data &otherData) const {
        if(block != otherData.block) return block < otherData.block;
        return right < otherData.right;
    }
};

int calc(int value) {
    return value * value;
}

int main() {
    int N = read<int>(),M = read<int>(),K = read<int>(),sqrtValue = static_cast<int>(sqrt(N)),*values = new int[N];
    for(int i = 0;i < N;i++) {
        values[i] = read<int>();
    }
    Data *datas = new Data[M];
    for(int i = 0;i < M;i++) {
        int left = read<int>(),right = read<int>();
        left--; right--;
        datas[i] = Data(i,left,right,left / sqrtValue);
    }
    sort(datas,datas + M);
    int nowLeft = 1,nowRight = 0,*cnt = new int[K + 1];
    memset(cnt,0,sizeof(int) * (K + 1));
    long long result = 0,*results = new long long[M];
    for(int i = 0;i < M;i++) {
        Data &tmpData = datas[i];
        while(nowLeft > tmpData.left) {
            nowLeft--;
            result -= calc(cnt[values[nowLeft]]);
            cnt[values[nowLeft]]++;
            result += calc(cnt[values[nowLeft]]);
        }
        while(nowRight < tmpData.right) {
            nowRight++;
            result -= calc(cnt[values[nowRight]]);
            cnt[values[nowRight]]++;
            result += calc(cnt[values[nowRight]]);
        }
        while(nowLeft < tmpData.left) {
            result -= calc(cnt[values[nowLeft]]);
            cnt[values[nowLeft]]--;
            result += calc(cnt[values[nowLeft]]);
            nowLeft++;
        }
        while(nowRight > tmpData.right) {
            result -= calc(cnt[values[nowRight]]);
            cnt[values[nowRight]]--;
            result += calc(cnt[values[nowRight]]);
            nowRight--;
        }
        results[tmpData.id] = result;
    }
    for(int i = 0;i < M;i++) {
        printf("%lld\n",results[i]);
    }
    return 0;
}
