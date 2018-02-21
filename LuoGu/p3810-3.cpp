#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MAXN = 100010;
const int MIN_VAL_RANGE = 1;
const int MAX_VAL_RANGE = 200000;

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
BIT<int> bitree(MAX_VAL_RANGE);

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

} opts[MAXN],opts1[MAXN],opts2[MAXN];

bool comp(const Operation &opt1,const Operation &opt2) {
    if(opt1.y != opt2.y) {
        return opt1.y < opt2.y;
    }
    if(opt1.z != opt2.z) {
        return opt1.z < opt2.z;
    }
    return opt1.id < opt2.id;
}

void cdq(int left,int right,int leftRange,int rightRange) {
    int pos1 = 0,pos2 = 0,mid = (leftRange + rightRange) >> 1;
    if(leftRange == rightRange) {
        for(int i = left;i <= right;i++) {
            Operation &tmpOpt = opts[i];
            tmpOpt.result += bitree.getSum(tmpOpt.z);
            bitree.update(tmpOpt.z,1);
        }
        for(int i = left;i <= right;i++) {
            Operation &tmpOpt = opts[i];
            bitree.update(tmpOpt.z,-1);
        }
        return;
    }
    if(left > right) return;
    for(int i = left;i <= right;i++) {
        Operation &tmpOpt = opts[i];
        if(tmpOpt.y <= mid) {
            bitree.update(tmpOpt.z,1);
            opts1[pos1++] = tmpOpt;
        }else {
            tmpOpt.result += bitree.getSum(tmpOpt.z);
            opts2[pos2++] = tmpOpt;
        }
    }
    for(int i = left;i <= right;i++) {
        Operation &tmpOpt = opts[i];
        if(tmpOpt.y <= mid) {
            bitree.update(tmpOpt.z,-1);
        }
    }
    copy(opts1,opts1 + pos1,opts + left);
    copy(opts2,opts2 + pos2,opts + left + pos1);
    cdq(left,left + pos1 - 1,leftRange,mid);
    cdq(left + pos1,right,mid + 1,rightRange);
}

int main() {
    int n = read<int>(),k = read<int>(),minValue = MAX_VAL_RANGE,maxValue = MIN_VAL_RANGE;
    for(int i = 0;i < n;i++) {
        int x = read<int>(),y = read<int>(),z = read<int>();
        minValue = min(minValue,y);
        maxValue = max(maxValue,y);
        opts[i] = Operation(x,y,z);
        opts[i].id = i;
    }
    sort(opts,opts + n);
    cdq(0,n - 1,minValue,maxValue);
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
