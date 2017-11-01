#include <cstdio>
#include <vector>
#include <functional>
#include <queue>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int N;
    while(~scanf("%d",&N)) {
        priority_queue<int,vector<int>,greater<int> > que;
        for(int i = 0;i < N;i++) {
            que.push(read<int>());
        }
        long long result = 0;
        while(que.size() > 1) {
            int val1 = que.top();
            que.pop();
            int val2 = que.top();
            que.pop();
            int val3 = val1 + val2;
            que.push(val3);
            result += val3;
        }
        printf("%lld\n",result);
    }
    return 0;
}
