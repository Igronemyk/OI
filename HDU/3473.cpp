#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_DEPTH = 18;
const int MAXN = 100005;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int values[MAXN];

long long sumValues[MAXN];

struct PTree {
    int values[MAX_DEPTH][MAXN],toLeft[MAX_DEPTH][MAXN],sortedValues[MAXN],size;
    long long sum[MAX_DEPTH][MAXN];

    void init() {
        memset(values,0,sizeof(values));
        memset(toLeft,0,sizeof(toLeft));
        memset(sum,0,sizeof(sum));
    }

    void build(int *initValues,int size) {
        this->size = size;
        init();
        for(int i = 1;i <= size;i++) {
            values[0][i] = initValues[i];
            sortedValues[i] = initValues[i];
        }
        sort(sortedValues + 1,sortedValues + size + 1);
        build(0,1,size);
    }

    void build(int depth,int left,int right) {
        if(left == right) return;
        int mid = (left + right) >> 1,midValue = sortedValues[mid];
        int leftSize = mid - left + 1,posL = left,posR = mid + 1;
        for(int i = left;i <= right;i++) {
            if(values[depth][i] < midValue) leftSize--;
        }
        for(int i = left;i <= right;i++) {
            int flag = 0;
            if(values[depth][i] < midValue || (values[depth][i] == midValue && leftSize > 0)) {
                flag = 1;
                values[depth + 1][posL++] = values[depth][i];
                if(values[depth][i] == midValue) leftSize--;
                sum[depth][i] = sum[depth][i - 1] + values[depth][i];
            }else {
                values[depth + 1][posR++] = values[depth][i];
                sum[depth][i] = sum[depth][i - 1];
            }
            toLeft[depth][i] = toLeft[depth][i - 1] + flag;
        }
        build(depth + 1,left,mid);
        build(depth + 1,mid + 1,right);
    }

    int query(int left,int right,int k,int &lessCnt,long long &lessSum) {
        return query(0,1,size,left,right,k,lessCnt,lessSum);
    }

    int query(int depth,int left,int right,int l,int r,int k,int &lessCnt,long long &lessSum) {
        if(left == right) return values[depth][left];
        int mid = (left + right) >> 1;
        int lx = toLeft[depth][l - 1] - toLeft[depth][left - 1],ly = toLeft[depth][r] - toLeft[depth][l - 1],rx = l - 1 - left + 1 - lx,ry = r - l + 1 - ly;
        if(ly >= k) {
            return query(depth + 1,left,mid,left + lx,left + lx + ly - 1,k,lessCnt,lessSum);
        }else {
            lessCnt += ly;
            lessSum += sum[depth][r] - sum[depth][l - 1];
            return query(depth + 1,mid + 1,right,mid + 1 + rx,mid + 1 + rx + ry - 1,k - ly,lessCnt,lessSum);
        }
    }
} ptree;


int main() {
    int T = read<int>();
    for(int nowCase = 1;nowCase <= T;nowCase++) {
        int N = read<int>();
        for(int i = 1;i <= N;i++) {
            values[i] = read<int>();
            sumValues[i] = sumValues[i - 1] + values[i];
        }
        ptree.build(values,N);
        int Q = read<int>();
        printf("Case #%d:\n",nowCase);
        while(Q--) {
            int l = read<int>(),r = read<int>(),k = ((r - l + 1) >> 1) + 1;
            l++; r++;
            long long lessValue = 0;
            int lessCnt = 0;
            long long midValue = ptree.query(l,r,k,lessCnt,lessValue);
            int greaterCnt = (r - l + 1) - lessCnt;
            long long greaterValue = sumValues[r] - sumValues[l - 1] - lessValue;
            printf("%lld\n",(greaterValue - greaterCnt * midValue) + (lessCnt * midValue - lessValue));
        }
        printf("\n");
    }
    return 0;
}
