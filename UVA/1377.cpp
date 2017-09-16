#include <cstdio>
#include <algorithm>
#include <set>
#include <queue>
#include <cmath>
#include <cstring>

using namespace std;

int n,id[1000001],value[21],lenSize,maxValue,caseCount = 0;
bool visit[2097152];

bool solved = false;
set<int> ans;

inline int read(){
    int result = 0, f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(f == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0'){result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Data{
    int state;
    set<int> nowAns;
    Data(int state) : state(state) {}
};

void init(){
    lenSize = 0;
    ans.clear();
    solved = false;
    memset(id,0,sizeof(id));
    memset(visit,false,sizeof(visit));
    for(int i = 0;i < n;i++){
        int tmpValue = read();
        if(!id[tmpValue]) {
            value[lenSize++] = tmpValue;
            id[tmpValue] = 1;
        }
    }
    sort(value,value + lenSize);
    maxValue = value[lenSize - 1];
    memset(id,-1,sizeof(id));
    for(int i = 0;i < lenSize;i++){
        id[value[i]] = i;
    }
}

void solve(){
    queue<Data> que;
    Data startData(0);
    startData.nowAns.insert(0);
    visit[0] = true;
    que.push(startData);
    while(!que.empty()){
        Data tmpData = que.front();
        que.pop();
        if(tmpData.state == (1 << lenSize) - 1){
            if(!solved){
                ans = tmpData.nowAns;
                solved = true;
            }else if(tmpData.nowAns.size() > ans.size()){
                break;
            }else if(tmpData.nowAns.size() < ans.size()){
                ans = tmpData.nowAns;
            }else{
                if(*ans.rbegin() > *tmpData.nowAns.rbegin()){
                    ans = tmpData.nowAns;
                }
            }
        }
        if(tmpData.nowAns.size() == 7) continue;
        if(solved && tmpData.nowAns.size() > ans.size()) continue;
        for(int i = 0;i < lenSize;i++){
            if(tmpData.state & (1 << i)) continue;
            for(set<int>::iterator it = tmpData.nowAns.begin();it != tmpData.nowAns.end();it++){
                if(*it >= value[i]){
                    Data newData = tmpData;
                    int newLength = *it - value[i];
                    for(set<int>::iterator it2 = newData.nowAns.begin();it2 != newData.nowAns.end();it2++){
                        int canRule = abs(*it2 - newLength);
                        if(id[canRule] == -1) continue;
                        newData.state |= (1 << id[canRule]);
                    }
                    if(!visit[newData.state]){
                        newData.nowAns.insert(newLength);
                        que.push(newData);
                        visit[newData.state] = true;
                    }
                }
                if(*it + value[i] <= maxValue){
                    Data newData = tmpData;
                    int newLength = *it + value[i];
                    for(set<int>::iterator it2 = newData.nowAns.begin();it2 != newData.nowAns.end();it2++){
                        int canRule = abs(*it2 - newLength);
                        if(id[canRule] == -1) continue;
                        newData.state |= (1 << id[canRule]);
                    }
                    if(!visit[newData.state]){
                        newData.nowAns.insert(newLength);
                        que.push(newData);
                        visit[newData.state] = true;
                    }
                }
            }
        }
    }
    printf("Case %d:\n",++caseCount);
    printf("%d\n",ans.size());
    bool start = false;
    for(set<int>::iterator it = ans.begin();it != ans.end();it++){
        if(!start){
            start = true;
        }else{
            printf(" ");
        }
        printf("%d",*it);
    }
    printf("\n");
}

int main(){
    while(~scanf("%d",&n) && n){
        init();
        solve();
    }
    return 0;
}
