#include <cstdio>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

long long nums[] = {1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,17711,28657,46368,75025,121393,196418,317811,514229,832040,1346269,2178309,3524578,5702887,9227465,14930352,24157817,39088169,63245986,102334155,165580141,267914296,433494437,701408733,1134903170,1836311903,2971215073,4807526976,7778742049,12586269025,20365011074,32951280099,53316291173,86267571272,139583862445,225851433717,365435296162,591286729879,956722026041,1548008755920,-1};

int getDepth(long long val) {
    return lower_bound(nums,nums + 60,val) - nums;
}

long long getFather(long long val) {
    if(val == 1) return -1;
    long long *pos = lower_bound(nums,nums + 60,val);
    pos--;
    return val - (*pos);
}

int main() {
    int m = read<int>();
    while(m--) {
        long long a = read<long long>(),b = read<long long>();
        int depthA = getDepth(a),depthB = getDepth(b);
        if(a == 1 || b == 1) {
            printf("%d\n",1);
            continue;
        }
        while(a != b) {
            if(depthA != depthB) {
                if(depthA > depthB) {
                    a = getFather(a);
                    depthA = getDepth(a);
                }else {
                    b = getFather(b);
                    depthB = getDepth(b);
                }
            }else {
                a = getFather(a);
                depthA = getDepth(a);
                b = getFather(b);
                depthB = getDepth(b);
            }
        }
        printf("%lld\n",a);
    }
    return 0;
}
