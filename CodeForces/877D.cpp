#include <iostream>
#include <queue>
#include <string>

using namespace std;

int nextX[] = {1,0,-1,0};
int nextY[] = {0,1,0,-1};
bool graph[1001][1001];
bool visit[1001][1001];

struct Data {
    int depth;
    int nowX,nowY;
    Data() : depth(-1),nowX(-1),nowY(-1) {}
    Data(int depth,int nowX,int nowY) : depth(depth),nowX(nowX),nowY(nowY) { }
};

int n,m,k;

bool check(int x,int y) {
    return x >= 0 && x < n && y >= 0 && y < m && graph[x][y];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> k;
    for(int i = 0;i < n;i++) {
        string s;
        cin >> s;
        for(int j = 0;j < m;j++) {
            if(s[j] == '.') {
                graph[i][j] = true;
            }
        }
    }
    int x1,y1,x2,y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x1--;y1--;x2--;y2--;

    queue<Data> que;
    que.push(Data(0,x1,y1));
    visit[x1][y1] = true;
    int result = -1;
    if(x1 == x2 && y1 == y2) {
        result = 0;
        goto outside;
    }
    while(!que.empty()) {
        Data tmpData = que.front();
        que.pop();
        for(int i = 0;i < 4;i++) {
           for(int step = 1;step <= k;step++) {
                int newX = tmpData.nowX + nextX[i] * step;
                int newY = tmpData.nowY + nextY[i] * step;
                if(!check(newX,newY)) break;
                if(newX == x2 && newY == y2) {
                    result = tmpData.depth + 1;
                    goto outside;
                }
                if(!visit[newX][newY]) {
                    visit[newX][newY] = true;
                    que.push(Data(tmpData.depth + 1,newX,newY));
                }
           }
        }
    }
    outside:
    cout << result << endl;
    return 0;
}
