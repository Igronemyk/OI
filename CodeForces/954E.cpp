#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <utility>
#include <iomanip>

using namespace std;

const long double EPS = 1e-9;

int check(const long double &a,const long double &b) {
    if(a - b > EPS) {
        return -1;
    }else if(b - a > EPS) {
        return 1;
    }else {
        return 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    long double T;
    cin >> n >> T;
    long double up = 0,down = 0;
    vector<int> waters,temps;
    vector<pair<int,int> > values;
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        waters.push_back(tmpValue);
    }
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        temps.push_back(tmpValue);
    }
    for(int i = 0;i < n;i++) {
        up += waters[i] * 1LL * temps[i];
        down += waters[i];
        values.push_back(make_pair(temps[i],waters[i]));
    }
    sort(values.begin(),values.end());
    long double nowTemp = up / down;
    switch(check(nowTemp,T)) {
        case 0: {
            cout << fixed << setprecision(10) << down << endl;
            break;
        }
        case 1: {
            for(vector<pair<int,int> >::iterator it = values.begin();it != values.end();it++) {
                pair<int,int> tmpValue = *it;
                up -= tmpValue.first * 1LL * tmpValue.second;
                down -= tmpValue.second;
                if(check(up / down,T) == 1) {
                    continue;
                }
                long double result = (down * T - up) / (tmpValue.first - T);
                down += result;
                break;
            }
            cout << fixed << setprecision(10) << down << endl;
            break;
        }
        case -1: {
            for(vector<pair<int,int> >::reverse_iterator it = values.rbegin();it != values.rend();it++) {
                pair<int,int> tmpValue = *it;
                up -= tmpValue.first * 1LL * tmpValue.second;
                down -= tmpValue.second;
                if(check(up / down,T) == -1) {
                    continue;
                }
                long double result = (down * T - up) / (tmpValue.first - T);
                down += result;
                break;
            }
            cout << fixed << setprecision(10) << down << endl;
            break;
        }
    }
    return 0;
}
