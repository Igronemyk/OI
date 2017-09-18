#include <cstdio>
#include <algorithm>

using namespace std;


int main(){
    int andValue,orValue,sumValue;
    while(~scanf("%d%d%d",&andValue,&orValue,&sumValue)){
        for(int a = 0 ;a <= sumValue && a <= orValue;a++){
            for(int b = 0;a + b <= sumValue;b++){
                if((a | b) > orValue) continue;
                for(int c = 0;a + b + c <= sumValue;c++){
                    if((a | b | c) > orValue) continue;
                    if(a + b + c == sumValue && (a | b | c) == orValue && (a & b & c) == andValue) {
                        printf("%d %d %d",a,b,c);
                        goto outside;
                    }
                }
            }
        }
        outside:
        printf("\n");
    }
    return 0;
}
