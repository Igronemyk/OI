#include<cstdio>
#include<cstring>
#include<cmath>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Vector2d {

    double x_;
    double y_;

    Vector2d(double x, double y):x_(x), y_(y){}
    Vector2d():x_(0), y_(0){}

    double CrossProduct(const Vector2d vec)
    {
        return x_*vec.y_ - y_*vec.x_;
    }

    double DotProduct(const Vector2d vec)
    {
        return x_ * vec.x_ + y_ * vec.y_;
    }

    Vector2d Minus(const Vector2d vec) const
    {
        return Vector2d(x_ - vec.x_, y_ - vec.y_);
    }

    bool operator < (const Vector2d &otherVec) const {
        if(x_ != otherVec.x_) {
            return x_ < otherVec.x_;
        }
        return y_ < otherVec.y_;
    }
};

struct Triangle {
    Vector2d pointA_, pointB_, pointC_;

    Triangle(Vector2d point1, Vector2d point2, Vector2d point3) :pointA_(point1), pointB_(point2), pointC_(point3) { }

    double ComputeTriangleArea() {
        Vector2d AB = pointB_.Minus(pointA_);
        Vector2d BC = pointC_.Minus(pointB_);
        return fabs(AB.CrossProduct(BC) / 2.0);
    }

    bool IsPointInTriangle(const Vector2d pointP) {
        Vector2d PA = pointA_.Minus(pointP);
        Vector2d PB = pointB_.Minus(pointP);
        Vector2d PC = pointC_.Minus(pointP);
        double t1 = PA.CrossProduct(PB);
        double t2 = PB.CrossProduct(PC);
        double t3 = PC.CrossProduct(PA);
        return t1*t2 >= 0 && t1*t3 >= 0;
    }
};

int main() {
    int n = read<int>();
    pair<Vector2d,int> *vecs = new pair<Vector2d,int>[n];
    for(int i = 0;i < n;i++) {
        vecs[i].first.x_ = read<int>();
        vecs[i].first.y_ = read<int>();
        vecs[i].second =i + 1;
    }
    sort(vecs,vecs + n);
    Triangle tri(vecs[0].first,vecs[1].first,vecs[2].first);
    printf("%d %d ",vecs[0].second,vecs[1].second);
    for(int i = 2;i < n;i++) {
        tri.pointC_ = vecs[i].first;
        if(tri.ComputeTriangleArea() != 0) {
            printf("%d\n",vecs[i].second);
            break;
        }
    }
    return 0;
}
