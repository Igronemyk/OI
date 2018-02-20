#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_VAL_RANGE = 10000;

bool visit[MAX_VAL_RANGE + 1];
int rowNum[MAX_VAL_RANGE + 1];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(visit,false,sizeof(visit));
    int n;
    cin >> n;
    vector<vector<int> > rows,cols;
    for(int i = 0;i < 2 * n;i++) {
        vector<int> tmp;
        tmp.reserve(n);
        bool flag = true;
        for(int j = 0;j < n;j++) {
            int tmpValue;
            cin >> tmpValue;
            if(flag && visit[tmpValue]) {
                flag = false;
            }
            tmp.push_back(tmpValue);
        }
        if(flag) {
            for(vector<int>::iterator it = tmp.begin();it != tmp.end();it++) {
                visit[*it] = true;
                rowNum[*it] = rows.size();
            }
            rows.push_back(tmp);
        }else {
            cols.push_back(tmp);
        }
    }
    vector<int> selectCol = *(cols.begin());
    for(vector<int>::iterator colIt = selectCol.begin();colIt != selectCol.end();colIt++) {
        int row = rowNum[*colIt];
        for(vector<int>::iterator rowIt = rows[row].begin();rowIt != rows[row].end();rowIt++) {
            cout << *rowIt << " ";
        }
    }
    cout << endl;
    return 0;
}
