#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int opt;
    long long result1 = 0,result2 = 0;
    map<int,int> values;
    while(~scanf("%d",&opt)) {
        if(opt == -1) break;
        switch(opt) {
            case 1: {
                int W = read<int>(),C = read<int>();
                if(values.count(C) != 0) {
                    break;
                }
                values[C] = W;
                result1 += W;
                result2 += C;
                break;
            }
            case 2: {
                if(values.size() == 0) {
                    break;
                }
                map<int,int>::iterator it = values.end();
                it--;
                result2 -= it->first;
                result1 -= it->second;
                values.erase(it);
                break;
            }
            case 3: {
                if(values.size() == 0) {
                    break;
                }
                map<int,int>::iterator it = values.begin();
                result2 -= it->first;
                result1 -= it->second;
                values.erase(it);
                break;
            }
        }
    }
    printf("%lld %lld\n",result1,result2);
    return 0;
}
