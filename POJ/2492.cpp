#include <cstdio>

using namespace std;

template<typename T>
T read(){
    T result = 0;bool f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f = !f;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct DisjointSet{
    int *father;
    DisjointSet(int size){
        father = new int[size];
        for(int i = 0;i < size;i++) father[i] = i;
    }

    int getFather(int u){
        if(father[u] == u) return u;
        return father[u] = getFather(father[u]);
    }

    void merge(int u,int v){
        int faU = getFather(u),faV = getFather(v);
        father[faU] = faV;
    }
};

int main(){
    int T = read<int>();
    for(int doingTimes = 1;doingTimes <= T;doingTimes++){
        int n = read<int>(), m = read<int>();
        DisjointSet ds(2 * n);
        bool flag = false;
        for(int i = 0;i < m;i++){
            int u = read<int>(),v = read<int>();
            u--;v--;
            if(flag) continue;
            if(ds.getFather(u) == ds.getFather(v)){
                flag = true;
                continue;
            }
            ds.merge(u,v + n);
            ds.merge(u + n,v);
        }
        printf("Scenario #%d:\n",doingTimes);
        printf(flag ? "Suspicious bugs found!\n\n" : "No suspicious bugs found!\n\n");
    }
    return 0;
}
