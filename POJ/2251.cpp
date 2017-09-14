#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f;

int L,R,C;

char ***graph;
bool ***visit;

int moveTo[6][3] = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};

struct Node{
    int l,r,c,depth;
    Node() : l(-1),r(-1),c(-1),depth(-1) {}
    Node(int l,int r,int c,int depth) : l(l) ,r(r),c(c),depth(depth) {}
};

bool checkMoveTo(int newL,int newR,int newC,int id){
    if(newL >=0 && newL < L && newR >=0 && newR < R && newC>=0 && newC<C && !visit[newL][newR][newC] && graph[newL][newR][newC] != '#') return true;
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    while(true){
        cin >> L >> R >> C;
        if(L == 0 && R == 0 && C == 0) break;
        graph = new char**[L];
        visit = new bool**[L];
        for(int i = 0;i < L;i++){
            graph[i] = new char*[R];
            visit[i] = new bool*[R];
            for(int j = 0;j < R;j++){
                graph[i][j] = new char[C];
                visit[i][j] = new bool[C];
                fill(visit[i][j],visit[i][j] + C,false);
            }
        }
        int startL,startR,startC;
        for(int i = 0;i < L;i++){
            for(int j = 0;j < R;j++){
                string s;
                cin >> s;
                int tmpSize = static_cast<int>(s.size());
                for(int k = 0;k < tmpSize;k++){
                    graph[i][j][k] = s[k];
                    if(s[k] == 'S'){
                        startL = i;
                        startR = j;
                        startC = k;
                    }
                }
            }
        }
        queue<Node> que;
        visit[startL][startR][startC] = true;
        que.push(Node(startL,startR,startC,0));
        bool solved = false;
        int ans = -1;
        while(!solved && !que.empty()){
            Node tmp = que.front();
            que.pop();
            for(int i = 0;i < 6;i++){
                int newL = tmp.l + moveTo[i][0];
                int newR = tmp.r + moveTo[i][1];
                int newC = tmp.c + moveTo[i][2];
                if(checkMoveTo(newL,newR,newC,i)){
                    visit[newL][newR][newC] = true;
                    Node now(newL,newR,newC,tmp.depth + 1);
                    que.push(now);
                    if(graph[newL][newR][newC] == 'E'){
                        solved = true;
                        ans = now.depth;
                        break;
                    }
                }
            }
        }
        if(ans == -1){
            cout << "Trapped!" << endl;
        }else{
            cout << "Escaped in " << ans << " minute(s)." << endl;
        }
    }
    return 0;
}
