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
#define RG register
using namespace std;
const int inf = 2147483640;
typedef int ll;
ll geti(){
    char ch=getchar();while((ch<'0' || ch>'9')&&ch!='-')ch=getchar();
    ll ret=0,k=1;
    if(ch=='-')k=-1,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret*k;
}
const int maxn = 30000 + 100;
int prime[maxn],mu[maxn],pnt=0;
int sigma[maxn],pre[maxn];
int who[maxn];
char vis[maxn];
struct Fs{
    ll f;
    int id;
}f[maxn];
inline char cmp(RG const Fs &x,RG const Fs &y){
    return x.f<y.f;
}
inline void sieve(){
    mu[1]=1;sigma[1]=1;
    for(RG int i=2;i<maxn;i++){
        if(!vis[i]){
            mu[i]=-1;prime[++pnt]=i;
        }
        for(RG int j=1;j<=pnt && i*prime[j]<maxn;j++){
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
    for(RG int i=1;i<maxn;i++)f[i].id=i;
    for(RG int i=1;i<maxn;i++){
        for(RG int j=i;j<maxn;j+=i){
            f[j].f+=i;
        }
    }
    /*for(int i=1;i<maxn;i++){
        printf("f[%d].c = %d\n",i,f[i].c);
    }
    */
}
int mx[maxn*280],ls[maxn*280],rs[maxn*280],root[maxn*280],vs[maxn],pts=0;
int vnt=0;
int p,v;
inline void update(RG int x1,int &x2,RG int l,RG int r){
    x2=++pts;
    if(l==r){
        mx[x2]=mx[x1]+v;
        return;
    }
    int mid=(l+r)>>1;
    ls[x2]=ls[x1];rs[x2]=rs[x1];
    p<=mid?update(ls[x1],ls[x2],l,mid):update(rs[x1],rs[x2],mid+1,r);
    mx[x2]=mx[ls[x2]]+mx[rs[x2]];
}
inline int query(RG int x,RG int l,RG int r,RG int xl,RG int xr){
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

    sieve();
    sort(f+1,f+maxn,cmp);
    for(RG int i=1;i<maxn;i++){
        for(RG int j=f[i].id;j<maxn;j+=f[i].id){
            ++vnt;
            p=j;v=f[i].f*mu[j/f[i].id];
            update(root[vnt-1],root[vnt],1,maxn);
        }
        vs[i]=vnt;
    }
    RG int Q=geti();
    RG int last=0;
    while(Q--){
        RG int n=geti();RG int m=geti();RG int a=geti();RG int p=geti();
        a = 1LL*(a^last)%p;
        if(n>m)swap(n,m);
        RG int pos=0;
        RG int res=0;
        RG int l=1,r=n,mid,rt=0;
        while(l<=r){
            mid=(l+r)>>1;
            if(f[mid].f<=a){
                l=mid+1;rt=mid;
            }
            else{
                r=mid-1;
            }
        }
        rt=vs[rt];
        for(RG int i=1;i<=n;i=pos+1){
            RG int n1=n/(n/i),m1=m/(m/i);
            pos=n1<m1?n1:m1;
            RG int ret=query(root[rt],1,maxn,i,pos);
            res+=ret*(n/i)*(m/i);
        }
        last=abs(res);
        printf("%d\n",res);
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
