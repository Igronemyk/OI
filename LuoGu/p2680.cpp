#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct BCS {
    int *father;
    BCS(int size) {
        father = new int[size];
        for(int i = 0;i < size;i++) father[i] = i;
    }

    int getFather(int pos) {
        if(father[pos] == pos) {
            return pos;
        }
        father[pos] = getFather(father[pos]);
        return father[pos];
    }

    void merge(int u,int v) {
        int fatherU = getFather(u),fatherV = getFather(v);
        if(fatherU == fatherV) return;
        father[fatherV] = fatherU;
    }

    bool isLinked(int u,int v) {
        return getFather(u) == getFather(v);
    }
};

struct Info {
    int father,edgeSign;
    Info() : father(-1) , edgeSign(-1) { }
};

struct SaveQuery {
    int u,v;
    SaveQuery() : u(-1) , v(-1) { }
};

const int MAXN = 300010;
const int MAXM = 600010;

namespace Adj {
    struct Node {
        int to,weight,next,sign;
    } nodes[MAXM];
    struct Query {
        int next,to,ansSign;
    } querys[MAXM];
    int tot,queryTot,heads[MAXN],headsForQuery[MAXN];

    void init() {
        tot = 0;
        queryTot = 0;
        memset(heads,-1,sizeof(heads));
        memset(headsForQuery,-1,sizeof(headsForQuery));
    }

    void addEdge(int u,int v,int w,int sign) {
        nodes[tot].to = v;
        nodes[tot].weight = w;
        nodes[tot].sign = sign;
        nodes[tot].next = heads[u];
        heads[u] = tot++;
    }

    void addQuery(int u,int v,int ansSign) {
        querys[queryTot].to = v;
        querys[queryTot].ansSign = ansSign;
        querys[queryTot].next = headsForQuery[u];
        headsForQuery[u] = queryTot++;
    }
}

using namespace Adj;

Info *fatherInfo;
bool *visit;
int *ans;
BCS *bcset;

void Tarjan(int now,int father) {
    for(int i = heads[now];i != -1;i = nodes[i].next) {
        if(nodes[i].to == father) continue;
        fatherInfo[nodes[i].to].father = now;
        fatherInfo[nodes[i].to].edgeSign = nodes[i].sign;
        Tarjan(nodes[i].to,now);
        bcset->merge(now,nodes[i].to);
    }
    for(int i = headsForQuery[now];i != -1;i = querys[i].next) {
        Query &tmpQuery = querys[i];
        if(!visit[tmpQuery.to]) continue;
        ans[tmpQuery.ansSign] = bcset->getFather(tmpQuery.to);
    }
    visit[now] = true;
}

int main() {
    init();
    int n = read<int>(),m = read<int>();
    fatherInfo = new Info[n];
    visit = new bool[n];
    memset(visit,false,sizeof(bool) * n);
    ans = new int[n];
    bcset = new BCS(n);
    int *edgeValue = new int[n - 1],*edgeCount = new int[n - 1];
    memset(edgeCount,0,sizeof(int) * (n - 1));
    for(int i = 0;i < n - 1;i++) {
        int a = read<int>(),b = read<int>(),t = read<int>();
        a--;b--;
        edgeValue[i] = t;
        addEdge(a,b,t,i);
        addEdge(b,a,t,i);
    }
    SaveQuery *saveQuerys = new SaveQuery[m];
    for(int i = 0;i < m;i++) {
        int u = read<int>(),v = read<int>();
        u--;v--;
        addQuery(u,v,i);
        addQuery(v,u,i);
        saveQuerys[i].u = u;
        saveQuerys[i].v = v;
    }
    Tarjan(0,-1);
    for(int i = 0;i < m;i++) {
        SaveQuery &tmpQuery = saveQuerys[i];
        int nowDoing = tmpQuery.u;
        while(nowDoing != ans[i]) {
            edgeCount[fatherInfo[nowDoing].edgeSign]++;
            nowDoing = fatherInfo[nowDoing].father;
        }
        nowDoing = tmpQuery.v;
        while(nowDoing != ans[i]) {
            edgeCount[fatherInfo[nowDoing].edgeSign]++;
            nowDoing = fatherInfo[nowDoing].father;
        }
    }
    int maxValueIndex = 0;
    for(int i = 1;i < n - 1;i++) {
        if(edgeValue[i] * edgeCount[i] > edgeValue[maxValueIndex] * edgeCount[maxValueIndex]) {
            maxValueIndex = i;
        }
    }
    int result = 0;
    for(int i = 0;i < m;i++) {
        int sumValue = 0;
        SaveQuery &tmpQuery = saveQuerys[i];
        int nowDoing = tmpQuery.u;
        while(nowDoing != ans[i]) {
            if(maxValueIndex != fatherInfo[nowDoing].edgeSign) sumValue += edgeValue[fatherInfo[nowDoing].edgeSign];
            nowDoing = fatherInfo[nowDoing].father;
        }
        nowDoing = tmpQuery.v;
        while(nowDoing != ans[i]) {
            if(maxValueIndex != fatherInfo[nowDoing].edgeSign) sumValue += edgeValue[fatherInfo[nowDoing].edgeSign];
            nowDoing = fatherInfo[nowDoing].father;
        }
        result = max(result,sumValue);
    }
    printf("%d\n",result);
    return 0;
}
