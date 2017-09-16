#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

const int INF = 0x3f3f3f3f;

int nums,depth;

int turnCharToInt(char c){
    switch(c){
        case 'A':return 0;
        case 'C':return 1;
        case 'G':return 2;
        case 'T':return 3;
    }
}

bool dfs(int nowDepth,int *nowLen,int **graph,int *sizes){
    if(nowDepth > depth) return false;
    int maxLeft = 0;
    for(int i = 0;i < nums;i++){
        int tmpLeft = sizes[i] - nowLen[i];
        maxLeft = max(maxLeft,tmpLeft);
    }
    if(maxLeft == 0) return true;
    if(nowDepth + maxLeft > depth) return false;
    for(int i = 0;i < 4;i++){
        bool canUpdate = false,result = false;
        stack<int> stk;
        for(int j = 0;j < nums;j++){
            if(graph[j][nowLen[j]] == i){
                nowLen[j]++;
                if(!canUpdate) canUpdate = true;
                stk.push(j);
            }
        }
        if(canUpdate){
            result = dfs(nowDepth + 1,nowLen,graph,sizes);
        }
        while(!stk.empty()){
            nowLen[stk.top()]--;
            stk.pop();
        }
        if(result) return true;
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    while(n--){
        cin >> nums;
        int **graph = new int*[nums];
        int *sizes = new int[nums];
        int sum = 0,minValue = INF;
        for(int i = 0;i < nums;i++){
            graph[i] = new int[nums];
            string tmpStr;
            cin >> tmpStr;
            int tmpSize = static_cast<int>(tmpStr.size());
            for(int j = 0;j < tmpSize;j++){
                graph[i][j] = turnCharToInt(tmpStr[j]);
            }
            sum += tmpSize;
            minValue = min(minValue,tmpSize);
            sizes[i] = tmpSize;
        }
        int *len = new int[nums];
        fill(len,len + nums,0);
        for(int i = minValue;i <= sum;i++){
            depth = i;
            if(dfs(0,len,graph,sizes)) {
                cout << i << endl;
                break;
            }
        }
    }
    return 0;
}
