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
int geti(){
    char ch=getchar();while((ch<'0' || ch>'9')&&ch!='-')ch=getchar();
    int ret=0,k=1;
    if(ch=='-')k=-1,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret*k;
}
const int maxn = 30000 + 100;
int prime[maxn],mu[maxn],pnt=0,sigma[maxn],pre[maxn],who[maxn];
char vis[maxn];
struct Fs{
    int f,id;
}f[maxn];
inline bool cmp(const Fs &x,const Fs &y){
    return x.f<y.f;
}
inline void sieve(){
    int i,j;
    mu[1]=1;sigma[1]=1;
    for(i=2;i<maxn;i++){
        if(!vis[i]){
            mu[i]=-1;prime[++pnt]=i;
        }
        for(j=1;j<=pnt && i*prime[j]<maxn;j++){
            vis[i*prime[j]]=true;
            who[i*prime[j]]=i;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                break;
            }
            mu[i*prime[j]]=-mu[i];
        }
        sigma[i]=sigma[i-1]+mu[i];
    }
    for(i=1;i<maxn;i++)f[i].id=i;
    for(i=1;i<maxn;i++){
        for(j=i;j<maxn;j+=i){
            f[j].f+=i;
        }
    }
}
inline int calc(register int n1,register int m1){
    register int pos=0;
    register int cur=0;
    for(int i=1;i<=n1;i=pos+1){
        pos=min(n1/(n1/i),m1/(m1/i));
        cur+=(sigma[pos]-sigma[i-1])*(n1/i)*(m1/i);
    }
    return cur;
}
int mx[maxn*200],ls[maxn*200],rs[maxn*200],root[maxn*200],vs[maxn],pts=0;
int vnt=0;
inline void update(register int x1,register int &x2,register int l,register int r,register int p,register int v){
    x2=++pts;
    if(l==r){
        mx[x2]=mx[x1]+v;
        return;
    }
    register int mid=(l+r)>>1;
    ls[x2]=ls[x1];rs[x2]=rs[x1];
    if(p<=mid)update(ls[x1],ls[x2],l,mid,p,v);
    else update(rs[x1],rs[x2],mid+1,r,p,v);
    mx[x2]=mx[ls[x2]]+mx[rs[x2]];
}
inline int query(register int x,register int l,register int r,register int xl,register int xr){
    if(l==xl && r==xr){
        return mx[x];
    }
    int mid=(l+r)>>1;
    if(xr<=mid)return query(ls[x],l,mid,xl,xr);
    else if(xl>mid)return query(rs[x],mid+1,r,xl,xr);
    else return query(ls[x],l,mid,xl,mid)+query(rs[x],mid+1,r,mid+1,xr);
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    register int i,j,Q,last,n,m,p,pos,res,rt,n1,m1,ret,a;
    sieve();
    sort(f+1,f+maxn,cmp);
    for(i=1;i<maxn;i++){
        for(j=f[i].id;j<maxn;j+=f[i].id){
            ++vnt;
            update(root[vnt-1],root[vnt],1,maxn,j,f[i].f*mu[j/f[i].id]);
        }
        vs[i]=vnt;
    }
    Q=geti();
    last=0;
    while(Q--){
        n=geti();m=geti();a=geti();p=geti();
        a = 1LL*(a^last)%p;
        if(n>m)swap(n,m);
        pos=0;
        res=0;
        rt=0;
        for(i=1;i<maxn;i++){
            if(f[i].f<=a)rt=i;
            else break;
        }
        for(i=1;i<=n;i=pos+1){
            n1=n/i,m1=m/i;
            pos=min(n/n1,m/m1);
            ret=query(root[vs[rt]],1,maxn,i,pos);
            res+=ret*(n/i)*(m/i);
        }
        last=abs(res);
        printf("%d\n",res);
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
