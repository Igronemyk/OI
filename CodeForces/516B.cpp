#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 2010;
const int dx[4] = {-1,0,1,0},dy[4] = {0,1,0,-1};

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

char graph[MAXN][MAXN];
int degree[MAXN][MAXN];

int main() {
    int N = read<int>(),M = read<int>();
    queue<pair<int,int> > que;
    for(int i = 1;i <= N;i++) {
        scanf("%s",graph[i] + 1);
    }
    for(int i = 1;i <= N;i++) {
        for(int j = 1;j <= M;j++) {
            if(graph[i][j] != '.') continue;
            for(int k = 0;k < 4;k++) {
                int distX = i + dx[k],distY = j + dy[k];
                if(graph[distX][distY] == '.') {
                    degree[i][j]++;
                }
            }
            if(degree[i][j] == 1) {
                que.push(make_pair(i,j));
            }
        }
    }
    while(!que.empty()) {
        pair<int,int> now = que.front();
        que.pop();
        int x = now.first,y = now.second;
        if(graph[x][y] != '.') continue;
        bool checkSign = false;
        int checkX = -1,checkY = -1;
        for(int i = 0;i < 4;i++) {
            int distX = x + dx[i],distY = y + dy[i];
            if(graph[distX][distY] == '.') {
                checkSign = true;
                checkX = distX;
                checkY = distY;
                break;
            }
        }
        if(!checkSign) {
            printf("Not unique\n");
            return 0;
        }
        if(y == checkY) {
            if(x + 1 == checkX) {
                graph[x][y] = '^';
                graph[checkX][y] = 'v';
            }else if(checkX + 1 == x) {
                graph[checkX][y] = '^';
                graph[x][y] = 'v';
            }
        }else {
            if(y + 1 == checkY) {
                graph[x][y] = '<';
                graph[x][checkY] = '>';
            }else if(checkY + 1 == y) {
                graph[x][checkY] = '<';
                graph[x][y] = '>';
            }
        }
        degree[x][y] = 0;
        degree[checkX][checkY] = 0;
        for(int i = 0;i < 4;i++) {
            int distX = checkX + dx[i],distY = checkY + dy[i];
            if(graph[distX][distY] != '.') continue;
            if(degree[distX][distY] == 0) continue;
            degree[distX][distY]--;
            if(degree[distX][distY] == 1) {
                que.push(make_pair(distX,distY));
            }
        }
    }
    for(int i = 1;i <= N;i++) {
        for(int j = 1;j <= M;j++) {
            if(graph[i][j] != '.') continue;
            printf("Not unique\n");
            return 0;
        }
    }
    for(int i = 1;i <= N;i++) {
        printf("%s\n",graph[i] + 1);
    }
    return 0;
}
