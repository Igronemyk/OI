#include <cstdio>
#include <algorithm>
#include <utility>

using namespace std;


const int MAX_CONDTION = 1e5;
const int MAX_VAL_RANGE = MAX_CONDTION * 2;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct BCS {
    int *father,size;
    BCS(int size) : size(size) {
        father = new int[size];
        init();
    }

    int getFather(int pos) {
        if(father[pos] == pos) return pos;
        father[pos] = getFather(father[pos]);
        return father[pos];
    }

    void init() {
        for(int i = 0;i < size;i++) father[i] = i;
    }

    void merge(int u,int v) {
        int fatherU = getFather(u),fatherV = getFather(v);
        father[fatherU] = fatherV;
    }

    bool isLinked(int u,int v) {
        return getFather(u) == getFather(v);
    }

};

int main() {
    int T = read<int>();
    BCS bcset(MAX_VAL_RANGE + 1);
    int *values = new int[MAX_VAL_RANGE];
    pair<int,int> *equalCondtion = new pair<int,int>[MAX_CONDTION],*unEqualCondtion = new pair<int,int>[MAX_CONDTION];
    while(T--) {
        bcset.init();
        int n = read<int>(),countEqual = 0,countUnEqual = 0,countValue = 0;
        while(n--) {
            int i = read<int>(),j = read<int>(),e = read<int>();
            values[countValue++] = i;
            values[countValue++] = j;
            switch(e) {
                case 0: {
                    unEqualCondtion[countUnEqual].first = i;
                    unEqualCondtion[countUnEqual++].second = j;
                    break;
                }
                case 1: {
                    equalCondtion[countEqual].first = i;
                    equalCondtion[countEqual++].second = j;
                    break;
                }
            }
        }
        sort(values,values + countValue);
        countValue = unique(values,values + countValue) - values;
        for(int i = 0;i < countEqual;i++) {
            int reFirst = lower_bound(values,values + countValue,equalCondtion[i].first) - values;
            int reSecond = lower_bound(values,values + countValue,equalCondtion[i].second) - values;
            bcset.merge(reFirst,reSecond);
        }
        bool flag = true;
        for(int i = 0;i < countUnEqual;i++) {
            int reFirst = lower_bound(values,values + countValue,unEqualCondtion[i].first) - values;
            int reSecond = lower_bound(values,values + countValue,unEqualCondtion[i].second) - values;
            if(bcset.isLinked(reFirst,reSecond)) {
                flag = false;
                break;
            }
        }
        printf(flag ? "YES\n" : "NO\n");
    }
    return 0;
}
