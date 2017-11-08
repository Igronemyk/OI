#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-')f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int BASE1 = 13;
const int BASE2 = 17;
const int MODDER1 = 10009;
const int MODDER2 = 10013;
const int MAX_LEN = 1510;

int hash(char *str,int base,int modder) {
    long long result = 0;
    int len = strlen(str);
    for(int i = 0;i < len;i++) {
        result = (result * base + str[i] - '0') % modder;
    }
    return static_cast<int>(result);
}

struct Data {
    int first,second;

    bool operator < (const Data &otherData) const {
        if(this->first != otherData.first) {
            return this->first < otherData.first;
        }else {
            return this->second < otherData.second;
        }
    }

    bool operator == (const Data &otherData) const {
        return this->first == otherData.first && this->second == otherData.second;
    }
};

int main() {
    int n = read<int>();
    Data *values = new Data[n];
    char *str = new char[MAX_LEN];
    for(int i = 0;i < n;i++) {
        scanf("%s",str);
        values[i].first = hash(str,BASE1,MODDER1);
        values[i].second = hash(str,BASE2,MODDER2);
    }
    sort(values,values + n);
    printf("%d\n",unique(values,values + n) - values);
    return 0;
}
