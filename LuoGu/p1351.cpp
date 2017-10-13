#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

template<typename T>
inline T read(){
    T result = 0;bool f = true;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f = !f;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int MODDER = 10007;

namespace Adj{
    struct Node{
        int to,next;
    } nodes[400010];
    int tot,heads[200010];

    void init(){
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v){
        nodes[tot].to = v;
        nodes[tot].next = heads[u];
        heads[u] = tot++;
    }
}

using namespace Adj;

int main(){
    int n = read<int>(),maxResult = 0,result = 0;
    init();
    for(int i = 0;i < n - 1;i++){
        int u = read<int>(),v = read<int>();
        addEdge(u,v);
        addEdge(v,u);
    }
    int *value = new int[n + 1];
    for(int i = 1;i <= n;i++) value[i] = read<int>();
    for(int i = 1;i <= n;i++){
        int sumValue = 0,maxValue1,maxValue2,status = 0;
        for(int j = heads[i];j != -1;j = nodes[j].next){
            sumValue += value[nodes[j].to];
            if(status == 0){
                maxValue1 = value[nodes[j].to];
                status++;
            }else if(status == 1){
                maxValue2 = value[nodes[j].to];
                if(maxValue2 > maxValue1){
                    int tmp = maxValue1;
                    maxValue1 = maxValue2;
                    maxValue2 = tmp;
                }
                status++;
            }else{
                int tmpValue = value[nodes[j].to];
                if(tmpValue > maxValue1){
                    maxValue2 = maxValue1;
                    maxValue1 = tmpValue;
                }else if(tmpValue > maxValue2){
                    maxValue2 = tmpValue;
                }
            }
        }
        if(status != 2) continue;
        for(int j = heads[i];j != -1;j = nodes[j].next){
            result = (result + value[nodes[j].to] * ((sumValue - value[nodes[j].to]) % MODDER)) % MODDER;
        }
        maxResult = max(maxResult,maxValue1 * maxValue2);
    }
    printf("%d %d\n",maxResult,result);
    return 0;
}
