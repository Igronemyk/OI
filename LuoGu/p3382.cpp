#include <cstdio>

const double EPS = 1e-10;
const int INF = 0x3f3f3f3f;

int N;
double *values;

double calc(double x) {
    double result = 0,tmpX = 1;
    for(int i = N;i >= 0;i--) {
        result += values[i] * tmpX;
        tmpX *= x;
    }
    return result;
}

int main() {
    scanf("%d",&N);
    double l,r;
    values = new double[N + 1];
    scanf("%lf%lf",&l,&r);
    for(int i = 0;i < N + 1;i++) {
        scanf("%lf",&values[i]);
    }
    double result = -1,calVal = -INF;
    while(r - l > EPS) {
        double mid1 = l + (r - l) / 3;
        double mid2 = r - (r - l) / 3;
        double calVal1 = calc(mid1);
        double calVal2 = calc(mid2);
        if(calVal1 - calVal2 > EPS) {
            if(calVal1 > calVal) {
                result = mid1;
                calVal = calVal1;
            }
            r = mid2 - EPS;
        }else {
            if(calVal2 > calVal) {
                result = mid2;
                calVal = calVal2;
            }
            l = mid1 + EPS;
        }
    }
    printf("%.5lf\n",result);
    return 0;
}
