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
inline ll geti(){
    char ch=getchar();while((ch<'0' || ch>'9')&&ch!='-')ch=getchar();
    ll ret=0,k=1;
    if(ch=='-')k=-1,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret*k;
}
const int maxn = 300000 +100 ;
int n,gap;
ll s[maxn],c[maxn],f[maxn];
struct lines{
    long double k,b,id;
}q[maxn];
inline char check(const int &id,const ll &x){
    return (long double)q[id-1].k*x+q[id-1].b>=(long double)q[id].k*x+q[id].b;
}
inline int solve(register int l,register int r,register ll x){
    register int mid,rt=-1;
    while(l<=r){
        mid=(l+r)>>1;
        if(check(mid,x)){
            l=mid+1;
            rt=mid;
        }
        else{
            r=mid-1;
        }
    }
    return rt;
}
int main(){
    n=geti();gap=geti();
    for(register int i=1;i<=n;i++){
        s[i]=s[i-1]+geti();
        c[i]=c[i-1]+geti();
    }
    f[0]=0;
    register int hd=0,tl=1;
    for(register int i=1;i<=n;i++){
        register int ret=solve(hd+1,tl,s[i]);
        f[i]=q[ret].k*s[i]+q[ret].b+gap*c[n]+s[i]*c[i];
        register lines r;
        r.k=-c[i];
        r.b=f[i]-gap*c[i];
        r.id=i;
        while(tl-hd>1 && (r.b-q[tl-1].b)*(q[tl-1].k-q[tl].k)<=(q[tl].b-q[tl-1].b)*(q[tl-1].k-r.k))tl--;
        q[++tl]=r;
    }
    printf("%lld",f[n]);
    return 0;
}
