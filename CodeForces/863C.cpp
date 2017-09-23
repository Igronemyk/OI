#include <iostream>
#include <algorithm>

using namespace std;

int stepA[3][3],stepB[3][3];

struct Data{
    long long scoreA;
    long long scoreB;
    long long index;
    Data() : scoreA(-1) ,scoreB(-1) , index(-1) {}
    Data(long long scoreA,long long scoreB,long long index) : scoreA(scoreA) , scoreB(scoreB) ,index(index) {}
};

int getResult(int a,int b){
    if(a == b){
        return 0;
    }else{
        switch(a){
        case 1:{
            switch(b){
                case 2: return -1;
                case 3: return 1;
            }
        }
        case 2:{
            switch(b){
                case 1: return 1;
                case 3: return -1;
            }
        }
        case 3:{
            switch(b){
                case 1: return -1;
                case 2: return 1;
            }
        }
        }
    }
}

bool visit[3][3];
Data mem[3][3];

int main(){
    long long k;
    int a,b;
    cin >> k >> a >> b;
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            cin >> stepA[i][j];
        }
    }
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            cin >> stepB[i][j];
        }
    }
    int doingA = a,doingB = b;
    long long countRounds = 0,scoreA = 0,scoreB = 0,repeatLength = -1,repeatScoreA = -1,repeatScoreB = -1;
    while(countRounds < k){
        switch(getResult(doingA,doingB)){
            case -1: {
                scoreB++;
                break;
            }
            case 0: {
                break;
            }
            case 1: {
                scoreA++;
                break;
            }
        }
        int newDoingA = stepA[doingA - 1][doingB - 1],newDoingB = stepB[doingA - 1][doingB - 1];
        doingA = newDoingA; doingB = newDoingB;
        countRounds++;
        if(visit[doingA - 1][doingB - 1]){
            repeatLength = countRounds - mem[doingA - 1][doingB - 1].index;
            repeatScoreA = scoreA - mem[doingA - 1][doingB - 1].scoreA;
            repeatScoreB = scoreB - mem[doingA - 1][doingB - 1].scoreB;
            break;
        }
        visit[doingA - 1][doingB - 1] = true;
        mem[doingA - 1][doingB - 1] = Data(scoreA,scoreB,countRounds);
    }
    if(repeatLength == -1){
        cout << scoreA << " " << scoreB << endl;
    }else{
        long long nowLeftRounds = k - countRounds;
        long long repeatTimes = nowLeftRounds / repeatLength;
        scoreA += repeatScoreA * repeatTimes;
        scoreB += repeatScoreB * repeatTimes;
        countRounds += repeatLength * repeatTimes;
        while(countRounds < k){
            switch(getResult(doingA,doingB)){
                case -1: {
                    scoreB++;
                    break;
                }
                case 0: {
                    break;
                }
                case 1: {
                    scoreA++;
                    break;
                }
            }
            int newDoingA = stepA[doingA - 1][doingB - 1],newDoingB = stepB[doingA - 1][doingB - 1];
            doingA = newDoingA; doingB = newDoingB;
            countRounds++;
        }
        cout << scoreA << " " << scoreB << endl;
    }
    return 0;

}
