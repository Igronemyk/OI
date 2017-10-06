#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

template<typename T>
T read(){
    T result = 0;bool f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f = !f; c = getchar();}
    while(c <='9' && c >= '0') {result = result * 10 + c - '0'; c = getchar();}
    return result * f;
}

int main(){
    int n = read<int>();
    vector<int> visit(n,0),per;
    per.reserve(n);
    for(int i = 0;i < n;i++){
        int tmpValue = read<int>();
        tmpValue--;
        visit[tmpValue]++;
        per.push_back(tmpValue);
    }
    stack<int> stk;
    int result = 0;
    for(int i = n - 1;i >= 0;i--){
        if(visit[i] == 0){
            result++;
            stk.push(i);
        }
    }
    vector<bool> isSkiped(n,false);
    for(vector<int>::iterator it = per.begin();it != per.end();it++){
        if(visit[*it] == 1) continue;
        if(stk.top() > *it && !isSkiped[*it]){
            isSkiped[*it] = true;
            continue;
        }
        visit[*it]--;
        *it = stk.top();
        stk.pop();
    }
    printf("%d\n",result);
    for(vector<int>::iterator it = per.begin();it != per.end();it++) printf("%d ",*it + 1);
    printf("\n");
    return 0;
}
