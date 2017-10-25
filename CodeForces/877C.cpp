#include <iostream>
#include <queue>

using namespace std;

struct Data {
    int value;
    bool isKilled;
    Data() :value(-1),isKilled(false) { }
    Data(int value,bool isKilled) : value(value), isKilled(isKilled) { }
};

int main() {
    int n;
    cin >> n;
    queue<Data> que;
    que.push(Data(n / 2 + (n % 2 == 0 ? 0 : 1),false));
    while(!que.empty()) {
        Data tmpData = que.front();
        que.pop();
        cout << tmpData.value << " ";
        if(tmpData.isKilled) {

        }
    }
    return 0;
}
