#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
inline T read(){
    T result = 0;bool f = true;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f = !f;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main(){
    int n = read<int>(),k = read<int>(),x = read<int>();
    vector<int> works;
    works.reserve(n);
    for(int i = 0;i < n;i++){
        works.push_back(read<int>());
    }
    int skipValue = 0;
    for(int i = n - 1;n - 1 - i < k;i--){
        if(works[i] < x){
            break;
        }else{
            skipValue++;
        }
    }
    int result = skipValue * x;
    for(int i = 0;i < n - skipValue;i++){
        result += works[i];
    }
    printf("%d\n",result);
    return 0;
}
