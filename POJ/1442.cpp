#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>

using namespace std;

const int MAXM = 30010;
const int MAXN = 30010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int values[MAXM],askValue[MAXN];

int main() {
    int M,N;
    while(~scanf("%d%d",&M,&N)) {
        for(int i = 1;i <= M;i++) {
            values[i] = read<int>();
        }
        for(int i = 1;i <= N;i++) {
            askValue[i] = read<int>();
        }
        int askSign = 1;
        multiset<int> nowValues;
        multiset<int>::iterator it;
        for(int i = 1;i <= M;i++) {
            nowValues.insert(values[i]);
            if(i == 1) {
                it = nowValues.begin();
            }else {
                if(values[i] < *it) {
                    it--;
                }
            }
            while(askSign != N + 1 && askValue[askSign] == i) {
                if(askSign != 1) {
                    it++;
                }
                printf("%d\n",*it);
                askSign++;
            }
        }
    }
    return 0;
}
