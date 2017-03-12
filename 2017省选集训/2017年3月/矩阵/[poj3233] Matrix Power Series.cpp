#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
const int inf = 2147483640;
typedef long long ll;
ll geti(){
    char ch=getchar();while((ch<'0' || ch>'9')&&ch!='-')ch=getchar();
    ll ret=0,k=1;
    if(ch=='-')k=-1,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret*k;
}
int n,q,mo;
struct mtx{
    int c[40][40];
    mtx(){
        memset(c,0,sizeof(c));
    }
};
inline mtx operator * (mtx a,mtx b){
    mtx c;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            for(int k=1;k<=n;++k){
                c.c[i][k]=(c.c[i][k]+a.c[i][j]*b.c[j][k])%mo;
            }
        }
    }
    return c;
}
inline mtx operator + (mtx a,mtx b){
    mtx c;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            c.c[i][j]=(a.c[i][j]+b.c[i][j])%mo;
        }
    }
    return c;
}
mtx p;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    n=geti();q=geti();mo=geti();
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            p.c[i][j]=geti();
        }
    }
    int u=q;
    mtx x=p,ret=p,res,tmp;
    for(int i=1;i<=n;++i)tmp.c[i][i]=1;
    while(u){
        if(u&1){
            tmp=tmp*x;
            res=res*x+ret;
        }
        ret=ret+ret*x;
        x=x*x;
        u>>=1;
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            printf("%d ",res.c[i][j]);
        }
        puts("");
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
