#include <cstdio>
#include <queue>
#include <functional>
#include <vector>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int N = read<int>();
    priority_queue<int,vector<int>,greater<int> > que;
    for(int i = 0;i < N;i++) {
        int opt = read<int>();
        switch(opt) {
            case 1: {
                que.push(read<int>());
                break;
            }
            case 2: {
                printf("%d\n",que.top());
                break;
            }
            case 3: {
                que.pop();
                break;
            }
        }
    }
    return 0;
}

