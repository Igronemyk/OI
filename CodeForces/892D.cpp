#include <iostream>
#include <algorithm>

using namespace std;

int n;

bool dfs(int depth,bool *visit,int *values,long long *sumIndex,int *nowValues,long long nowSumIndex) {
    if(depth == n - 1) {
        for(int i = 0;i < n;i++) {
            if(visit[i]) continue;
            nowValues[depth] = values[i];
            break;
        }
        return true;
    }
    for(int i = 0;i < n;i++) {
        if(visit[i]) continue;
        if(sumIndex[depth + 1] == nowSumIndex + values[i]) {
            continue;
        }
        visit[i] = true;
        nowValues[depth] = values[i];
        bool tmpResult = dfs(depth + 1,visit,values,sumIndex,nowValues,nowSumIndex + values[i]);
        visit[i] = false;
        if(tmpResult) return true;
    }
    return false;
}

int main() {
    cin >> n;
    int *values = new int[n];
    long long *sumIndex = new long long[n + 1];
    sumIndex[0] = 0;
    for(int i = 0;i < n;i++) {
        cin >> values[i];
        sumIndex[i + 1] = sumIndex[i] + values[i];
    }
    bool *visit = new bool[n];
    fill(visit,visit + n,false);
    int *nowValues = new int[n];
    fill(nowValues,nowValues + n,-1);
    bool result = dfs(0,visit,values,sumIndex,nowValues,0);
    if(result) {
        for(int i = 0;i < n;i++) {
            cout << nowValues[i] << " ";
        }
        cout << endl;
    }else {
        cout << -1 << endl;
    }
    return 0;
}

