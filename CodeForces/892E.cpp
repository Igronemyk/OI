#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

struct BCS {
    int *father,size;
    BCS(int size) : size(size) {
        father = new int[size];
        init();
    }

    void init() {
        for(int i = 0;i < size;i++) father[i] = i;
    }

    int getFather(int pos) {
        if(father[pos] == pos) return pos;
        father[pos] = getFather(father[pos]);
        return father[pos];
    }

    bool merge(int u,int v) {
        int fatherU = getFather(u),fatherV = getFather(v);
        if(fatherU == fatherV) return false;
        father[fatherU] = fatherV;
        return true;
    }

    bool isLinked(int u,int v) {
        return getFather(u) == getFather(v);
    }
};

struct Graph {
    struct Edge {
        int next,to,weight;
    };
    Edge *edges;
    int tot,*heads;
    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v,int w) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        edges[tot].weight = w;
        heads[u] = tot++;
    }
};

struct Info {
    int from,to,values;
    bool operator < (const Info &otherInfo) const {
        return this->values < otherInfo.values;
    }
};


int main() {
    int n,m;
    cin >> n >> m;
    Info *infos = new Info[m],*sortedInfos = new Info[m];
    BCS bcset(n + 1);
    for(int i = 0;i < m;i++) {
        Info &tmpInfo = infos[i];
        cin >> tmpInfo.from >> tmpInfo.to >> tmpInfo.values;
        Info &sortedInfo = sortedInfos[i];
        sortedInfo.from = tmpInfo.from;
        sortedInfo.to = tmpInfo.to;
        sortedInfo.values = tmpInfo.values;
    }
    sort(sortedInfos,sortedInfos + m);
    int q;
    cin >> q;
    while(q--) {
        int k;
        cin >> k;
        bcset.init();
        bool flag = true;
        int maxValue = 0;
        while(k--) {
            int tmpValue;
            cin >> tmpValue;
            if(!flag) continue;
            tmpValue--;
            Info &tmpInfo = infos[tmpValue];
            if(!bcset.merge(tmpInfo.from,tmpInfo.to)) {
                flag = false;
            }
            maxValue = max(maxValue,tmpInfo.values);
        }
        if(!flag) {
            cout << "NO" << endl;
            continue;
        }
        int pos = 0;
        while(sortedInfos[pos].values < maxValue) {
            Info &tmpInfo = sortedInfos[pos];
            cout << "At " << tmpInfo.values;
            if(bcset.isLinked(tmpInfo.from,tmpInfo.to)) {
                flag = false;
                break;
            }
            pos++;
        }
        if(!flag) {
            cout << "NO" << endl;
        }else {
            cout << "YES" << endl;
        }
    }
    return 0;
}
