#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main(){
    string s;
    cin >> s;
    int n;
    cin >> n;
    bool solved = false;
    bool flag1 = false,flag2 = false;
    for(int i = 0;i < n;i++){
        string tmpStr;
        cin >> tmpStr;
        if(s == tmpStr){
            printf("YES\n");
            solved = true;
            break;
        }
        if(tmpStr[0] == s[1]) flag1 = true;
        if(tmpStr[1] == s[0]) flag2 = true;
        if(flag1 && flag2){
            printf("YES\n");
            solved = true;
            break;
        }
    }
    if(!solved) printf("NO\n");
    return 0;
}
