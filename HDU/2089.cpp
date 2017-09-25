#include <bits/stdc++.h>

using namespace std;


inline int amount(int x)
{
    if(x==0)return 1;
    string str;
    stringstream ss;
    ss<<x;
    ss>>str;
    int dp_map[10][10][2]= {0};
    memset(dp_map,0,sizeof(dp_map));
    int len=str.length();
    int maxn=str[0]-'0';
    for(int i=0; i<10; ++i)
    {
        if(i == 4) continue;
        dp_map[len - 1][i][0] = 1;
    }
    for(int i=len-2; i>=0; --i)
    {
        for(int j=0; j<10; ++j)
        {

            if(j == 4) continue;
            for(int k = 0;k < 10;k++){
                if(j == 6 && k == 2) continue;
                dp_map[i][j][0] += dp_map[i + 1][k][0];
            }
        }
    }
    dp_map[len - 1][str[len - 1] - '0'][1] = dp_map[len - 1][str[len - 1] - '0'][0];
    for(int i=len-2; i>=0; --i)
    {
        int j = str[i] - '0';
        if(j == 4) continue;
        for(int k = 0;k <= str[i + 1] - '0';k++){
            if(j == 6 && k == 2) continue;
            if(k == str[i + 1] - '0') dp_map[i][j][1] += dp_map[i + 1][k][1];
            else dp_map[i][j][1] += dp_map[i +1][k][0];
        }
    }
    int ans=0;
    for(int i=0; i<=maxn; ++i)
    {
        //cout<<dp_map[0][i][1]<<' ';
        ans+=dp_map[0][i][(i == maxn ? 1 : 0)];
    }
    //cout<<endl;
    return ans;
}


int main()
{
    int n,m;

    while(cin>>n>>m)
    {
        if(n==0&&m==0)break;
        cout<<amount(m)-amount(n-1)<<endl;
    }

}
