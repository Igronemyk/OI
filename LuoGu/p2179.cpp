#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <utility>

using namespace std;

const double EPS = 1e-12;
const int MAXN = 1e4 + 10;
const double INF = 1e5;

template<typename T>
T sqr(const T &val) {
    return val * val;
}

double s[MAXN],k[MAXN],v[MAXN],x[MAXN],Eu;
int n;

bool check1(int sign,double value,double mid) {
    return 2.00 * value * k[sign] * (mid - v[sign]) * sqr(mid) > 1;
}

double getX(int sign,double value) {
    double L = max(v[sign],0.00),R = INF;
    while(R - L > EPS) {
        double mid = (L + R) * 0.5;
        if(check1(sign,value,mid)) {
            R = mid;
        }else {
            L = mid;
        }
    }
    return L;
}

bool check(double value) {
    double result = 0;
    for(int i = 1;i <= n;i++) {
        x[i] = getX(i,value);
    }
    for(int i = 1;i <= n;i++) {
        result += k[i] * sqr(x[i] - v[i]) * s[i];
    }
    return result < Eu;
}

int main() {
    scanf("%d",&n);
    scanf("%lf",&Eu);
    for(int i = 1;i <= n;i++) {
        scanf("%lf%lf%lf",&s[i],&k[i],&v[i]);
    }
    double L = 0,R = INF;
    while(R - L > EPS) {
        double mid = (L + R) * 0.5;
        if(check(mid)) {
            R = mid;
        }else {
            L = mid;
        }
    }
    double result = 0;
    for(int i = 1;i <= n;i++) {
        result += s[i] / x[i];
    }
    printf("%lf\n",result);
    return 0;
}
