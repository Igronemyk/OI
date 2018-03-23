#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MIN_VAL_RANGE = 0;
const int MAX_VAL_RANGE = 1e9;
const int MAX_OPT_SIZE = 4e5;
const int MAXN = 510;
const int MAXQ = 60010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct BIT {
    int values[MAXN + 1][MAXN + 1];

    BIT() {
        memset(values,0,sizeof(values));
    }

    void update(int x,int y,int value) {
        for(int i = x;i <= MAXN;i += lowbit(i)) {
            for(int j = y;j <= MAXN;j += lowbit(j)) {
                values[i][j] += value;
            }
        }
    }

    int getSum(int x,int y) {
        int result = 0;
        for(int i = x;i > 0;i -= lowbit(i)) {
            for(int j = y;j > 0;j -= lowbit(j)) {
                result += values[i][j];
            }
        }
        return result;
    }

    int getCnt(int x1,int y1,int x2,int y2) {
        return getSum(x2,y2) - getSum(x1 - 1,y2) - getSum(x2,y1 - 1) + getSum(x1 - 1,y1 - 1);
    }

    int lowbit(int value) {
        return value & -value;
    }

} bitree;

struct Operation {
    int type,id,x1,y1,x2,y2,k;

    Operation() : type(0) , x1(0) , y1(0) , x2(0) , y2(0) , k(0) { }

    Operation(int type,int id,int x1,int y1,int x2,int y2,int k) : type(type) , id(id) , x1(x1) , y1(y1) , x2(x2) , y2(y2) , k(k) { }

} opts[MAX_OPT_SIZE],opts1[MAX_OPT_SIZE],opts2[MAX_OPT_SIZE];

int N,Q,results[MAXQ];

void cdq(int left,int right,int leftRange,int rightRange) {
    if(left > right) return;
    if(leftRange == rightRange) {
        for(int i = left;i <= right;i++) {
            Operation &tmpOpt = opts[i];
            if(tmpOpt.type == 1) {
                results[tmpOpt.id] = leftRange;
            }
        }
        return;
    }
    int mid = (leftRange + rightRange) >> 1,cnt1 = 0,cnt2 = 0;
    for(int i = left;i <= right;i++) {
        Operation &tmpOpt = opts[i];
        if(tmpOpt.type == 0) {
            if(tmpOpt.k <= mid) {
                bitree.update(tmpOpt.x1,tmpOpt.y1,1);
                opts1[cnt1++] = tmpOpt;
            }else {
                opts2[cnt2++] = tmpOpt;
            }
        }else {
            int cnt = bitree.getCnt(tmpOpt.x1,tmpOpt.y1,tmpOpt.x2,tmpOpt.y2);
            if(cnt < tmpOpt.k) {
                tmpOpt.k -= cnt;
                opts2[cnt2++] = tmpOpt;
            }else {
                opts1[cnt1++] = tmpOpt;
            }
        }
    }
    for(int i = left;i <= right;i++) {
        Operation &tmpOpt = opts[i];
        if(tmpOpt.type == 0) {
            if(tmpOpt.k <= mid) {
                bitree.update(tmpOpt.x1,tmpOpt.y1,-1);
            }
        }
    }
    for(int i = 0;i < cnt1;i++) {
        opts[left + i] = opts1[i];
    }
    for(int i = 0;i < cnt2;i++) {
        opts[left + cnt1 + i] = opts2[i];
    }
    cdq(left,left + cnt1 - 1,leftRange,mid);
    cdq(left + cnt1,right,mid + 1,rightRange);
}

int main() {
    int cnt = 0;
    N = read<int>();
    Q = read<int>();
    for(int i = 1;i <= N;i++) {
        for(int j = 1;j <= N;j++) {
            int tmpValue = read<int>();
            opts[cnt++] = Operation(0,0,i,j,0,0,tmpValue);
        }
    }
    for(int i = 0;i < Q;i++) {
        int x1 = read<int>(),y1 = read<int>(),x2 = read<int>(),y2 = read<int>(),k = read<int>();
        opts[cnt++] = Operation(1,i,x1,y1,x2,y2,k);
    }
    cdq(0,cnt - 1,MIN_VAL_RANGE,MAX_VAL_RANGE);
    for(int i = 0;i < Q;i++) {
        printf("%d\n",results[i]);
    }
    return 0;
}
