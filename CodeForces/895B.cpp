#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

struct Info {
    int value,times;
    Info() : value(-1) , times(-1) { }
    Info(int value,int times) : value(value) , times(times) { }
};

int main() {
    int n,x,k;
    cin >> n >> x >> k;
    map<int,int> countValues;
    int *values = new int[n];
    for(int i = 0;i < n;i++) {
        cin >> values[i];
    }
    sort(values,values + n);
    Info *infos = new Info[n];
    int countInfo = 0,preValue = -1;
    for(int i = 0;i < n;i++) {
        if(values[i] == preValue) {
            infos[countInfo - 1].times++;
        }else {
            preValue = values[i];
            infos[countInfo++] = Info(values[i],1);
        }
    }
    long long result = 0;
    for(int i = 0;i < countInfo;i++) {
        Info &tmpInfo = infos[i];
        int tmpValue = tmpInfo.value / x;
        result += countValues[tmpValue - k + ((tmpInfo.value % x == 0) ? 1 : 0)] * 1LL * tmpInfo.times;
        if(tmpValue % x == 0) {
            countValues[tmpValue - 1] += tmpInfo.times;
        }
        countValues[tmpValue] += tmpInfo.times;
        if((k - ((tmpInfo.value % x == 0) ? 1 : 0)) == 0) {
            result += tmpInfo.times * 1LL * tmpInfo.times;
        }
    }
    cout << result << endl;
    return 0;
}
