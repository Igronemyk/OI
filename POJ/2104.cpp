#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <utility>

using namespace std;

const int MAXN = 100010;
const int MAXM = 5010;
const int INF = 0x3f3f3f3f;

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

    void update(int pos,int val) {
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

BIT<int> bitree(MAXN);

struct Operation {
    int type,left,right,value,cnt;

    Operation() : type(0) , left(0) , right(0) , value(0) , cnt(0) { }

    Operation(int type,int left,int right,int value,int cnt) : type(type) , left(left) , right(right) , value(value) , cnt(cnt) { }
} opts[MAXN + MAXM],opts1[MAXN + MAXM],opts2[MAXN + MAXM];

int result[MAXM];

void cdq(int left,int right,int leftRange,int rightRange) {
    if(left > right) return;
    if(leftRange == rightRange) {
        for(int i = left;i <= right;i++) {
            if(opts[i].type == 2) {
                result[opts[i].value] = leftRange;
            }
        }
        return;
    }
    int midRange = (leftRange + rightRange) >> 1;
    int cnt1 = 0,cnt2 = 0;
    for(int i = left;i <= right;i++) {
        Operation &tmpOpt = opts[i];
        if(tmpOpt.type == 1) {
            if(tmpOpt.value <= midRange) {
                bitree.update(tmpOpt.left,1);
                opts1[cnt1++] = tmpOpt;
            }else {
                opts2[cnt2++] = tmpOpt;
            }
        }else {
            int tmpResult = bitree.getSum(tmpOpt.right) - bitree.getSum(tmpOpt.left - 1);
            if(tmpOpt.cnt - tmpResult <= 0) {
                opts1[cnt1++] = tmpOpt;
            }else {
                tmpOpt.cnt -= tmpResult;
                opts2[cnt2++] = tmpOpt;
            }
        }
    }
    for(int i = left;i <= right;i++) {
        Operation &tmpOpt = opts[i];
        if(tmpOpt.type == 1) {
            if(tmpOpt.value <= midRange) {
                bitree.update(tmpOpt.left,-1);
            }
        }
    }
    for(int i = 0;i < cnt1;i++) {
        opts[left + i] = opts1[i];
    }
    for(int i = 0;i < cnt2;i++) {
        opts[left + cnt1 + i] = opts2[i];
    }
    cdq(left,left + cnt1 - 1,leftRange,midRange);
    cdq(left + cnt1,right,midRange + 1,rightRange);
}

int main() {
    int n = read<int>(),m = read<int>();
    int nowIndex = 0;
    for(int i = 1;i <= n;i++) {
        int value = read<int>();
        opts[nowIndex++] = Operation(1,i,-1,value,-1);
    }
    for(int i = 1;i <= m;i++) {
        int left = read<int>(),right = read<int>(),k = read<int>();
        opts[nowIndex++] = Operation(2,left,right,i,k);
    }
    cdq(0,nowIndex - 1,-INF,INF);
    for(int i = 1;i <= m;i++) {
        printf("%d\n",result[i]);
    }
    return 0;
}
