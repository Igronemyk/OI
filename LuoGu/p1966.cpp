#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MODDER = 99999997;

template<typename T>
inline T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Data{
    int value;
    int sign;
    Data() : value(-1),sign(-1){}
    Data(int value,int sign) : value(value) ,sign(sign) { }
    bool operator < (const Data otherData) const {
        return this->value < otherData.value;
    }
};

int result = 0;

void merge(int *value,int left,int mid,int right,int *tmp){
    int tmpPos = left,leftPos = left,rightPos = mid;
    while(leftPos < mid && rightPos < right){
        if(value[leftPos] > value[rightPos]){
            tmp[tmpPos++] = value[rightPos++];
            result += mid - leftPos;
            result %= MODDER;
        }else{
            tmp[tmpPos++] = value[leftPos++];
        }
    }
    while(leftPos < mid) tmp[tmpPos++] = value[leftPos++];
    while(rightPos < right) tmp[tmpPos++] = value[rightPos++];
    memcpy(value + left,tmp + left,sizeof(int) * (right - left));
}

void mergeSort(int *value,int left,int right,int *tmp){
    if(left + 1 == right) return;
    int mid = (left + right) >> 1;
    mergeSort(value,left,mid,tmp);
    mergeSort(value,mid,right,tmp);
    merge(value,left,mid,right,tmp);
}

int main() {
    int n = read<int>();
    Data *value1 = new Data[n],*value2 = new Data[n];
    for(int i = 0;i < n;i++){
        int tmpValue = read<int>();
        value1[i] = Data(tmpValue,i);
    }
    for(int i = 0;i < n;i++){
        int tmpValue = read<int>();
        value2[i] = Data(tmpValue,i);
    }
    sort(value1,value1 + n);
    sort(value2,value2 + n);
    int *signs = new int[n];
    for(int i = 0;i < n;i++){
        signs[value1[i].sign] = value2[i].sign;
    }
    int *tmp = new int[n];
    mergeSort(signs,0,n,tmp);
    printf("%d\n",result);
    return 0;
}
