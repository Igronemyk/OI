#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

struct Query {
    int l,r.k;
};

struct SegmentTree {

};

int main() {
    int n,q;
    int *values = new int[q * 2 + 3];
    values[0] = 1;
    values[1] = n;
    cin >> n >> q;
    Query *querys = new Query[q];
    int pos = 2;
    for(int i = 0;i < q;i++) {
        cin >> querys[i].l >> querys[i].r >> querys[i].k;
        values[pos++] = querys[i].l;
        values[pos++] = querys[i].r;
    }
    sort(values,values + pos);
    int length = unique(values,values + pos) - values;

    return 0;
}
