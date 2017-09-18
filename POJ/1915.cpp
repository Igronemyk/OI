#include <cstdio>
#include <functional>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

bool vis[300][300];
int nextX[] = {-1,-1,-2,-2,1,1,2,2},nextY[] = {-2,2,-1,1,-2,2,-1,1};
inline int read(){
    int result = 0,f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Data{
    int x,y,depth;
    Data(int x,int y,int depth) : x(x),y(y),depth(depth) {}
};

int main(){
    int T = read();
    while(T--){
        memset(vis,0,sizeof(vis));
        int length = read();
        int startX = read(),startY = read(),endX = read(),endY = read();
        queue<Data> que;
        que.push(Data(startX,startY,0));
        vis[startX][startY] = true;
        int result = 0;
        while(!que.empty()){
            Data tmpData = que.front();
            que.pop();
            if(tmpData.x == endX && tmpData.y == endY){
                result = tmpData.depth;
                break;
            }
            for(int i = 0;i < 8;i++){
                int newX = tmpData.x + nextX[i],newY = tmpData.y + nextY[i];
                if(newX >= length || newX < 0 || newY >= length || newY < 0) continue;
                if(!vis[newX][newY]){
                    vis[newX][newY] = true;
                    que.push(Data(newX,newY,tmpData.depth + 1));
                }
            }
        }
        printf("%d\n",result);
    }
    return 0;
}
