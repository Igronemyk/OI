#include <cstdio>
#include <iostream>
using namespace std;

int v[1000006];
int tmp[1000006];

long long ans = 0;

void Merge(int l,int mid,int r)
{
    int l_p=l,r_p=mid;
    int tmp_p=l;
    while(l_p!=mid&&r_p!=r){
        if(v[l_p]<=v[r_p]){
            tmp[tmp_p++]=v[l_p++];
        }else{
            tmp[tmp_p++]=v[r_p++];
            ans += mid-l_p;
        }
    }
    while(l_p!=mid) tmp[tmp_p++]=v[l_p++];
    while(r_p!=r) tmp[tmp_p++]=v[r_p++];
    for(int i = l;i < r;i++) v[i] = tmp[i];
}

void MergeSort(int l,int r){
    if(l+1==r || l == r){
        return;
    }
    int mid=(l + r) >> 1;
    MergeSort(l,mid);
    MergeSort(mid,r);
    Merge(l,mid,r);
    return;
}



int main(){
    int vsize;
    while(true){
        ans = 0;
        scanf("%d",&vsize);
        if(vsize == 0) break;
        for(int i=0;i<vsize;i++){
            scanf("%d",&v[i]);
        }
        MergeSort(0,vsize);
        printf("%lld\n",ans);
    }
    return 0;
}
