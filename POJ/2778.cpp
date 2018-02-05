#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

const int MAX_AC_NODE_SIZE = 150;
const int MAX_CHARSET_SIZE = 4;
const int BUFFER_SIZE = 15;
const int MODDER = 100000;

int getIndex(char c) {
    switch(c) {
        case 'A': {
            return 0;
        }
        case 'T': {
            return 1;
        }
        case 'C': {
            return 2;
        }
        case 'G': {
            return 3;
        }
        default: {
            return -1;
        }
    }
}

template<typename T>
struct Matrix {
    int N,M;
    T **values;
    Matrix(int N,int M,T **copyValues) : N(N) , M(M) {
        values = new T*[N];
        for(int i = 0;i < N;i++) {
            values[i] = new T[M];
            memcpy(values[i],copyValues[i],sizeof(T) * M);
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
            values[i][i] = 1;
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

struct ACNode {
    int trans[MAX_CHARSET_SIZE],fail;
    bool isEnd;
} an[MAX_AC_NODE_SIZE];

int acSize = 0;

struct ACAM {
    int root;

    static int newNode() {
        for(int i = 0;i < MAX_CHARSET_SIZE;i++) an[acSize].trans[i] = -1;
        an[acSize].fail = -1;
        an[acSize].isEnd = false;
        return acSize++;
    }

    ACAM() {
        root = newNode();
    }

    void insert(char *str) {
        int now = root;
        for(int i = 0;str[i];i++) {
            int index = getIndex(str[i]);
            if(an[now].trans[index] == -1) {
                an[now].trans[index] = newNode();
            }
            now = an[now].trans[index];
        }
        an[now].isEnd = true;
    }

    void build() {
        queue<int> que;
        an[root].fail = root;
        for(int i = 0;i < MAX_CHARSET_SIZE;i++) {
            if(an[root].trans[i] == -1) {
                an[root].trans[i] = root;
            }else {
                an[an[root].trans[i]].fail = root;
                que.push(an[root].trans[i]);
            }
        }
        while(!que.empty()) {
            int tmpNode = que.front();
            que.pop();
            for(int i = 0;i < MAX_CHARSET_SIZE;i++) {
                if(an[tmpNode].trans[i] == -1) {
                    an[tmpNode].trans[i] = an[an[tmpNode].fail].trans[i];
                }else {
                    an[an[tmpNode].trans[i]].fail = an[an[tmpNode].fail].trans[i];
                    if(an[an[an[tmpNode].trans[i]].fail].isEnd) {
                        an[an[tmpNode].trans[i]].isEnd = true;
                    }
                    que.push(an[tmpNode].trans[i]);
                }
            }
        }
    }
};


int main() {
    int m,n;
    scanf("%d%d",&m,&n);
    ACAM acMachine;
    char *buffer = new char[BUFFER_SIZE];
    while(m--) {
        scanf("%s",buffer);
        acMachine.insert(buffer);
    }
    acMachine.build();
    int size = acSize;
    int **values = new int*[size];
    for(int i = 0;i < size;i++) {
        values[i] = new int[size];
        memset(values[i],0,sizeof(int) * size);
    }
    for(int i = 0;i < acSize;i++) {
        if(an[i].isEnd) continue;
        for(int j = 0;j < MAX_CHARSET_SIZE;j++) {
            if(an[an[i].trans[j]].isEnd) continue;
            values[i][an[i].trans[j]]++;
        }
    }
    Matrix<int> matrix(size,size,values);
    matrix = Matrix<int>::pow(matrix,n);
    int resultCount = 0;
    for(int i = 0;i < size;i++) {
        resultCount = (resultCount + matrix.values[0][i]) % MODDER;
    }
    printf("%d\n",resultCount);
    return 0;
}
