#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <set>
#include <map>

using namespace std;

const long long MAX_RANGE = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    set<long long> values;
    queue<long long> doingValues;
    map<long long,bool> isVisited;
    int *primes = new int[n];
    for(int i = 0;i < n;i++) {
        cin >> primes[i];
        doingValues.push(primes[i]);
        values.insert(primes[i]);
    }
    values.insert(1);
    int k;
    cin >> k;
    while(!doingValues.empty()) {
        long long tmpValue = doingValues.front();
        doingValues.pop();
        for(int i = 0;i < n;i++) {
            unsigned long long tmpCalValue = tmpValue;
            tmpCalValue *= primes[i];
            if(tmpCalValue > MAX_RANGE) continue;
            if(isVisited.count(tmpCalValue) == 0) {
                doingValues.push(tmpCalValue);
                values.insert(tmpCalValue);
                isVisited[tmpCalValue] = true;
            }
        }
        if(values.size() > k * 4) break;
    }
    set<long long>::iterator it = values.begin();
    while(--k) {
        it++;
    }
    cout << *it << endl;
    return 0;
}

