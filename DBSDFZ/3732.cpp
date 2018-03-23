#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstddef>

using namespace std;

const int MAX_VAL_RANGE = 50000;

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

long long cal(int value) {
    if(value < 2) return 0;
    return value * 1LL * (value - 1) / 2;
}

int main() {
    int N = read<int>(),M = read<int>(),sqrtValue = sqrt(N),*values = new int[N],*cnt = new int[MAX_VAL_RANGE + 1];
    pair<long long,long long> *results = new pair<long long,long long>[M];
    memset(cnt,0,sizeof(int) * (MAX_VAL_RANGE + 1));
    Data *datas = new Data[M];
    for(int i = 0;i < N;i++) {
        values[i] = read<int>();
    }
    for(int i = 0;i < M;i++) {
        int x = read<int>() - 1,y = read<int>() - 1;
        datas[i] = Data(x / sqrtValue,x,y,i);
    }
    sort(datas,datas + M);
    int nowLeft = -1,nowRight = -1;
    long long result = 0;
    for(int i = 0;i < M;i++) {
        Data &tmpData = datas[i];
        if(i == 0) {
            for(int j = tmpData.x;j <= tmpData.y;j++) {
                result -= cal(cnt[values[j]]);
                cnt[values[j]]++;
                result += cal(cnt[values[j]]);
            }
            nowLeft = tmpData.x;
            nowRight = tmpData.y;
            results[tmpData.sign].first = result;
            results[tmpData.sign].second = cal(tmpData.y - tmpData.x + 1);
            continue;
        }
        while(nowLeft > tmpData.x) {
            nowLeft--;
            result -= cal(cnt[values[nowLeft]]);
            cnt[values[nowLeft]]++;
            result += cal(cnt[values[nowLeft]]);
        }
        while(nowRight < tmpData.y) {
            nowRight++;
            result -= cal(cnt[values[nowRight]]);
            cnt[values[nowRight]]++;
            result += cal(cnt[values[nowRight]]);
        }
        while(nowLeft < tmpData.x) {
            result -= cal(cnt[values[nowLeft]]);
            cnt[values[nowLeft]]--;
            result += cal(cnt[values[nowLeft]]);
            nowLeft++;
        }
        while(nowRight > tmpData.y) {
            result -= cal(cnt[values[nowRight]]);
            cnt[values[nowRight]]--;
            result += cal(cnt[values[nowRight]]);
            nowRight--;
        }
        results[tmpData.sign].first = result;
        results[tmpData.sign].second = cal(tmpData.y - tmpData.x + 1);
    }
    for(int i = 0;i < M;i++) {
        pair<long long,long long> &tmpResult = results[i];
        if(tmpResult.first == 0) {
            printf("0/1\n");
        }else {
            long long gcdValue = __gcd(tmpResult.first,tmpResult.second);
            printf("%lld/%lld\n",tmpResult.first / gcdValue,tmpResult.second / gcdValue);
        }
    }
    delete[] values;
    delete[] cnt;
    delete[] results;
    delete[] datas;
    return 0;
}
