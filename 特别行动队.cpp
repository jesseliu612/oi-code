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
const int maxn = 1000000 + 100;
struct node{
    ll id,x,y;
}q[maxn];
ll f[maxn],s[maxn];
int n,hd,tl;
ll a,b,c;
ll xmg[maxn];
int main(){
    n=geti();a=geti();b=geti();c=geti();
    for(int i=1;i<=n;i++)xmg[i]=geti(),s[i]=s[i-1]+xmg[i];
    int hd=0,tl=1;
    // q[++tl].id=0;q[tl].x=0;q[tl].y=0;
    for(int i=1;i<=n;i++){
        while((tl-hd>1) && q[hd+2].x-q[hd+1].x>=s[i]*q[hd+2].y-s[i]*q[hd+1].y)++hd;
        int j=q[hd+1].id;
        f[i]=f[j]+a*(s[i]-s[j])*(s[i]-s[j])+b*(s[i]-s[j])+c;
        ll x=f[i]+a*s[i]*s[i]-b*s[i];
        ll y=2*a*s[i];
        while((tl-hd)>1 && (x-q[tl].x)*(q[tl].y-q[tl-1].y)<=(q[tl].x-q[tl-1].x)*(y-q[tl].y))--tl;
        q[++tl].id=i;q[tl].x=x;q[tl].y=y;
        //cout << "ZY = " << j << " " << f[i] << " , hd = " << hd << " , tl = " << tl << endl;
    }
    printf("%lld",f[n]);
    return 0;
}
