#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int value[4];

int main(){
    int T;
    cin >> T;
    while(T--){
        fill(value,value + 4,0);
        for(int i = 0;i < 4;i++){
            string tmpStr;
            cin >> tmpStr;
            value[i] = tmpStr.size();
            value[i] -= 2;
            for(string::iterator it = tmpStr.begin();it != tmpStr.end();it++){
                if(*it == '_') value[i]--;
            }
        }
        bool selectValue = false,stop = false;
        int result = 2;
        for(int i = 0;i < 4;i++){
            bool flag = true;
            for(int j = 0;j < 4;j++){
                if(i == j) continue;
                if(value[i] * 2 > value[j]){
                    flag = false;
                    break;
                }
            }
            if(flag){
                if(stop) break;
                if(!selectValue){
                    selectValue = true;
                }else{
                    stop = true;
                    result = 2;
                    break;
                }
                result = i;
            }
        }
        for(int i = 0;i < 4;i++){
            bool flag = true;
            for(int j = 0;j < 4;j++){
                if(i == j) continue;
                if(value[i] * 1.00 / 2 < value[j]){
                    flag = false;
                    break;
                }
            }
            if(flag){
                if(stop) break;
                if(!selectValue){
                    selectValue = true;
                }else if(result != i){
                    stop = true;
                    result = 2;
                    break;
                }
                result = i;
            }
        }
        cout << (char)('A' + result) << endl;
    }
    return 0;
}
