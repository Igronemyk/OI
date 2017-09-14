#include <bits/stdc++.h>

using namespace std;

class BigInteger{
private:
    bool isNegative;
    int length;
    int nowSize;
    int *value;
    void reSize(){
        int *newValue = new int[nowSize * 2];
        copy(value,value + nowSize,newValue);
        delete []value;
        value = newValue;
    }
    void checkIsNeedResize(){
        if(length == nowSize){
            reSize();
        }
    }
public:
    BigInteger(string s){
        int pos = 0;
        if(){

        }
    }

    BigInteger(string s,int toSize){

    }


};

int main(){

    return 0;
}
