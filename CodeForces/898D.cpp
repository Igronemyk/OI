#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>

using namespace std;

const int MAX_VAL = 1e6 + 1;

template<typename T>
struct BIT {
    T *values;
    int size;

    BIT(int size) : size(size) {
        values = new T[size + 1];
        memset(values,0,sizeof(T) * (size + 1));
    }

    T getSum(int pos) {
        if(pos < 0) return 0;
        T result = 0;
        while(pos) {
            result += values[pos];
            pos -= lowbit(pos);
        }
        return result;
    }

    void update(int pos,T val) {
        for(int i = pos;i <= size;i += lowbit(i)) {
            values[i] += val;
        }
    }

    int lowbit(int val) {
        return val & -val;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m,k;
    cin >> n >> m >> k;
    BIT<int> values(MAX_VAL);
    set<int> clocks;
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        values.update(tmpValue,1);
        clocks.insert(tmpValue);
    }
    int result = 0;
    for(int i = 1;i + m <= MAX_VAL + 1;i++) {
        int value = values.getSum(i + m - 1) - values.getSum(i - 1);
        while(value >= k) {
            set<int>::iterator downPos = clocks.upper_bound(i + m - 1);
            downPos--;
            values.update(*downPos,-1);
            result++;
            clocks.erase(downPos);
            value--;
        }
    }
    cout << result << endl;
    return 0;
}
