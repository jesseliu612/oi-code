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
const int maxn = 50000;
int prime[maxn],vis[maxn],mu[maxn],pre[maxn],pnt=0;
void sieve(){
    mu[1]=1;
    for(int i=2;i<maxn;i++){
        if(!vis[i]){
            prime[++pnt]=i;mu[i]=-1;
        }
        for(int j=1;j<=pnt && i*prime[j]<maxn;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                break;
            }
            else{
                mu[i*prime[j]]=-mu[i];
            }
        }
    }
}
ll calc(ll x){
    ll mx=sqrt(x)+1;
    ll ret=0;
    //printf("calc(%lld)\n",x);cout << flush;
    //cout << mx << endl;
    for(int i=1;i<=mx;i++){
        ret+=(x/(i*i))*mu[i];
    }
    return ret;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    sieve();
    int T=geti();
    while(T--){
        ll n=geti();
        ll l=1,r=(1ll<<31)-1,mid,rt=-1;
        while(l<=r){
            mid=(l+r)>>1;
            //cout << "l = " << l << " , r = " << r << endl;
            if(calc(mid)<=n){
                rt=mid;
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        printf("%lld\n",rt);
    }
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
