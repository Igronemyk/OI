#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<int> > graph(n,vector<int>(m,0));
    vector<vector<int> > index(m,vector<int>(n + 1,0));
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < m;j++) {
            cin >> graph[i][j];
            index[j][i + 1] = index[j][i] + graph[i][j];
        }
    }
    int maxScore = 0,minRemove = 0;
    for(int i = 0;i < m;i++) {
        vector<int> score(n,0);
        int nowSumValue = 0,maxScorePos = -1;
        for(int j = n - 1;j >= 0;j--) {
            nowSumValue += graph[j][i];
            int preIndex = j + k;
            if(preIndex <= n - 1) nowSumValue -= graph[preIndex][i];
            if(graph[j][i] == 1) {
                score[j] = nowSumValue;
            }else {
                score[j] = 0;
            }
            if(maxScorePos == -1) {
                maxScorePos = j;
            }else if(score[maxScorePos] <= score[j]){
                maxScorePos = j;
            }
        }
        maxScore += score[maxScorePos];
        minRemove += index[i][maxScorePos];
    }
    cout << maxScore << " " << minRemove << endl;
    return 0;
}
