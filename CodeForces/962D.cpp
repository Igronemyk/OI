#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <map>
#include <set>

using namespace std;

const int MAXN = 150010;

bool isDeleted[MAXN];

long long results[MAXN];

map<long long,set<int> > values;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        values[tmpValue].insert(i);
    }
    int result = n;
    for(map<long long,set<int> >::iterator it = values.begin();it != values.end();it++) {
        long long value = it->first;
        set<int> &tmpSet = it->second;
        while(tmpSet.size() >= 2) {
            isDeleted[*tmpSet.begin()] = true;
            result--;
            tmpSet.erase(tmpSet.begin());
            values[value * 2].insert(*tmpSet.begin());
            tmpSet.erase(tmpSet.begin());
        }
        for(set<int>::iterator it = tmpSet.begin();it != tmpSet.end();it++) {
            results[*it] = value;
        }
    }
    cout << result << endl;
    for(int i = 0;i < n;i++) {
        if(isDeleted[i]) continue;
        cout << results[i] << " ";
    }
    cout << endl;
    return 0;
}

