#include <cstdio>
#include <algorithm>

using namespace std;

template<typename T>
inline T read(){
    T result = 0;bool f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f = !f;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int L,N,M;

bool check(int *dis,int checkValue){
    int countValue = 0,lastValue = 0;
    for(int i = 0;i <= N;i++){
        if(dis[i] - lastValue < checkValue){
            countValue++;
        }else{
            lastValue = dis[i];
        }
    }
    return countValue <= M;
}

int main(){
    L = read<int>();
    N = read<int>();
    M = read<int>();
    int *dis = new int[N + 1];
    for(int i = 0;i < N;i++){
        dis[i] = read<int>();
    }
    dis[N] = L;
    int left = 0,right = L,result = 0;
    while(left <= right){
        int mid = (left + right) >> 1;
        if(check(dis,mid)){
            left = mid + 1;
            result = max(result,mid);
        }else{
            right = mid - 1;
        }
    }
    printf("%d\n",result);
    return 0;
}
