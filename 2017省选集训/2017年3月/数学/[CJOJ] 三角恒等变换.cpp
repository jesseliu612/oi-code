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
const int mo = 1e9+7;
struct mtx{
    ll c[4][4];
    void out(){
        for(int i=0;i<=3;++i){
            for(int j=0;j<=3;++j){
                cout << c[i][j] << " ";
            }
            puts("");
        }
        puts("");
    }
};
mtx operator * (mtx &a,mtx &b){
    mtx c={0};
    for(int i=0;i<=3;++i){
        for(int j=0;j<=3;++j){
            for(int k=0;k<=3;++k){
                (c.c[i][k]+=a.c[i][j]*b.c[j][k])%=mo;
            }
        }
    }
    return c;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int n=geti();int m=geti();
    if(m==0){
        printf("%d %d",n,n);return 0;
    }
    if(m<=2){
        printf("-1");return 0;
    }
    mtx b={0},ret={0},z={0};
    for(int i=1;i<=3;++i)b.c[0][i]=n;
    b.c[0][0]=-1;
    for(int i=0;i<=3;++i)ret.c[i][i]=1;
    z.c[0][0]=1;z.c[0][3]=1;
    z.c[2][1]=1;z.c[3][2]=1;
    z.c[2][3]=1;z.c[3][3]=1;
    mtx tmp=z;
    int u=m-3;
    while(u){
        if(u&1){
            ret=ret*z;
        }
        z=z*z;
        u>>=1;
    }
    b=b*ret;
    printf("%lld ",(b.c[0][3]%mo+1+mo)%mo);
    b=b*tmp;
    printf("%lld",(b.c[0][3]+mo)%mo);
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
