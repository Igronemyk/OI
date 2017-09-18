#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 362880;

int factorials[9] = {1,1,2,6,24,120,720,5040,40320},next[] = {-1,1,-3,3},pow[9] = {100000000,10000000,1000000,100000,10000,1000,100,10,1};//l,r,u,d
bool visit[MAX];

char turnToOpt(int opt){
    switch(opt){
        case 0:return 'l';
        case 1:return 'r';
        case 2:return 'u';
        case 3:return 'd';
    }
}

int hash(int num){
    int permuation[10];
    for(int i = 0;i < 9;i++){
        permuation[9 - i - 1] = num%10;
        num/=10;
    }
    int result = 0;
    for(int i = 1;i < 9;i++){
        int tmpResult = 0;
        for(int j = 0;j < i;j++){
            if(permuation[j] > permuation[i]) tmpResult++;
        }
        result += tmpResult * factorials[i];
    }
    return result;
}

bool canSolve(int num) {
    int permuation[10];
    for(int i = 0;i < 9;i++){
        permuation[9 - i - 1] = num%10;
        num/=10;
    }
    int result = 0;
    for(int i = 1; i < 9; i++) {
        if(permuation[i] == 9) continue;
        for(int j = 0; j < i; j++) {
            if(permuation[j] == 9) continue;
            if(permuation[j] > permuation[i]) result++;
        }
    }
    return !(result % 2);
}

struct State{
    int num;
    int pre;
    int opt;
    int pos;
};

State que[MAX];
int head = 0,tail = 0;

void printResult(int doing){
    if(que[doing].opt == -1){
        return;
    }
    printResult(que[doing].pre);
    cout << turnToOpt(que[doing].opt);
}

void addValue(int num,int a,int b,int opt){
    int n1 = num/pow[a] %10,n2 = num/pow[b] % 10;
    num = num - (n1 - n2)*pow[a] + (n1 - n2)*pow[b];
    int hashcode = hash(num);
    if(!visit[hashcode]){
        visit[hashcode] = true;
        que[tail].num = num;
        que[tail].pre = head;
        que[tail].opt = opt;
        que[tail++].pos = b;
    }
}

int main(){
    int num = 0;
    int pos = -1;
    for(int i = 0;i < 9;i++){
        char tmpChar;
        cin >> tmpChar;
        if(tmpChar == 'x'){
            num = num * 10 + 9;
            pos = i;
        }else{
            num = num * 10 + tmpChar - '0';
        }
    }
    if(!canSolve(num)){
        cout << "unsolvable" << endl;
        return 0;
    }
    int result = -1;
    que[tail].num = num;
    que[tail].pre = -1;
    que[tail].opt = -1;
    que[tail++].pos = pos;
    visit[hash(num)] = true;
    while(head < tail){
        if(que[head].num == 123456789) {
            result = head;
            break;
        }
        for(int i = 0;i < 4;i++){
            int newPos = que[head].pos + next[i];
            if(newPos >= 9 || newPos < 0 || ((next[i] == 1 || next[i] == -1) && newPos/3 != que[head].pos/3)) continue;
            addValue(que[head].num,que[head].pos,newPos,i);
        }
        head++;
    }
    printResult(result);
    cout << endl;
    return 0;
}
