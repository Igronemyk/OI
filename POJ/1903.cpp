#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

int state[24];

map<int,int> tmpAns;

int bitCount(int x){
    int result = 0;
    while(x){
        result++;
        x = x & (x - 1);
    }
    return result;
}

int main(){
    int n;
    while(~scanf("%d",&n)){
        memset(state,0,sizeof(state));
        tmpAns.clear();
        for(int i = 0;i < n;i++){
            string s;
            cin >> s;
            for(string::iterator it = s.begin();it != s.end();it++){
                state[i] ^= (1 << (*it - 'A'));
            }
        }
        int n1 = n/2,n2 = n - n1;
        for(int i = 0;i < (1 << n1);i++){
            int tmpResult = 0;
            for(int j = 0;j < n1;j++) tmpResult ^= ((i >> j) & 1) * state[j];
            if(!tmpAns.count(tmpResult) || bitCount(i) > bitCount(tmpAns[tmpResult])) tmpAns[tmpResult] = i;
        }
        int result = 0;
        for(int i = 0;i < (1 << n2);i++){
            int tmpResult = 0;
            for(int j = 0;j < n2;j++) tmpResult ^= ((i >> j) & 1) * state[j + n1];
            if(tmpAns.count(tmpResult) && bitCount(i) + bitCount(tmpAns[tmpResult] > bitCount(result))) result = (i << n1) | tmpAns[tmpResult];
        }
        printf("%d\n",bitCount(result));
        for(int i = 0;i < n;i++) if(result & (1 << i)) printf("%d ",i + 1);
        printf("\n");
    }
    return 0;
}
