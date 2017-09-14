#include <cstdio>
#include <algorithm>
#include <queue>
#include <utility>
#include <cmath>

using namespace std;

inline int read(){
    int result = 0,f = 1;
    char c = getchar();
    while(c > '9' || c < '0') {if(c == '-')f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

bool isPrime[10001],visit[10000];

void initPrime(int maxValue){
    fill(isPrime,isPrime + maxValue + 1,true);
    isPrime[0] = false;isPrime[1] = false;
    long double sqrtValue = sqrt(static_cast<long double>(maxValue));
    for(int i = 2;i <= sqrtValue;i++){
        if(isPrime[i]){
            for(int j = i;i * j <= maxValue;j++){
                isPrime[i * j] = false;
            }
        }
    }
}

int getValue(int *digit){
    return digit[0] + digit[1] * 10 + digit[2] * 100 + digit[3] * 1000;
}

int main(){
    initPrime(10000);
    int T = read();
    while(T--){
        fill(visit,visit + 10000,false);
        int a = read(),b = read();
        queue<pair<int,int> > que;
        que.push(make_pair(a,0));
        int result = 0;
        visit[a] = true;
        while(!que.empty()){
            pair<int,int> tmp = que.front();
            que.pop();
            if(tmp.first == b){
                result = tmp.second;
                break;
            }
            int *digit = new int[4],tmpValue = tmp.first;
            for(int i = 0;i < 4;i++){
                digit[i] = tmpValue % 10;
                tmpValue /= 10;
            }
            for(int i = 0;i < 4;i++){
                int oldValue = digit[i];
                for(int j = 0;j <= 9;j++){
                    if(i == 3 && j == 0) continue;
                    digit[i] = j;
                    int val = getValue(digit);
                    if(isPrime[val] && !visit[val]){
                        visit[val] = true;
                        que.push(make_pair(val,tmp.second + 1));
                    }
                }
                digit[i] = oldValue;
            }
        }
        printf("%d\n",result);
    }
    return 0;
}
