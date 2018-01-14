#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

struct BCS {
    int *father;
    BCS(int size) {
        father = new int[size + 1];
        for(int i = 0;i <= size;i++) father[i] = i;
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
};

struct Info {
    int weight;
    int value;
    int sign;
    Info() : weight(-1) , value(-1) , sign(-1) { }
    Info(int weight,int value,int sign) : weight(weight) , value(value) , sign(sign) { }
    bool operator < (const Info &otherInfo) const {
        if(weight != otherInfo.weight) {
            return weight < otherInfo.weight;
        }else {
            return sign > otherInfo.sign;
        }
    }
};

int main() {
    int n;
    cin >> n;
    set<Info> values;
    vector<Info> infos;
    int lastValue = -1,lastCount = 0,sign = 1;
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        if(tmpValue != lastValue) {
            Info tmpInfo(lastCount,lastValue,sign);
            if(lastValue != -1) {
                values.insert(tmpInfo);
                infos.push_back(tmpInfo);
                sign++;
            }
            lastValue = tmpValue;
            lastCount = 1;
        }else {
            lastCount++;
        }
    }
    if(lastCount != 0) {
        Info tmpInfo(lastCount,lastValue,sign);
        values.insert(tmpInfo);
        infos.push_back(tmpInfo);
    }
    sign++;
    BCS leftSet(sign + 1),rightSet(sign + 1);
    int result = 0;
    while(!values.empty()) {
        Info tmpInfo = *(--values.end());
        result++;
        values.erase(--values.end());
        int leftSign = tmpInfo.sign - 1,rightSign = tmpInfo.sign + 1;
        bool isVaildLeft = false,isVaildRight = false;
        if(leftSign > 0) {
            leftSign = leftSet.getFather(leftSign);
            if(leftSign != 0) {
                isVaildLeft = true;
            }
        }
        leftSet.merge(tmpInfo.sign,leftSign);
        if(rightSign <= sign) {
            rightSign = rightSet.getFather(rightSign);
            if(rightSign != sign + 1) {
                isVaildRight = true;
            }
        }
        rightSet.merge(tmpInfo.sign,rightSign);
        while(isVaildLeft && isVaildRight) {
            if(infos[leftSign - 1].value == infos[rightSign - 1].value) {
                set<Info>::iterator leftIt = values.find(infos[leftSign - 1]),rightIt = values.find(infos[rightSign - 1]);
                Info newInfo(infos[leftSign - 1].weight + infos[rightSign - 1].weight,infos[leftSign - 1].value,leftSign);
                values.insert(newInfo);
                infos[leftSign - 1] = newInfo;
                int removeSign = rightSign;
                rightSign = rightSign + 1;
                isVaildRight = false;
                if(rightSign <= sign) {
                    rightSign = rightSet.getFather(rightSign);
                    if(rightSign != sign + 1) {
                        isVaildRight = true;
                    }
                }
                leftSet.merge(removeSign,leftSign);
                rightSet.merge(removeSign,rightSign);
                values.erase(leftIt);
                values.erase(rightIt);
            }else {
                break;
            }
        }
    }
    cout << result << endl;
    return 0;
}
