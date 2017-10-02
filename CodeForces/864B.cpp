#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

bool isUpperCase(char c){
    return c >= 'A' && c <= 'Z';
}

int main(){
    int n = read<int>();
    string s;
    cin >> s;
    int result = 0;
    bool visit[26];
    memset(visit,false,sizeof(visit));
    int tmpResult = 0;
    for(int i = 0;i < n;i++){
        if(isUpperCase(s[i])){
            result = max(result,tmpResult);
            tmpResult = 0;
            memset(visit,false,sizeof(visit));
            continue;
        }
        if(!visit[s[i] - 'a']){
            visit[s[i] - 'a'] = true;
            tmpResult++;
        }
    }
    cout << max(result,tmpResult) << endl;
    return 0;
}
