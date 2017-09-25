#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Query{
    int opt;
    int left;
    int right;
    Query() : opt(-1) ,left(-1),right(-1) {}
    Query(int opt,int left,int right) : opt(opt),left(left),right(right) {}
};

int values[200000];

Query querys[200000];

int indexs[100];

int main(){
    int n,q,m;
    cin >> n >> q >> m;
    for(int i = 0;i < n;i++) cin >> values[i];
    for(int i = 0;i < q;i++){
        int opt,left,right;
        cin >> opt >> left >> right;
        querys[i] = Query(opt,left - 1,right - 1);
    }
    for(int i = 0;i < m;i++) {
        cin >> indexs[i];
        indexs[i]--;
    }
    for(int i = 0;i < m;i++){
        for(int j = q - 1;j >= 0;j--){
            if(querys[j].left > indexs[i] || querys[j].right < indexs[i]) continue;
            if(querys[j].opt == 1){
                indexs[i]--;
                if(indexs[i] < querys[j].left) indexs[i] = querys[j].right;
            }else{
                int dis = indexs[i] - querys[j].left;
                indexs[i] = querys[j].right - dis;
            }
        }
        cout << values[indexs[i]] << " ";
    }
    return 0;
}
