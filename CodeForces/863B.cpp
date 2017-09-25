#include <iostream>
#include <algorithm>

using namespace std;

int values[1000];

int main(){
    int N;
    cin >> N;
    for(int i = 0;i < 2 * N;i++){
        cin >> values[i];
    }
    sort(values,values + 2 * N);
    for(int i = 0;i < 2 * N - 1;i++){
        for(int j = i + 1;j < 2 * N;j++){

        }
    }
    cout << result;
    return 0;
}


//1 2 100 200 201 202

//1 5 6 10

// 9 + 1 // 4 + 4
