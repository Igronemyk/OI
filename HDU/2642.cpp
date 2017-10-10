#include <cstring>
#include <iostream>

using namespace std;

struct ArrayTree{
    int **sum,size;

    ArrayTree(int size) : size(size) {
        sum = new int*[size + 1];
        for(int i = 0;i <= size;i++){
            sum[i] = new int[size + 1];
            memset(sum[i],0,sizeof(int) * (size + 1));
        }
    }

    void update(int x,int y,int value){
        for(int i = x;i <= size;i += lowbit(i)){
            for(int j = y;j <= size;j += lowbit(j)){
                sum[i][j] += value;
            }
        }
    }

    int getSum(int x,int y){
        int result = 0;
        for(int i = x;i > 0;i -= lowbit(i)){
            for(int j = y;j > 0;j -= lowbit(j)){
                result += sum[i][j];
            }
        }
        return result;
    }

    int lowbit(int value){
        return value & (-value);
    }

};

int main(){
    int M;
    while(cin >> M){
        ArrayTree tree(1001);
        bool **visit = new bool*[1002];
        for(int i = 0;i <= 1001;i++){
            visit[i] = new bool[1002];
            memset(visit[i],false,sizeof(bool) * 1002);
        }
        while(M--){
            char opt;
            cin >> opt;
            switch(opt){
                case 'B':{
                    int x,y;
                    cin >> x >> y;
                    x++;y++;
                    if(visit[x][y]) break;
                    tree.update(x,y,1);
                    visit[x][y] = true;
                    break;
                }
                case 'D':{
                    int x,y;
                    cin >> x >> y;
                    x++;y++;
                    if(!visit[x][y]) break;
                    tree.update(x,y,-1);
                    visit[x][y] = false;
                    break;
                }
                case 'Q':{
                    int x1,y1,x2,y2;
                    cin >> x1 >> x2 >> y1 >> y2;
                    x1++;y1++;x2++;y2++;
                    if(x1 > x2) swap(x1,x2);
                    if(y1 > y2) swap(y1,y2);
                    int result = tree.getSum(x2,y2) - tree.getSum(x1 - 1,y2) - tree.getSum(x2,y1 - 1) + tree.getSum(x1 - 1,y1 - 1);
                    cout << result << endl;
                    break;
                }
            }
        }
    }
    return 0;
}
