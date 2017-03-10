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
const int maxn = 1e7+100;
const int mo = 20101009;
int n,m;
int prime[maxn],vis[maxn],fx[maxn],pre[maxn],s[maxn],sum[maxn],pnt=0;
void sieve(){
    fx[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++pnt]=i;fx[i]=1-i;
        }
        for(int j=1;j<=pnt && i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                fx[i*prime[j]]=fx[i];
                break;
            }
            else{
                ll cur=(ll)fx[i]*fx[prime[j]];cur%=mo;
                fx[i*prime[j]]=cur;
            }
        }
    }
    for(int i=1;i<=n;i++)pre[i]=(pre[i-1]+fx[i])%mo;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    n=geti();m=geti();
    sieve();
    if(n>m)swap(n,m);
    ll ans=0;
    for(int i=1;i<=m;i++)sum[i]=sum[i-1]+i,sum[i]%=mo;
    for(int Q=1;Q<=n;Q++){
        ll cur=Q;
        cur*=sum[n/Q];cur%=mo;
        cur*=sum[m/Q];cur%=mo;
        cur*=fx[Q];cur%=mo;
        ans+=cur;ans%=mo;
    }
    cout << (ans%mo+mo)%mo;
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
