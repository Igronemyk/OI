#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstddef>
#include <iomanip>

using namespace std;
bool comp(const  pair<pair<int,int>,int> &a,const pair<pair<int,int>,int> &b) {
    if(a.first.first == b.first.first) {
        return a.first.second > b.first.second;
    }
    return a.first.first < b.first.first;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    pair<pair<int,int>,int> *values = new pair<pair<int,int>,int>[n];
    for(int i = 0;i < n;i++) {
        int l,r;
        cin >> l >> r;
        values[i] = make_pair(make_pair(l,r),i + 1);
    }
    sort(values,values + n,comp);
    int maxR = 0,nowPos = -1;
    for(int i = 0;i < n;i++) {
        if(values[i].first.second <= maxR) {
            cout << values[i].second << " " << values[nowPos].second << endl;
            return 0;
        }else {
            maxR = values[i].first.second;
            nowPos = i;
        }
    }
    cout << "-1 -1" << endl;
    return 0;
}

