#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int n = read<int>(),m = read<int>();
    vector<int> colors;
    colors.reserve(n);
    int maxValue = 1;
    for(int i = 0;i < n;i++) {
        int tmpValue = read<int>();
        colors.push_back(tmpValue);
        maxValue = max(maxValue,tmpValue);
    }
    vector<vector<int> > values(maxValue + 1,vector<int>());
    for(int i = 0;i < n;i++) {
        int color = colors[i];
        values[color].push_back(i);
    }
    while(m--) {
        int opt = read<int>();
        if(opt == 1) {
            int left = read<int>(),right = read<int>(),color = read<int>();
            if(color > maxValue) {
                printf("0\n");
                continue;
            }
            left--; right--;
            vector<int>::iterator nowBegin = values[color].begin(),nowEnd = values[color].end(),leftIt = lower_bound(nowBegin,nowEnd,left),rightIt = lower_bound(nowBegin,nowEnd,right);
            if(leftIt == nowEnd && rightIt == nowEnd) {
                printf("0\n");
                continue;
            }else if(rightIt == nowEnd) {
                printf("%d\n",static_cast<int>(rightIt - leftIt));
            }else {
                if(*rightIt == right) {
                    rightIt++;
                }
                printf("%d\n",static_cast<int>(rightIt - leftIt));
            }
        }else {
            int pos = read<int>();
            pos--;
            int color1 = colors[pos],color2 = colors[pos + 1];
            if(color1 == color2) {
                continue;
            }else {
                vector<int>::iterator it1 = lower_bound(values[color1].begin(),values[color1].end(),pos),it2 = lower_bound(values[color2].begin(),values[color2].end(),pos + 1);
                *it1 = pos + 1;
                *it2 = pos;
                colors[pos] = color2;
                colors[pos + 1] = color1;
            }
        }
    }
    printf("\n");
    return 0;
}
