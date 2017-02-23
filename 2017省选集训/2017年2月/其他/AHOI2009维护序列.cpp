#include <cstdio>
#include <iostream>
#define ls (x<<1)
#define rs (x<<1|1)
using namespace std;
typedef long long ll;
ll geti(){
    ll ret=0;char ch=getchar();
    while(ch<'0' || ch>'9')ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret;
}
const int maxn = 100000 + 100;
int n;
ll p;
ll a[maxn],mx[maxn*4],lazyp[maxn*4],lazyc[maxn*4];
ll size[maxn*4];
void build(int x,int l,int r){
    lazyc[x]=1;lazyp[x]=0;
    if(l==r){
        size[x]=1;mx[x]=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    size[x]=size[ls]+size[rs];
    mx[x]=(mx[ls]+mx[rs])%p;
}
void update(int x){
    if(size[x]==1)return;
    mx[ls]=(mx[ls]*lazyc[x])%p;mx[ls]=(mx[ls]+lazyp[x]*size[ls])%p;
    mx[rs]=(mx[rs]*lazyc[x])%p;mx[rs]=(mx[rs]+lazyp[x]*size[rs])%p;
    lazyc[ls]=(lazyc[ls]*lazyc[x])%p;
    lazyc[rs]=(lazyc[rs]*lazyc[x])%p;
    lazyp[ls]=(lazyp[ls]*lazyc[x]+lazyp[x])%p;
    lazyp[rs]=(lazyp[rs]*lazyc[x]+lazyp[x])%p;
    lazyp[x]=0;lazyc[x]=1;
}
void modifyp(int x,int l,int r,int xl,int xr,ll v){
    if(l==xl && r==xr){
        mx[x]=(mx[x]+v*size[x])%p;lazyp[x]+=v;return;
    }
    update(x);
    int mid=(l+r)>>1;
    if(xr<=mid)modifyp(ls,l,mid,xl,xr,v);
    else if(xl>mid)modifyp(rs,mid+1,r,xl,xr,v);
    else{
        modifyp(ls,l,mid,xl,mid,v);modifyp(rs,mid+1,r,mid+1,xr,v);
    }
    mx[x]=(mx[ls]+mx[rs])%p;
}
void modifyc(int x,int l,int r,int xl,int xr,ll v){
    update(x);
    if(l==xl && r==xr){
        mx[x]=(mx[x]*v)%p;lazyp[x]=(lazyp[x]*v)%p;lazyc[x]=(lazyc[x]*v)%p;update(x);
        return;
    }
    int mid=(l+r)>>1;
    if(xr<=mid)modifyc(ls,l,mid,xl,xr,v);
    else if(xl>mid)modifyc(rs,mid+1,r,xl,xr,v);
    else {
        modifyc(ls,l,mid,xl,mid,v);modifyc(rs,mid+1,r,mid+1,xr,v);
    }
    mx[x]=(mx[ls]+mx[rs])%p;
}
ll query(int x,int l,int r,int xl,int xr){
    update(x);
    if(l==xl && r==xr){
        return mx[x];
    }
    int mid=(l+r)>>1;
    if(xr<=mid)return query(ls,l,mid,xl,xr);
    else if(xl>mid)return query(rs,mid+1,r,xl,xr);
    else return (query(ls,l,mid,xl,mid)+query(rs,mid+1,r,mid+1,xr))%p;
}
int main(){
    n=geti();p=geti();
    for(int i=1;i<=n;i++)a[i]=geti();
    build(1,1,n+10);
    int Q,op,x,m,g;
    Q=geti();
    while(Q--){
        op=geti();
        if(op==1){
            x=geti();m=geti();g=geti();
            modifyc(1,1,n+10,x,m,g);
        }
        else if(op==2){
            x=geti();m=geti();g=geti();
            modifyp(1,1,n+10,x,m,g);
        }
        else{
            x=geti();m=geti();
            printf("%lld\n",query(1,1,n+10,x,m));
        }
    }
 
    return 0;
}
