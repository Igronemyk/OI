#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int MAXN = 1e5 + 10;

vector<int> links[MAXN];
vector<int> newLinks[MAXN];
int values[MAXN];
stack<int> stk;
bool isInStack[MAXN];
int dfn[MAXN],low[MAXN],nowIndex,nowSqrt,sqrtValues[MAXN],valueCnts[MAXN];

void tarjan(int now) {
    dfn[now] = ++nowIndex;
    low[now] = dfn[now];
    isInStack[now] = true;
    stk.push(now);
    for(vector<int>::iterator it = links[now].begin();it != links[now].end();it++) {
        if(dfn[*it] == 0) {
            tarjan(*it);
            low[now] = min(low[now],low[*it]);
        }else if(isInStack[*it]) {
            low[now] = min(low[now],low[*it]);
        }
    }
    if(dfn[now] == low[now]) {
        int tmpValue;
        do {
            tmpValue = stk.top();
            stk.pop();
            sqrtValues[tmpValue] = nowSqrt;
            isInStack[tmpValue] = false;
            valueCnts[nowSqrt]++;
        }while(tmpValue != now);
        nowSqrt++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m,h;
    cin >> n >> m >> h;
    for(int i = 1;i <= n;i++) {
        int tmpValue;
        cin >> tmpValue;
        values[i] = tmpValue;
    }
    for(int i = 1;i <= m;i++) {
        int u,v;
        cin >> u >> v;
        if((values[u] + 1) % h == values[v]) {
            links[u].push_back(v);
        }
        if((values[v] + 1) % h == values[u]) {
            links[v].push_back(u);
        }
    }
    for(int i = 1;i <= n;i++) {
        if(dfn[i] == 0) {
            tarjan(i);
        }
    }
    for(int start = 1;start <= n;start++) {
        for(vector<int>::iterator it = links[start].begin();it != links[start].end();it++) {
            if(sqrtValues[start] == sqrtValues[*it]) {
                continue;
            }
            newLinks[sqrtValues[start]].push_back(sqrtValues[*it]);
        }
    }
    int minPos = -1,minSize = MAXN;
    for(int now = 0;now < nowSqrt;now++) {
        int size = newLinks[now].size();
        if(size == 0) {
            if(minSize > valueCnts[now]) {
                minSize = valueCnts[now];
                minPos = now;
            }
        }
    }
    int cnt = 0;
    vector<int> result;
    for(int i = 1;i <= n;i++) {
        if(minPos == sqrtValues[i]) {
            result.push_back(i);
        }
    }
    if(result.size() != minSize) exit(1);
    cout << result.size() << endl;
    for(vector<int>::iterator it = result.begin();it != result.end();it++) {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}

