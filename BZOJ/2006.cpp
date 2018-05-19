#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 500010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int values[MAXN],sumValues[MAXN],logValue[MAXN];

struct Data {
    int startSign,start,end,nowPos,value;

    Data() : startSign(-1) , start(-1) , end(-1) , nowPos(-1) , value(-1) { }
    Data(int startSign,int start,int end,int nowPos) : startSign(startSign) , start(start) , end(end) , nowPos(nowPos) , value(sumValues[nowPos] - sumValues[startSign - 1]) { }

    bool operator < (const Data &otherData) const {
        return value < otherData.value;
    }

};

struct ST {
    int **values;
    const int *keys;

    ST(int *keys,int length) : keys(keys) {
        int calLength = logValue[length];
        values = new int*[length];
        for(int i = 0;i < length;i++) {
            values[i] = new int[calLength + 1];
            values[i][0] = i;
        }
        for(int j = 1;j <= calLength;j++) {
            for(int i = 0;i + (1 << j) - 1 < length;i++) {
                if(keys[values[i][j - 1]] > keys[values[i + (1 << (j - 1))][j - 1]]) {
                    values[i][j] = values[i][j - 1];
                }else {
                    values[i][j] = values[i + (1 << (j - 1))][j - 1];
                }
            }
        }
    }

    int getMaxPos(int left,int right) {
        int calLength = logValue[right - left + 1];
        int sign1 = values[left][calLength],sign2 = values[right - (1 << calLength) + 1][calLength];
        if(keys[sign1] < keys[sign2]) {
            return sign2;
        }else {
            return sign1;
        }
    }
};

void init() {
    for(int i = 2;i < MAXN;i++) {
        logValue[i] = logValue[i >> 1] + 1;
    }
}

int main() {
    init();
    int n = read<int>(),k = read<int>(),L = read<int>(),R = read<int>();
    for(int i = 1;i <= n;i++) {
        values[i] = read<int>();
        sumValues[i] = sumValues[i - 1] + values[i];
    }
    ST table(sumValues,n + 1);
    priority_queue<Data> pq;
    for(int i = 1;i + L - 1 <= n;i++) {
        int start = i + L - 1,end = min(n,i + R - 1);
        pq.push(Data(i,start,end,table.getMaxPos(start,end)));
    }
    long long result = 0;
    while(k--) {
        Data tmpData = pq.top();
        pq.pop();
        result += tmpData.value;
        {
            int start = tmpData.start,end = tmpData.nowPos - 1;
            if(start <= end) {
                pq.push(Data(tmpData.startSign,start,end,table.getMaxPos(start,end)));
            }
        }
        {
            int start = tmpData.nowPos + 1,end = tmpData.end;
            if(start <= end) {
                pq.push(Data(tmpData.startSign,start,end,table.getMaxPos(start,end)));
            }
        }
    }
    printf("%lld\n",result);
    return 0;
}
