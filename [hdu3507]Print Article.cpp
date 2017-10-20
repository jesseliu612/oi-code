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
const int maxn = 500000 + 100;
struct node{
    ll id,x,y;
}q[maxn];
ll f[maxn],s[maxn];
int n,hd,tl;
ll m;
ll c[maxn];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    while(scanf("%d%lld",&n,&m)==2){
        memset(s,0,sizeof(s));
        hd=0;tl=0;
        for(int i=1;i<=n;i++)c[i]=geti(),s[i]=s[i-1]+c[i];
        q[++tl].id=0;
        q[tl].x=0;
        q[tl].y=0;
        //printf("%lld ",f[1]);
        for(int i=1;i<=n;i++){
            while((tl-hd>1) && s[i]*(q[hd+2].y-q[hd+1].y)>=q[hd+2].x-q[hd+1].x)++hd;
            int j=q[hd+1].id;
            f[i]=f[j]+(s[i]-s[j])*(s[i]-s[j])+m;
            ll x=f[i]+s[i]*s[i];
            ll y=2*s[i];
            while((tl-hd>1) && (x-q[tl].x)*(q[tl].y-q[tl-1].y)<=(q[tl].x-q[tl-1].x)*(y-q[tl].y))--tl;
            q[++tl].x=x;q[tl].y=y;q[tl].id=i;
        }
        //puts("");
        printf("%lld\n",f[n]);
    }
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
