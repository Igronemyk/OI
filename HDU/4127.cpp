#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int N,graph[8][8],vis[8][8],nextX[] = {0,1,0,-1},nextY[] = {1,0,-1,0},maxDepth;

inline int read(){
    int result = 0,f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-')f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

void fillFlood(int x,int y,int color){
    vis[x][y] = 1;
    for(int i = 0;i < 4;i++){
        int newX = x + nextX[i],newY = y + nextY[i];
        if(newX >= N || newX < 0 || newY >= N || newY < 0) continue;
        if(vis[newX][newY] == 1) continue;
        if(graph[newX][newY] == color) fillFlood(newX,newY,color);
        else vis[newX][newY] = 2;
    }
}

int getCnt(int color){
    int result = 0;
    for(int i = 0;i < N;i++){
        for(int j = 0;j < N;j++){
            if(vis[i][j] == 2 && graph[i][j] == color){
                result++;
                fillFlood(i,j,color);
            }
        }
    }
    return result;
}

int getH(){
    bool flag[6];
    memset(flag,0,sizeof(flag));
    int result = 0;
    for(int i = 0;i < N;i++){
        for(int j = 0;j < N;j++){
            if(vis[i][j] != 1 && !flag[graph[i][j]]){
                result++;
                flag[graph[i][j]] = true;
            }
        }
    }
    return result;
}

bool IDAStar(int depth){
    if(depth == maxDepth) return getH() == 0;
    if(depth + getH() > maxDepth) return false;
    int tmpSave[8][8];
    for(int i = 0;i < 6;i++){
        memcpy(tmpSave,vis,sizeof(vis));
        if(getCnt(i) == 0) continue;
        if(IDAStar(depth + 1)) return true;
        memcpy(vis,tmpSave,sizeof(vis));
    }
    return false;
}

int main(){
    while(~scanf("%d",&N)){
        if(N == 0) break;
        for(int i = 0;i < N;i++){
            for(int j = 0;j < N;j++){
                graph[i][j] = read();
            }
        }
        memset(vis,0,sizeof(vis));
        fillFlood(0,0,graph[0][0]);
        maxDepth = getH();
        while(true){
            if(IDAStar(0)) break;
            maxDepth++;
        }
        printf("%d\n",maxDepth);
    }
    return 0;
}


