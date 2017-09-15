#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

inline int read(){
    int result = 0,f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int solve(int *height,int left,int right,int nowHeight){
    if(left > right) return 0;
    if(left == right) return 1;
    int minHeight = INF;
    for(int i = left;i <= right;i++){
        minHeight = min(minHeight,height[i] - nowHeight);
    }
    int result = minHeight;
    for(int i = left;i <= right;i++){
        while(i <= right && height[i] - nowHeight == minHeight) i++;
        int nowLeft = i;
        while(i <= right && height[i] - nowHeight > minHeight) i++;
        int nowRight = i - 1;
        result += solve(height,nowLeft,nowRight,nowHeight + minHeight);
    }
    return min(result,right - left + 1);
}

int main(){
    int n = read();
    int *height = new int[n];
    for(int i = 0;i < n;i++){
        height[i] = read();
    }
    printf("%d",solve(height,0,n - 1,0));
    return 0;
}
