#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

bool visit[3];

int turnOpt(string opt) {
    if(opt == "&") {
        return 0;
    }else if(opt == "|") {
        return 1;
    }else {
        return 2;
    }
}

int status[10];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,optCount = 0;
    cin >> n;
    fill(status,status + 10,2);
    int *nowValue = new int[10];
    while(n--) {
        string opt;
        cin >> opt;
        int optValue = turnOpt(opt),val;
        cin >> val;
        fill(nowValue,nowValue + 10,0);
        int nowPos = 0;
        while(val) {
            nowValue[nowPos++] = (val & 1);
            val >>= 1;
        }
        for(int i = 0;i < 10;i++) {
            bool hasValue = nowValue[i] & 1;
            switch(optValue) {
                case 0: {
                    if(!hasValue) {
                        status[i] = 1;
                    }
                    break;
                }
                case 1: {
                    if(hasValue) {
                        status[i] = 4;
                    }
                    break;
                }
                case 2: {
                    if(hasValue) {
                        if(status[i] == 1) {
                            status[i] = 4;
                        }else if(status[i] == 2) {
                            status[i] = 3;
                        }else if(status[i] == 3) {
                            status[i] = 2;
                        }else if(status[i] == 4) {
                            status[i] = 1;
                        }
                    }
                    break;
                }
            }
        }
    }
    int countOne = 0,andValue = 1023;
    int countThree = 0,xorValue = 0;
    int countFour = 0,orValue = 0;
    for(int i = 0;i < 10;i++) {
        if(status[i] == 1) {
            andValue ^= (1 << i);
            countOne++;
        }else if(status[i] == 3) {
            xorValue |= (1 << i);
            countThree++;
        }else if(status[i] == 4) {
            orValue |= (1 << i);
            countFour++;
        }
    }
    int result = 0;
    if(countOne != 0) result++;
    if(countThree != 0) result++;
    if(countFour != 0) result++;
    cout << result << endl;
    if(countOne != 0) {
        cout << "& " << andValue << endl;
    }
    if(countThree != 0) {
        cout << "^ " << xorValue << endl;
    }
    if(countFour != 0) {
        cout << "| " << orValue << endl;
    }
    return 0;
}

