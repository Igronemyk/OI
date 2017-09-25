#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c >'9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int N,oneCount;

bool check(int left,int right){
    cout << "? ";
    for(int i = 1;i < left;i++) cout << 0;
    for(int i = left;i <= right;i++) cout << 1;
    for(int i = right + 1;i <= N;i++) cout << 0;
    cout << endl;
    int ans = read<int>();
    return ans > oneCount - (right - left + 1) && ans < oneCount + (right - left + 1);
}

int main(){
    N = read<int>();
    cout << "? ";
    for(int i = 1;i <= N;i++) cout << 0;
    cout << endl;
    oneCount = read<int>();
    int left = 1,right = N;
    while((right - left) >= 2){
        int mid = (left + right) >> 1;
        check(mid,right) ? (left = mid) : (right = mid);
    }
    cout << "? ";
    for(int i = 1;i < left;i++) cout << 0;
    cout << 1;
    for(int i = left + 1;i <= N;i++) cout << 0;
    cout << endl;
    int ans = read<int>();
    if(ans < oneCount){
        cout << "! " << right << " " << left << endl;
    }else{
        cout << "! " << left << " " << right << endl;
    }
    return 0;
}
