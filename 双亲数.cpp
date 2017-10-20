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
const int maxn = 100000 + 100;
int n,m;
int prime[maxn],mu[maxn],pnt=0;
ll sigma[maxn];
char vis[maxn];
void sieve(){
    mu[1]=1;sigma[1]=1;
    for(int i=2;i<=m;i++){
        if(!vis[i]){
            mu[i]=-1;prime[++pnt]=i;
        }
        for(int j=1;j<=pnt && i*prime[j]<=m;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                break;
            }
            mu[i*prime[j]]=-mu[i];
        }
        sigma[i]=sigma[i-1]+mu[i];
    }
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    n=geti();m=geti();int d=geti();
    if(n>m)swap(n,m);
    sieve();
    int n1=n/d,m1=m/d;
    int pos=0;
    ll cur=0;
    for(int i=1;i<=n1;i=pos+1){
        pos=min(n1/(n1/i),m1/(m1/i));
        cur+=(sigma[pos]-sigma[i-1])*(n1/i)*(m1/i);
    }
    cout << cur;
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}

