#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_VAR_SIZE = 26;

struct Stack {
    int *values,tail;
    Stack(int size) {
        values = new int[size];
        tail = 0;
    }

    void push(int val) {
        values[tail++] = val;
    }

    int top() {
        return values[tail - 1];
    }

    void pop() {
        tail--;
    }

    bool isEmpty() {
        return tail == 0;
    }

    void clear() {
        tail = 0;
    }

};

int getFZD(string fzd) {
    if(fzd[2] == '1') {
        return 0;
    }
    int pos = 4,result = 0;
    while(fzd[pos] <= '9' && fzd[pos] >= '0') {result = result * 10 + fzd[pos] - '0';pos++;}
    return result;
}

int getVal(string s) {
    int pos = 0,len = static_cast<int>(s.size()),result = 0;
    while(pos < len && s[pos] <= '9' && s[pos] >= '0') {result = result * 10 + s[pos] - '0';pos++;}
    return result;
}

int main() {
    int T;
    cin >> T;
    bool *existVar = new bool[MAX_VAR_SIZE];
    Stack vars(MAX_VAR_SIZE);
    Stack fzdstk(10000);
    while(T--) {
        vars.clear();
        fzdstk.clear();
        memset(existVar,false,sizeof(bool) * MAX_VAR_SIZE);
        int L;
        cin >> L;
        string fzd;
        cin >> fzd;
        int resultFZD = getFZD(fzd),nowCount = 0,nowFZD = 0,maxFZD = 0,cantDo = -1;
        bool isCE = false;
        for(int i = 0;i < L;i++) {
            string opt;
            cin >> opt;
            if(opt[0] == 'F') {
                string var,x,y;
                cin >> var >> x >> y;
                if(isCE) continue;
                if(existVar[var[0] - 'a']) {
                    isCE = true;
                    continue;
                }else {
                    existVar[var[0] - 'a'] = true;
                    vars.push(var[0] - 'a');
                }
                nowCount++;
                if(cantDo != -1) {
                    fzdstk.push(0);
                    continue;
                }
                if(!(x[0] == 'n') && !(y[0] == 'n')) {
                    int valueX = getVal(x),valueY = getVal(y);
                    if(valueX <= valueY) {
                        fzdstk.push(0);
                    }else {
                        cantDo = nowCount;
                        fzdstk.push(0);
                    }
                }else if(x[0] == 'n' && !(y[0] == 'n')) {
                    cantDo = nowCount;
                    fzdstk.push(0);
                }else if(y[0] == 'n' && !(x[0] == 'n')) {
                    nowFZD++;
                    fzdstk.push(1);
                    maxFZD = max(maxFZD,nowFZD);
                }else if(x[0] == 'n' && y[0] == 'n') {
                    fzdstk.push(0);
                }
            }else if(opt[0] == 'E'){
                if(isCE) continue;
                if(cantDo == nowCount) {
                    cantDo = -1;
                }
                nowCount--;
                if(nowCount < 0) {
                    isCE = true;
                    continue;
                }
                int tmpFZD = fzdstk.top();
                fzdstk.pop();
                if(tmpFZD == 1) {
                    nowFZD--;
                }
                existVar[vars.top()] = false;
                vars.pop();
            }
        }

            if(nowCount != 0) {
                isCE = true;
            }
            if(isCE) {
                cout << "ERR" << endl;
                continue;
            }
            if(resultFZD == maxFZD) {
                cout << "Yes" << endl;
            }else {
                cout << "No" << endl;
            }
    }
    return 0;
}
