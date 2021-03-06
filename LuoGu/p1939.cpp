#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MODDER = static_cast<int>(1e9 + 7);

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

template<typename T>
struct Matrix {
    int N,M;
    T **values;
    Matrix(int N,int M,T **copyValue) : N(N) , M(M) {
        values = new T*[N];
        for(int i = 0;i < N;i++) {
            values[i] = new T[M];
            memcpy(values[i],copyValue[i],sizeof(T) * M);
        }
    }

    Matrix operator * (const Matrix &otherMatrix)  const {
        int newN = this->N,newM = otherMatrix.M;
        T **resultValue = new T*[newN];
        for(int i = 0;i < newN;i++) {
            resultValue[i] = new T[newM];
            memset(resultValue[i],0,sizeof(T) * newM);
        }
        for(int i = 0;i < newN;i++) {
            for(int j = 0;j < newM;j++) {
                long long tmpValue = 0;
                for(int k = 0;k < this->M;k++) {
                    tmpValue = (tmpValue + static_cast<long long>(this->values[i][k]) * otherMatrix.values[k][j]) % MODDER;
                }
                resultValue[i][j] = tmpValue % MODDER;
            }
        }
        return Matrix(newN,newM,resultValue);
    }

    void print() {
        for(int i = 0;i < this->N;i++) {
            for(int j = 0;j < this->M;j++) {
                cout << values[i][j] << " ";
            }
            cout << endl;
        }
    }

    static Matrix pow(Matrix m,long long times) {
        T **values = new T*[m.N];
        for(int i = 0;i < m.N;i++) {
            values[i] = new T[m.M];
            memset(values[i],0,sizeof(int) * m.M);
            if(i < m.M) values[i][i] = 1;
        }
        Matrix result(m.N,m.M,values),base = m;
        while(times) {
            if(times & 1) result = result * base;
            base = base * base;
            times >>= 1;
        }
        return result;
    }

};

int values[3][3] = {{1,0,1},{0,1,0},{0,0,1}};

int main() {
    int n = 3;
    int **values = new int*[n];
    for(int i = 0;i < 3;i++) {
        values[i] = new int[n];
    }
    values[0][0] = 1; values[0][1] = 0; values[0][2] = 1; values[1][0] = 1; values[1][1] = 0; values[1][2] = 0; values[2][0] = 0; values[2][1] = 1; values[2][2] = 0;
    Matrix<int> m1(n,n,values);
    int T = read<int>();
    while(T--) {
        int k = read<int>();
        Matrix<int> m2 = Matrix<int>::pow(m1,k);
        printf("%d\n",m2.values[0][2]);
    }
    return 0;
}

