#include <cstdio>
#include <set>
#include <cstring>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c -'0';c = getchar();}
    return result * f;
}

int main() {
    int M = read<int>(),N = read<int>();
    int *values = new int[M],*querys = new int[M];
    for(int i = 0;i < M;i++) {
        values[i] = read<int>();
    }
    memset(querys,0,sizeof(int) * M);
    for(int i = 0;i < N;i++) {
        int tmpValue = read<int>();
        querys[tmpValue - 1]++;
    }
    multiset<int> mst;
    bool init = false;
    multiset<int>::iterator nowValue;
    for(int i = 0;i < M;i++) {
        mst.insert(values[i]);
        if(init) {
            if(values[i] < *nowValue) {
                nowValue--;
            }
        }
        while(querys[i]--) {
            if(!init) {
                init = true;
                nowValue = mst.begin();
            }else {
                nowValue++;
            }
            printf("%d\n",*nowValue);
        }
    }
    return 0;
}
