#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

inline int read(){
    int result = 0,f = 1;
    char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c -'0';c = getchar();}
    return result * f;
}

int main(){
    while(true){
        int n = read();
        if(n == 0) break;
        queue<unsigned long long> que;
        que.push(1);
        unsigned long long result = 0;
        if(n == 1){
            printf("1\n");
            continue;
        }
        while(!que.empty()){
            unsigned long long tmp = que.front();
            que.pop();
            if(tmp % n == 0) {
                result = tmp;
                break;
            }
            que.push(tmp * 10);
            que.push(tmp * 10 + 1);
        }
        printf("%lld\n",result);
    }
    return 0;
}
