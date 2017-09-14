#include <bits/stdc++.h>

using namespace std;

struct Data{
    int k,b;
    Data() : k(-1) ,b(-1) {}
    Data(int k,int b) : k(k) , b(b) {}
    double solve(double x){
        return k * x + b;
    }
};

Data d1,d2;

bool checkValue(pair<double,double> value){
    double y1 = d1.solve(value.first),y2 = d2.solve(value.first);
    if(y1 < y2){
        double tmp = y1;
        y1 = y2;
        y2 = tmp;
    }
    return (value.second >= y2 && value.second <= y1);
}

pair<double,double> getPoint(Data &data1,Data &data2){
    int tmp1 = data1.b - data2.b;
    int tmp2 = data2.k - data1.k;
    double x = tmp1 / tmp2;
    return make_pair(x,data1.solve(x));
}

int main(){
    ios::sync_with_stdio(false);
    int k,a,b;
    cin >> k >> a >> b;
    d1 = Data(k,a);
    d2 = Data(k,b);
    int n;
    cin >> n;
    Data *datas = new Data[n];
    long long result = 0;
    for(int i = 0;i < n;i++){
        int tmpK,tmpB;
        cin >> tmpK >> tmpB;
        datas[i] = Data(tmpK,tmpB);
        for(int j = 0;j < i;j++){
            if(datas[i].k != datas[j].k && checkValue(getPoint(datas[i],datas[j]))) result++;
        }
    }
    cout << result << endl;
    return 0;
}
