#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MAXN = 100010;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct SegmentTree {
    int ch[MAXN << 2][2],sZ,root,left,right;
    long long sum[MAXN << 2],mV[MAXN << 2];
    
    int newNode(long long value) {
        int sign = ++sZ;
        ch[sign][0] = 0;
        ch[sign][1] = 0;
        sum[sign] = value;
        mV[sign] = value;
        return sign;
    }

    void init(long long *values,int size) {
        sZ = 0;
        left = 1;
        right = size;
        root = buildTree(left,right,values);
    }

    void updateInfo(int now) {
        sum[now] = sum[ch[now][0]] + sum[ch[now][1]];
        mV[now] = max(mV[ch[now][0]],mV[ch[now][1]]);
    }
    int buildTree(int left,int right,long long *values) {
        if(left > right) return 0;
        if(left == right) return newNode(values[left]);
        int mid = (left + right) >> 1,now = newNode(0);
        ch[now][0] = buildTree(left,mid,values);
        ch[now][1] = buildTree(mid + 1,right,values);
        updateInfo(now);
        return now;
    }

    void sqrtVal(int l,int r) {
        sqrtVal(root,left,right,l,r);
    }

    void sqrtVal(int now,int left,int right,int l,int r) {
        if(left == right) {
            sum[now] = static_cast<long long>(floor(sqrt(sum[now])));
            mV[now] = sum[now];
            return;
        }
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                if(mV[ch[now][0]] > 1) {
                    sqrtVal(ch[now][0],left,mid,l,r);
                }
            }else {
                if(mV[ch[now][0]] > 1) {
                    sqrtVal(ch[now][0],left,mid,l,mid);
                }
                if(mV[ch[now][1]] > 1) {
                    sqrtVal(ch[now][1],mid + 1,right,mid + 1,r);
                }
            }
        }else {
            if(mV[ch[now][1]] > 1) {
                sqrtVal(ch[now][1],mid + 1,right,l,r);
            }
        }
        updateInfo(now);
    }

    long long getSum(int l,int r) {
        return getSum(root,left,right,l,r);
    }

    long long getSum(int now,int left,int right,int l,int r) {
        if(left == l && right == r) {
            return sum[now];
        }
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                return getSum(ch[now][0],left,mid,l,r);
            }else {
                return getSum(ch[now][0],left,mid,l,mid) + getSum(ch[now][1],mid + 1,right,mid + 1,r);
            }
        }else {
            return getSum(ch[now][1],mid + 1,right,l,r);
        }
    }

} stree;

long long values[MAXN];

int main() {
    int n = read<int>();
    for(int i = 1;i <= n;i++) {
        values[i] = read<long long>();
    }
    stree.init(values,n);
    int m = read<int>();
    while(m--) {
        int opt = read<int>();
        if(opt == 0) {
            int l = read<int>(),r = read<int>();
            if(l > r) swap(l,r);
            stree.sqrtVal(l,r);
        }else {
            int l = read<int>(),r = read<int>();
            if(l > r) swap(l,r);
            printf("%lld\n",stree.getSum(l,r));
        }
    }
    return 0;
}
