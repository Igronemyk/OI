#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int main() {
    int T;
    scanf("%d",&T);
    while(T--) {
        long long n;
        scanf("%lld",&n);
        if(n == 0) {
            printf("%d %d\n",2,5);
        }else if(n == 1) {
            printf("%d %d\n",2,3);
        }else if(n == 2) {
            printf("%d %d\n",3,5);
        }else if(n == 3) {
            printf("%d %d\n",1,2);
        }else if(n == 4) {
            printf("%d %d\n",1,4);
        }else {
            if(n & 1LL) {
                printf("%lld %lld\n",n - 3,n - 1);
            }else {
                printf("%lld %lld\n",n - 4,n);
            }
        }
    }
    return 0;
}
