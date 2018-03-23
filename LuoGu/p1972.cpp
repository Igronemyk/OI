#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX_VAL_RANGE = 1000010;

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

int main() {
    int N = read<int>(),*values = new int[N],*cnt = new int[MAX_VAL_RANGE + 1],sqrtValue = static_cast<int>(sqrt(N));
    for(int i = 0;i < N;i++) {
        values[i] = read<int>();
    }
    int M = read<int>(),*results = new int[M];
    memset(cnt,0,sizeof(int) * (MAX_VAL_RANGE + 1));
    Data *datas = new Data[M];
    for(int i = 0;i < M;i++) {
        int left = read<int>(),right = read<int>();
        left--; right--;
        datas[i] = Data(i,left,right,left / sqrtValue);
    }
    sort(datas,datas + M);
    int nowLeft = 0,nowRight = -1,result = 0;
    for(int i = 0;i < M;i++) {
        Data &tmpData = datas[i];
        while(nowLeft > tmpData.left) {
            nowLeft--;
            if(cnt[values[nowLeft]] == 0) {
                result++;
            }
            cnt[values[nowLeft]]++;
        }
        while(nowRight < tmpData.right) {
            nowRight++;
            if(cnt[values[nowRight]] == 0) {
                result++;
            }
            cnt[values[nowRight]]++;
        }
        while(nowLeft < tmpData.left) {
            cnt[values[nowLeft]]--;
            if(cnt[values[nowLeft]] == 0) {
                result--;
            }
            nowLeft++;
        }
        while(nowRight > tmpData.right) {
            cnt[values[nowRight]]--;
            if(cnt[values[nowRight]] == 0) {
                result--;
            }
            nowRight--;
        }
        results[tmpData.id] = result;
    }
    for(int i = 0;i < M;i++) {
        printf("%d\n",results[i]);
    }
    return 0;
}
