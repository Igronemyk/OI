#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MAXN = 100010;
const int MAXZ = 200010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

template<typename T>
struct BIT {
    T *values;
    int size;

    BIT(int size) : size(size) {
        values = new T[size];
        clear();
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

    void clear() {
        memset(values,0,sizeof(T) * size);
    }
};

int result[MAXN];
BIT<int> bitree(MAXZ);

struct Operation {
    int x,y,z,id,result;

    Operation() : x(0) , y(0) , z(0) , id(0) , result(0) { }

    Operation(int x,int y,int z) : x(x) , y(y) , z(z) , id(0) , result(0) { }

    bool operator < (const Operation &otherOpt) const {
        if(x != otherOpt.x) {
            return x < otherOpt.x;
        }
        if(y != otherOpt.y) {
            return y < otherOpt.y;
        }
        if(z != otherOpt.z) {
            return z < otherOpt.z;
        }
        return result < otherOpt.result;
    }

    bool operator == (const Operation &otherOpt) const {
        return x == otherOpt.x && y == otherOpt.y && z == otherOpt.z;
    }

} opts[MAXN],tmp[MAXN];

bool comp(const Operation &opt1,const Operation &opt2) {
    if(opt1.y != opt2.y) {
        return opt1.y < opt2.y;
    }
    if(opt1.z != opt2.z) {
        return opt1.z < opt2.z;
    }
    return opt1.id < opt2.id;
}


void cdq(int left,int right) {
    if(left == right) return;
    int mid = (left + right) >> 1;
    cdq(left,mid);
    cdq(mid + 1,right);
    merge(opts + left,opts + mid + 1,opts + mid + 1,opts + right + 1,tmp + left,comp);
    copy(tmp + left,tmp + right + 1,opts + left);
    for(int i = left;i <= right;i++) {
        Operation &tmpOpt = opts[i];
        if(tmpOpt.id <= mid) {
            bitree.update(tmpOpt.z,1);
        }else {
            int oldResult = tmpOpt.result;
            tmpOpt.result += bitree.getSum(tmpOpt.z);
        }
    }
    for(int i = left;i <= right;i++) {
        Operation &tmpOpt = opts[i];
        if(tmpOpt.id <= mid) {
            bitree.update(tmpOpt.z,-1);
        }
    }
}

int main() {
    int n = read<int>(),k = read<int>();
    for(int i = 0;i < n;i++) {
        int x = read<int>(),y = read<int>(),z = read<int>();
        opts[i] = Operation(x,y,z);
    }
    sort(opts,opts + n);
    for(int i = 0;i < n;i++) {
        opts[i].id = i;
    }
    cdq(0,n - 1);
    sort(opts,opts + n);
    for(int i = n - 2;i >= 0;i--) {
        if(opts[i] == opts[i + 1]) {
            opts[i].result = opts[i + 1].result;
        }
    }
    for(int i = 0;i < n;i++) {
        result[opts[i].result]++;
    }
    for(int i = 0;i < n;i++) {
        printf("%d\n",result[i]);
    }
    return 0;
}

