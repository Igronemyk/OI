#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>

using namespace std;

const int MAX_CHARSET_SIZE = 10;
const int FIRST_CHAR = 'A';
const int MAX_AC_NODE_SIZE = 110;
const double EPS = 1e-10;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct ACNode {
    int trans[MAX_CHARSET_SIZE],fail;
    bool isEnd;

    ACNode() {
        memset(trans,-1,sizeof(trans));
        fail = -1;
        isEnd = false;
    }
} an[MAX_AC_NODE_SIZE];

int acSize = 0;

struct ACAM {
    int root;

    ACAM() : root(newNode()) { }

    static int newNode() {
        an[acSize++] = ACNode();
        return acSize - 1;
    }

    int insert(char *str) {
        int now = root;
        for(int i = 0;str[i];i++) {
            int index = str[i] - FIRST_CHAR;
            if(an[now].trans[index] == -1) {
                an[now].trans[index] = newNode();
            }
            now = an[now].trans[index];
        }
        an[now].isEnd = true;
        return now;
    }

    void build() {
        queue<int> que;
        an[root].fail = root;
        for(int i = 0;i < MAX_CHARSET_SIZE;i++) {
            if(an[root].trans[i] != -1) {
                an[an[root].trans[i]].fail = root;
                que.push(an[root].trans[i]);
            }else {
                an[root].trans[i] = root;
            }
        }
        while(!que.empty()) {
            int now = que.front();
            que.pop();
            for(int i = 0;i < MAX_CHARSET_SIZE;i++) {
                if(an[now].trans[i] == -1) {
                    an[now].trans[i] = an[an[now].fail].trans[i];
                }else {
                    an[an[now].trans[i]].fail = an[an[now].fail].trans[i];
                    if(an[an[an[now].fail].trans[i]].isEnd) {
                        an[an[now].trans[i]].isEnd = true;
                    }
                    que.push(an[now].trans[i]);
                }
            }
        }
    }

};

bool gauss(double **values,int size) {
    for(int i = 0;i < size;i++) {
        int nowSelect = i;
        for(int j = i + 1;j < size;j++) {
            if(fabs(values[j][i]) > fabs(values[nowSelect][i])) {
                nowSelect = j;
            }
        }
        if(fabs(values[nowSelect][i]) <= EPS) {
            return false;
        }
        if(nowSelect != i) {
            swap(values[nowSelect],values[i]);
        }
        for(int j = 0;j < size;j++) {
            if(i == j) continue;
            double tmpValue = values[j][i] / values[i][i];
            for(int k = size;k >= i;k--) {
                values[j][k] -= values[i][k] * tmpValue;
            }
        }
    }
    return true;
}

int main() {
    int n = read<int>(),l = read<int>(),m = read<int>();
    double *weights = new double[m];
    for(int i = 0;i < m;i++) {
        double p = read<int>(),q = read<int>();
        weights[i] = p / q;
    }
    char *buffer = new char[l + 1];
    ACAM acam;
    int fail = 0,*signs = new int[n];
    for(int i = 0;i < n;i++) {
        scanf("%s",buffer);
        for(int j = 0;j < l;j++) {
            if(weights[buffer[j] - FIRST_CHAR] < EPS) {
                fail++;
                break;
            }
        }
        signs[i] = acam.insert(buffer);
    }
    acam.build();
    if(fail == n) {
        for(int i = 0;i < n;i++) {
            printf("0.00\n");
        }
        return 0;
    }
    int size = acSize;
    double **matrix = new double*[size];
    for(int i = 0;i < size;i++) {
        matrix[i] = new double[size + 1];
        fill(matrix[i],matrix[i] + (size + 1),0.00);
    }
    for(int i = 0;i < size;i++) {
        matrix[i][i] = -1.00;
        if(an[i].isEnd) continue;
        for(int j = 0;j < m;j++) {
            matrix[an[i].trans[j]][i] += weights[j];
        }
    }
    matrix[0][size] = -1.00;
    gauss(matrix,size);
    for(int i = 0;i < n;i++) {
        double result = matrix[signs[i]][size] / matrix[signs[i]][signs[i]];
        if(fabs(result) <= EPS) {
            printf("0.00\n");
        }else {
            printf("%.2lf\n",result);
        }
    }
    return 0;
}
