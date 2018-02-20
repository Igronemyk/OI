#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <utility>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

template<typename T>
struct Discreter {
    T *values;
    int size;
    Discreter(T *copyValues,int size) : size(size) {
        values = new T[size];
        memcpy(values,copyValues,sizeof(T) * size);
        sort(values,values + size);
        this->size = unique(values,values + size) - values;
    }

    int getSign(T value) {
        return lower_bound(values,values + size,value) - values;
    }


};

template<typename T>
struct BIT {
    T *values;
    int size;

    BIT(int size) : size(size) {
        values = new T[size + 1];
        memset(values,0,sizeof(T) * (size + 1));
    }

    void update(int pos,T val) {
        for(int i = pos;i <= size;i += lowbit(i)) {
            values[i] += val;
        }
    }

    T getSum(int pos) {
        T result = 0;
        while(pos) {
            result += values[pos];
            pos -= lowbit(pos);
        }
        return result;
    }

    int lowbit(int value) {
        return value & -value;
    }
};

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
    int n = read<int>(),sqrtValue = static_cast<int>(sqrt(n)),*values = new int[n];
    for(int i = 0;i < n;i++) {
        values[i] = read<int>();
    }
    Discreter<int> discreter(values,n);
    for(int i = 0;i < n;i++) {
        values[i] = discreter.getSign(values[i]) + 1;
    }
    int q = read<int>();
    long long *results = new long long[q];
    Data *datas = new Data[q];
    for(int i = 0;i < q;i++) {
        int x = read<int>() - 1,y = read<int>() - 1;
        datas[i] = Data(x / sqrtValue,x,y,i);
    }
    sort(datas,datas + q);
    int nowLeft = 0,nowRight = -1;
    long long result = 0;
    BIT<int> bitree(n);
    for(int i = 0;i < q;i++) {
        Data &tmpData = datas[i];
        while(nowLeft < tmpData.x) {
            result -= bitree.getSum(values[nowLeft] - 1);
            bitree.update(values[nowLeft],-1);
            nowLeft++;
        }
        while(nowLeft > tmpData.x) {
            nowLeft--;
            result += bitree.getSum(values[nowLeft] - 1);
            bitree.update(values[nowLeft],1);
        }
        while(nowRight < tmpData.y) {
            nowRight++;
            result += nowRight - nowLeft - bitree.getSum(values[nowRight]);
            bitree.update(values[nowRight],1);
        }
        while(nowRight > tmpData.y) {
            result -= nowRight - nowLeft + 1 - bitree.getSum(values[nowRight]);
            bitree.update(values[nowRight],-1);
            nowRight--;
        }
        results[tmpData.sign] = result;
    }
    for(int i = 0;i < q;i++) {
        printf("%lld\n",results[i]);
    }
    return 0;
}
