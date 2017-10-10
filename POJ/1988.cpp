#include <iostream>
#include <algorithm>

using namespace std;

struct DisjointSet{
    int *father,*son,*depth;
    DisjointSet(int size){
        father = new int[size];
        son = new int[size];
        depth = new int[size];
        for(int i = 0;i < size;i++) father[i] = i;
        fill(son,son + size,1);
        fill(depth,depth + size,0);
    }

    int getFather(int u){
        if(father[u] == u) return u;
        int tmpValue = father[u];
        father[u] = getFather(father[u]);
        depth[u] += depth[tmpValue];
        return father[u];
    }

    void merge(int u,int v){
        int faU = getFather(u),faV = getFather(v);
        father[faV] = faU;
        depth[faV] += son[faU];
        son[faU] += son[faV];
    }

    bool isLink(int u,int v){
        return this->getFather(u) == this->getFather(v);
    }

    int getSize(int u){
        return this->son[this->getFather(u)] - this->depth[u] - 1;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    DisjointSet ds(30000);
    int P;
    cin >> P;
    for(int i = 0;i < P;i++){
        char opt;
        cin >> opt;
        if(opt == 'M'){
            int u,v;
            cin >> u >> v;
            u--;v--;
            if(!ds.isLink(u,v)){
                ds.merge(u,v);
            }
        }else{
            int pos;
            cin >> pos;
            pos--;
            cout << ds.getSize(pos) << endl;
        }
    }
    return 0;
}
