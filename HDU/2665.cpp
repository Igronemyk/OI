#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <utility>

using namespace std;

const int MAXN = 200010;
const int MAXM = 200010;

template<typename T>
T read() {
    int value;
    scanf("%d",&value);
    return value;
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
            Operation &tmpOpt = opts[i];
            if(tmpOpt.type == 2) {
                result[tmpOpt.value] = leftRange;
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
            int cnt = bitree.getSum(tmpOpt.right) - bitree.getSum(tmpOpt.left - 1);
            if(cnt < tmpOpt.cnt) {
                tmpOpt.cnt -= cnt;
                opts2[cnt2++] = tmpOpt;
            }else {
                opts1[cnt1++] = tmpOpt;
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
    copy(opts1,opts1 + cnt1,opts + left);
    copy(opts2,opts2 + cnt2,opts + left + cnt1);
    cdq(left,left + cnt1 - 1,leftRange,midRange);
    cdq(left + cnt1,right,midRange + 1,rightRange);
}

int values[MAXN],sortedValues[MAXN];

void solve() {
    int n = read<int>(),m = read<int>();
    int nowIndex = 0;
    for(int i = 0;i < n;i++) {
        values[i] = read<int>();
        sortedValues[i] = values[i];
    }
    sort(sortedValues,sortedValues + n);
    int sortedSize = unique(sortedValues,sortedValues + n) - sortedValues;
    for(int i = 0;i < n;i++) {
        int value = lower_bound(sortedValues,sortedValues + sortedSize,values[i]) - sortedValues;
        opts[nowIndex++] = Operation(1,i + 1,-1,value,-1);
    }
    for(int i = 1;i <= m;i++) {
        int left = read<int>(),right = read<int>(),k = read<int>();
        opts[nowIndex++] = Operation(2,left,right,i,k);
    }
    cdq(0,nowIndex - 1,0,sortedSize);
    for(int i = 1;i <= m;i++) {
        printf("%d\n",sortedValues[result[i]]);
    }
    return;
}

int main() {
    int T = read<int>();
    while(T--) {
        solve();
    }
    return 0;
}
