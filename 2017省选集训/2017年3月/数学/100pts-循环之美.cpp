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
const int maxn = 3e6+100;
int n,m,k,lim;
int prime[maxn],mu[maxn],sigma[maxn],pre[maxn],rnt=0,divk[maxn],knt=0;
char vis[maxn];
int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}
void sieve(){
    mu[1]=1;
    for(int i=2;i<=lim;i++){
        if(!vis[i]){
            mu[i]=-1;prime[++rnt]=i;
        }
        for(int j=1;j<=rnt && i*prime[j]<=lim;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                break;
            }
            mu[i*prime[j]]=-mu[i];
        }
    }
    for(int i=1;i<=lim;i++){
        sigma[i]=sigma[i-1]+mu[i];
    }
    int u=k;
    for(int i=2;i<=k;i++){
        if(u%i==0){
            while(u%i==0)u/=i;
            ++knt;
            divk[knt]=i;
        }
    }
}
map<ll ,ll> dd;
ll du(ll x){
    if(x<=lim)return sigma[x];
    if(dd[x])return dd[x];
    ll res=0;
    ll pos;
    for(ll i=2;i<=x;i=pos+1){
        pos=x/(x/i);
        res+=(pos-i+1)*du(x/i);
    }
    dd[x]=1-res;
    return 1-res;
}
map< ll , map<ll,ll> > ss;
ll g(ll x,ll y){
    if(x<=1)return x;
    if(y==0)return du(x);
    if(ss[x][y])return ss[x][y];
    ss[x][y]=g(x,y-1)+g(x/divk[y],y);
    return ss[x][y];
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    n=geti();m=geti();k=geti();
    lim=min(min(n,m),3000000);
    sieve();
    int pos=0;
    for(int i=1;i<=k;i++){
        pre[i]=pre[i-1];
        if(gcd(i,k)==1)pre[i]+=1;
    }
    ll res=0;
    ll lm=min(n,m);
    for(int i=1;i<=lm;i=pos+1){
        pos=min(n/(n/i),m/(m/i));
        res+=(ll)(g(pos,knt)-g(i-1,knt))*(n/i)*(((m/i)/k)*pre[k]+pre[(m/i)%k]);
    }
    cout << res;
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
