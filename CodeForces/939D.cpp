#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
#include <utility>

using namespace std;

const int MAX_CHARSET_SIZE = 26;
const char FIRST_CHAR = 'a';

struct BCS {
    int *father;

    BCS(int size) {
        father = new int[size];
        for(int i = 0;i < size;i++) father[i] = i;
    }

    int getFather(int pos) {
        if(father[pos] == pos) return pos;
        father[pos] = getFather(father[pos]);
        return father[pos];
    }

    void merge(int u,int v) {
        int faU = getFather(u),faV = getFather(v);
        if(faU == faV) return;
        father[faU] = faV;
    }

    bool isLinked(int u,int v) {
        return getFather(u) == getFather(v);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    string a,b;
    cin >> a >> b;
    BCS bcset(MAX_CHARSET_SIZE);
    vector<pair<int,int> > results;
    for(int i = 0;i < n;i++) {
        int indexA = a[i] - FIRST_CHAR,indexB = b[i] - FIRST_CHAR;
        if(indexA == indexB) {
            continue;
        }else if(bcset.isLinked(indexA,indexB)) {
            continue;
        }else {
            bcset.merge(indexA,indexB);
            results.push_back(make_pair(indexA,indexB));
        }
    }
    cout << results.size() << endl;
    for(vector<pair<int,int> >::iterator it = results.begin();it != results.end();it++) {
        cout << static_cast<char>(it->first + FIRST_CHAR) << " " << static_cast<char>(it->second + FIRST_CHAR) << endl;
    }
    return 0;
}

