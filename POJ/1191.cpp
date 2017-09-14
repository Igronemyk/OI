#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <memory.h>

using namespace std;

int sum[9][9],dp[15][9][9][9][9];

int myPow(int value){
    return value * value;
}

double myPow(double value){
    return value * value;
}


int main(){
    ios::sync_with_stdio(false);
    int n;
    while(cin >> n){
        memset(sum,0,sizeof(sum));
        memset(dp,0,sizeof(dp));
        int sumAll = 0;
        for(int i = 1;i <= 8;i++){
            for(int j = 1;j <= 8;j++){
                int tmpValue;
                cin >> tmpValue;
                sumAll += tmpValue;
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i -1][j - 1] + tmpValue;
            }
        }
        for(int x1 = 1;x1 <= 8;x1++){
            for(int y1 = 1;y1 <= 8;y1++){
                for(int x2 = x1;x2 <= 8;x2++){
                    for(int y2 = y1;y2 <= 8;y2++){
                        dp[0][x1][y1][x2][y2] = myPow(sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 -1][y1 - 1]);
                    }
                }
            }
        }
        for(int i = 1;i < n;i++){
            for(int x1 = 1;x1 <= 8;x1++){
                for(int y1 = 1;y1 <= 8;y1++){
                    for(int x2 = x1;x2 <= 8;x2++){
                        for(int y2 = y1;y2 <= 8;y2++){
                            dp[i][x1][y1][x2][y2] = 40960001;
                            for(int doing = x1;doing < x2;doing++){
                                dp[i][x1][y1][x2][y2] = min(dp[i][x1][y1][x2][y2],dp[0][x1][y1][doing][y2] + dp[i - 1][doing + 1][y1][x2][y2]);
                                dp[i][x1][y1][x2][y2] = min(dp[i][x1][y1][x2][y2],dp[i - 1][x1][y1][doing][y2] + dp[0][doing + 1][y1][x2][y2]);
                            }
                            for(int doing = y1;doing < y2;doing++){
                                dp[i][x1][y1][x2][y2] = min(dp[i][x1][y1][x2][y2],dp[0][x1][y1][x2][doing] + dp[i - 1][x1][doing + 1][x2][y2]);
                                dp[i][x1][y1][x2][y2] = min(dp[i][x1][y1][x2][y2],dp[i - 1][x1][y1][x2][doing] + dp[0][x1][doing + 1][x2][y2]);
                            }
                        }
                    }
                }
            }
        }
        double result = ((double)(dp[n -1][1][1][8][8]*1.0)) / n - myPow(((double)(sumAll*1.0))/n);
        cout << setprecision(3) << fixed << sqrt(result) << endl;
    }
    return 0;
}
/*
#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <memory.h>

using namespace std;

int data[9][9];
int sum[9][9];
double dp[14][9][9][9][9];

double count(int x1, int y1, int x2, int y2)
{
    double ans = (double)(sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1]);

    return ans*ans;
}

int main()
{
    int n, total=0;
    cin>>n;
    for(int i=1; i<=8; ++i)
      for(int j=1; j<=8; ++j)
      {
            cin>>data[i][j];
            sum[i][j] = sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1] + data[i][j];
            total += data[i][j];
        }
    for(int x1=1; x1<=8; ++x1)
     for(int y1=1; y1<=8; ++y1)
      for(int x2=x1; x2<=8; ++x2)
          for(int y2=y1; y2<=8; ++y2)
             dp[0][x1][y1][x2][y2] = count(x1,y1,x2,y2);
    for(int k=1; k<n; ++k)
     for(int x1=1; x1<=8; ++x1)
      for(int y1=1; y1<=8; ++y1)
       for(int x2=x1; x2<=8; ++x2)
          for(int y2=y1; y2<=8; ++y2)
          {
                int t;
                dp[k][x1][y1][x2][y2] = (double)(1<<30);
                for(t=x1; t<x2; ++t)
                {
                    dp[k][x1][y1][x2][y2] = min(dp[k][x1][y1][x2][y2], dp[0][x1][y1][t][y2]+dp[k-1][t+1][y1][x2][y2]);
                    dp[k][x1][y1][x2][y2] = min(dp[k][x1][y1][x2][y2], dp[k-1][x1][y1][t][y2]+dp[0][t+1][y1][x2][y2]);
                }

                for(t=y1; t<y2; ++t)
                {
                    dp[k][x1][y1][x2][y2] = min(dp[k][x1][y1][x2][y2], dp[0][x1][y1][x2][t]+dp[k-1][x1][t+1][x2][y2]);
                    dp[k][x1][y1][x2][y2] = min(dp[k][x1][y1][x2][y2], dp[k-1][x1][y1][x2][t]+dp[0][x1][t+1][x2][y2]);
                }
            }
    double ans = dp[n-1][1][1][8][8]*1.0/n - ((double)total*1.0/n)*((double)total*1.0/n);
    cout<<setprecision(3)<<fixed<<sqrt(ans)<<endl;
    return 0;
}
*/
