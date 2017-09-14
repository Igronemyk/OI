
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int n, m, dp[105][80][80];      //dp[i][j][k]表示第i行的状态为j，第i-1行的状态为k时能放炮兵的最大数量

int nState, state[80], num[80]; //10位二进制位中各个1之间的距离不小于2，这样的数只有60个。
                                //依次存放在state[]中，num[i]表示state[i]中1的个数

//在小于2^m的数中找1之间的距离不小于2的数，保存在state[]中
void init()
{
    int k = 1 << m;
    nState = 0;
    for (int i = 0; i < k; i++)
        if ( (i&(i<<1)) == 0 && (i&(i<<2)) == 0 )
        {
            state[nState] = i;
            num[nState] = 0;
            int j = i;
            while (j)
            {
                num[nState] += j % 2;
                j /= 2;
            }
            nState++;
        }
}
        for (int j = 0; j < nState; j++)
        {
            if ( (state[j] & row[0]) != state[j] )
                continue;
            for (int k = 0; k < nState; k++)
                dp[0][j][k] = num[j];
        }

        // 计算dp[1]
        if (n > 1)
        for (int j = 0; j < nState; j++)
        {
            if ( (state[j] & row[1]) != state[j] )
                continue;
            for (int k = 0; k < nState; k++)
            {
                if ( (state[j] & state[k]) == 0 )
                    dp[1][j][k] = dp[0][k][0] + num[j];
            }
        }

        // 计算dp[>1]
        for (int i = 2; i < n; i++)
        {
            for (int j = 0; j < nState; j++)
            {
                if ( (state[j] & row[i]) != state[j] )
                    continue;
                for (int k = 0; k < nState; k++)
                {
                    if ( state[j] & state[k] )
                        continue;
                    for (int h = 0; h < nState; h++)
                    {
                        if ( state[j] & state[h] )
                            continue;
                        if ( dp[i-1][k][h] > dp[i][j][k] )
                            dp[i][j][k] = dp[i-1][k][h];
                    }
                    dp[i][j][k] += num[j];
                }
            }
        }

        // 在dp[n-1]中找最大值
        int max = 0;
        for (int j = 0; j < nState; j++)
        {
            for (int k = 0; k < nState; k++)
                if (max < dp[n-1][j][k])
                    max = dp[n-1][j][k];
        }

        printf("%d\n", max);
                for(int i = 0;i < n;i++){
            for(int j = 0;j < nState;j++){
                for(int k = 0;k < nState;k++){
                    printf("dp[%d][%d][%d]=%d\n",i,j,k,dp[i][j][k]);
                }
            }
        }
    }
}
