#include <cstdio>
#include <algorithm>

using namespace std;

struct Data{
    int leftCount;
    int value;
    Data(): leftCount(-1),value(-1) {}
    Data(int leftCount,int value): leftCount(leftCount),value(value) {}
};

Data myStack[100000];

int main(){
    int n;
    while(~scanf("%d",&n)){
        if(n == 0) break;
        long long result = 0;
        int pos = 0;
        for(int i = 0;i < n;i++){
            int value;
            scanf("%d",&value);
            Data tmpData(i,value);
            while(pos > 0 && myStack[pos - 1].value >= value){
                tmpData.leftCount = myStack[pos - 1].leftCount;
                long long tmpResult = i - myStack[pos - 1].leftCount;
                result = max(result,tmpResult * myStack[pos - 1].value);
                pos--;
            }
            myStack[pos++] = tmpData;
        }
        while(pos > 0){
            long long tmpResult = n - myStack[pos - 1].leftCount;
            result = max(result,tmpResult*myStack[pos - 1].value);
            pos--;
        }
        printf("%lld\n",result);
    }
    return 0;
}
