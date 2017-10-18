#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;


int n,a,b,c;

int mem[110][110];

const int INF = 0x3f3f3f3f;

int dfs(int depth,int nowLoc) {
    if(depth == n) return 0;
    if(mem[depth][nowLoc] != -1) return mem[depth][nowLoc];
    int result = INF;
    if(nowLoc == 0) {
        result = min(result,min(dfs(depth + 1,1) + a,dfs(depth + 1,2) + b));
    }else if(nowLoc == 1) {
        result = min(result,min(dfs(depth + 1,2) + c,dfs(depth + 1,0) + a));
    }else if(nowLoc == 2) {
        result = min(result,min(dfs(depth + 1,0) + b,dfs(depth + 1,1) + c));
    }
    mem[depth][nowLoc] = result;
    return mem[depth][nowLoc];
}

int main() {
    cin >> n >> a >> b >> c;
    memset(mem,-1,sizeof(mem));
    cout << dfs(1,0) << endl;
    return 0;
}
