#include <cstdio>
#include <iostream>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int k = read<int>();
    bool hasSolved = false;
    for(int i = 10000;i <= 30000;i++) {
        int sub1 = i % 1000,sub2 = (i / 10) % 1000,sub3 = i / 100;
        if(sub1 % k == 0 && sub2 % k == 0 && sub3 % k == 0) {
            printf("%d\n",i);
            if(!hasSolved) hasSolved = true;
        }
    }
    if(!hasSolved) {
        printf("No\n");
    }
    return 0;
}
