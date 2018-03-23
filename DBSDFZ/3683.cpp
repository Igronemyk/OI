#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>

using namespace std;

const int MODDER = 9901;
const int MAX_VAL_RANGE = 8000;

long long quickPow(long long a,long long b) {
    long long result = 1,base = a;
    while(b) {
        if(b & 1) result = (result * base) % MODDER;
        base = (base * base) % MODDER;
        b >>= 1;
    }
    return result;
}

long long inv(long long value) {
    return quickPow(value,MODDER - 2);
}

int main() {
    long long A,B;
    while(~scanf("%lld%lld",&A,&B)){
        pair<long long,long long> *values = new pair<long long,long long>[MAX_VAL_RANGE + 1];
        int nowIndex = 0;
        for(int i = 2;i * i <= A;i++) {
            if(A % i != 0) continue;
            values[nowIndex].first = i;
            values[nowIndex].second = 0;
            while(A % i == 0) {
                values[nowIndex].second++;
                A /= i;
            }
            nowIndex++;
        }
        if(A > 1) {
            values[nowIndex].first = A;
            values[nowIndex].second = 1;
            A = 1;
            nowIndex++;
        }
        for(int i = 0;i < nowIndex;i++) {
            values[i].second *= B;
        }
        long long result = 1;
        for(int i = 0;i < nowIndex;i++) {
            pair<long long,long long> &tmpValue = values[i];
            if(tmpValue.first % MODDER - 1 == 0) {
                result = result * (tmpValue.second + 1) % MODDER;
            }else {
                result = result * (((quickPow(tmpValue.first % MODDER,tmpValue.second + 1) - 1 + MODDER) % MODDER * inv((tmpValue.first % MODDER - 1 + MODDER) % MODDER)) % MODDER) % MODDER;
            }
        }
        printf("%lld\n",result);
    }
    return 0;
}
