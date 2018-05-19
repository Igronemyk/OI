#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 2e5 + 10;

struct Info {
    long long hp,damage;

    Info() : hp(0) , damage(0) { }

    Info(long long hp,long long damage) : hp(hp) , damage(damage) { }

    bool operator < (const Info &otherInfo) const {
        return hp - damage > otherInfo.hp - otherInfo.damage;
    }

} infos[MAXN];

long long sumValues[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,a,b;
    cin >> n >> a >> b;
    if(b == 0) {
        long long result = 0;
        for(int i = 0;i < n;i++) {
            long long hp,damage;
            cin >> hp >> damage;
            result += damage;
        }
        cout << result << endl;
        return 0;
    }
    long long bigDamageSum = 0;
    for(int i = 1;i <= n;i++) {
        long long hp,damage;
        cin >> hp >> damage;
        infos[i] = Info(hp,damage);
        bigDamageSum += damage;
    }
    sort(infos + 1,infos + n + 1);
    for(int i = 1;i <= n;i++) {
        sumValues[i] = sumValues[i - 1] + max(0LL,infos[i].hp - infos[i].damage);
    }
    long long result = 0;
    {
        long long tmpResult = 0;
        tmpResult += sumValues[min(n,b)];
        tmpResult += bigDamageSum;
        result = max(result,tmpResult);
    }
    for(int i = 1;i <= n;i++) {
        Info tmpInfo = infos[i];
        long long tmpResult = tmpInfo.hp;
        for(int j = 0;j < a;j++) {
            tmpResult *= 2;
        }
        int cnt = b - 1;
        if(cnt <= i - 1) {
            tmpResult += sumValues[cnt];
        }else {
            tmpResult += sumValues[i - 1];
            cnt -= i - 1;
            tmpResult += sumValues[min(n,i + 1 + cnt - 1)] - sumValues[i];
        }
        tmpResult += bigDamageSum - tmpInfo.damage;
        result = max(result,tmpResult);
    }
    cout << result << endl;
    return 0;
}
