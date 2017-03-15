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
const int maxn = 5000000 + 100;
const int mo = 1e9+7;
int k;
int mu[maxn],prime[maxn],pnt=0;
ll f[maxn],g[maxn],pre[maxn],mi[maxn];
char vis[maxn];
ll ksm(ll x){
    ll u=k,ret=1;
    x%=mo;
    while(u){
        if(u&1){
            (ret*=x)%=mo;
        }
        (x*=x)%=mo;
        u>>=1;
    }
    return ret;
}
void sieve(){
    mu[1]=1;g[1]=1;mi[1]=1;
    for(int i=2;i<maxn;i++){
        if(!vis[i]){
            prime[++pnt]=i;
            mu[i]=-1;
            mi[i]=ksm(i);
            g[i]=mi[i]-1;
        }
        for(int j=1;j<=pnt && i*prime[j]<maxn;j++){
            vis[i*prime[j]]=true;
            mi[i*prime[j]]=(mi[i]*mi[prime[j]])%mo;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                g[i*prime[j]]=(g[i]*mi[prime[j]])%mo;
                break;
            }
            mu[i*prime[j]]=-mu[i];
            g[i*prime[j]]=(g[i]*g[prime[j]])%mo;
        }
    }
    for(int i=1;i<maxn;i++)pre[i]=(pre[i-1]+g[i])%mo;
}
int main(){
    int T=geti();k=geti();
    sieve();
    int n,m;
    while(T--){
        n=geti();m=geti();
        if(n>m)swap(n,m);
        ll ans=0;
        int pos=0;
        for(int i=1;i<=n;i=pos+1){
            pos=min(n/(n/i),m/(m/i));
            (ans+=(((ll)(n/i)*(m/i))%mo)*(pre[pos]-pre[i-1]))%=mo;
        }
        if(ans<0)ans+=mo;
        printf("%lld\n",ans);
    }
    return 0;
}
