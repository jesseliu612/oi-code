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
const int ed=255;
ll geti(){
    char ch=getchar();while((ch<'0' || ch>'9')&&ch!='-')ch=getchar();
    ll ret=0,k=1;
    if(ch=='-')k=-1,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret*k;
}
int n;
ll p;
int pr[8]={2,3,5,7,11,13,17,19};
struct num{
    int zt,pr;
}a[600];
bool cmp(num x,num y){
    return x.pr>y.pr;
}
ll f[ed+1][ed+1],g[2][ed+1][ed+1];
int main(){
    n=geti();p=geti();
    for(int i=2;i<=n;i++){
        a[i].pr=i;
        for(int j=0;j<8;j++){
            if(a[i].pr%pr[j]==0){
                a[i].zt|=(1<<j);
                while(a[i].pr%pr[j]==0)a[i].pr/=pr[j];
            }
        }
    }

    sort(a+2,a+n+1,cmp);

    f[0][0]=1;
    for(int i=2;i<=n;i++){
        //printf("a[%d].pr = %d, a[%d].zt = %d\n",i,a[i].pr,i,a[i].zt);
        if(i==2 || a[i].pr!=a[i-1].pr || a[i].pr==1){
            memcpy(g[0],f,sizeof(f));
            memcpy(g[1],f,sizeof(f));
        }
        
        for(int j=ed;j>=0;j--){
            for(int k=ed;k>=0;k--){
                if(j&k)continue;
                if(!(k&a[i].zt)){
                    g[0][(a[i].zt | j)][k]+=g[0][j][k];g[0][(a[i].zt | j)][k]%=p;
                }
                if(!(j&a[i].zt)){
                    g[1][j][(a[i].zt | k)]+=g[1][j][k];g[1][j][(a[i].zt | k)]%=p;
                }
            }
        }

        if(i==n || a[i+1].pr!=a[i].pr || a[i].pr==1){
            for(int j=ed;j>=0;j--){
                for(int k=ed;k>=0;k--){
                    if(j&k)continue;
                    f[j][k]=g[0][j][k]+g[1][j][k]-f[j][k];
                }
            }
        }
    }
    
    ll ans=0;
    for(int i=ed;i>=0;i--){
        for(int j=ed;j>=0;j--){
            if(i&j)continue;
            ans+=f[i][j];ans%=p;
        }
    }
    ans+=p;ans%=p;
    printf("%lld",ans);
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
