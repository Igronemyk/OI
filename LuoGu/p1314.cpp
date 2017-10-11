#include <cstdio>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = 0x3f3f3f3f;

template<typename T>
inline T read(){
    T result = 0;bool f = true;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f = !f;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

template<typename T>
inline T abs(T value){
    return value < 0 ? -value : value;
}

struct Data{
    int w,v;
    Data() : w(-1) , v(-1) {}
    Data(int w,int v) : w(w) ,v(v) {}
};

struct Query{
    int left,right;
    Query() : left(-1) , right(-1) {}
    Query(int left,int right) : left(left) , right(right) {}
};

int n,m;
long long S,result = LONG_MAX;

bool check(Data *datas,Query *querys,int checkValue){
    long long nowValue = 0;
    long long *sum1 = new long long [n + 1],*sum2 = new long long[n + 1];
    sum1[0] = 0;sum2[0] = 0;
    for(int i = 1;i <= n;i++){
        if(datas[i - 1].w >= checkValue){
            sum1[i] = sum1[i - 1] + 1;
            sum2[i] = sum2[i - 1] + datas[i - 1].v;
        }else{
            sum1[i] = sum1[i - 1];
            sum2[i] = sum2[i - 1];
        }
    }
    for(int i = 0;i < m;i++){
        nowValue += (sum1[querys[i].right] - sum1[querys[i].left - 1]) * (sum2[querys[i].right] - sum2[querys[i].left - 1]);
    }
    result = min(result,abs(S - nowValue));
    return nowValue > S;
}

int main(){
    n = read<int>();
    m = read<int>();
    S = read<long long>();
    Data *datas = new Data[n];
    int left = INF,right = -INF;
    for(int i = 0;i < n;i++){
        int w = read<int>(),v = read<int>();
        datas[i] = Data(w,v);
        left = min(left,w);
        right = max(right,w);
    }
    Query *querys = new Query[m];
    for(int i = 0;i < m;i++){
        int left = read<int>(),right = read<int>();
        querys[i] = Query(left,right);
    }
    while(left <= right){
        int mid = (left + right) >> 1;
        if(check(datas,querys,mid)){
            left = mid + 1;
        }else{
            right = mid - 1;
        }
    }
    printf("%lld\n",result);
    return 0;
}
