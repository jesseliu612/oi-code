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
int a[maxn];
struct Ptree{
    ll mx[maxn*30],lazy[maxn*30];
    int root[maxn*30],ls[maxn*30],rs[maxn*30],pnt;
    Ptree(){
        memset(mx,0,sizeof(mx));
        memset(root,0,sizeof(root));
        memset(ls,0,sizeof(ls));
        memset(rs,0,sizeof(rs));
        pnt=0;
    }
    void build(int &x,int l,int r){
        x=++pnt;
        if(l==r){
            mx[x]=a[l];return;
        }
        int mid=(l+r)>>1;
        build(ls[x],l,mid);build(rs[x],mid+1,r);
        mx[x]=mx[ls[x]]+mx[rs[x]];
    }
    void modify(int &x,int x2,int l,int r,int xl,int xr,ll v){
        x=++pnt;
        ls[x]=ls[x2];rs[x]=rs[x2];mx[x]=mx[x2];lazy[x]=lazy[x2];
        if(l==xl && r==xr){
            lazy[x]+=v;
            return;
        }
        mx[x]+=v*(xr-xl+1);
        int mid=(l+r)>>1;
        if(xr<=mid)modify(ls[x],ls[x2],l,mid,xl,xr,v);
        else if(xl>mid)modify(rs[x],rs[x2],mid+1,r,xl,xr,v);
        else modify(ls[x],ls[x2],l,mid,xl,mid,v),modify(rs[x],rs[x2],mid+1,r,mid+1,xr,v);
    }
    ll query(int x,int l,int r,int xl,int xr){
        if(l==xl && r==xr){
            return mx[x]+lazy[x]*(xr-xl+1);
        }
        int mid=(l+r)>>1;
        if(xr<=mid)return query(ls[x],l,mid,xl,xr)+lazy[x]*(xr-xl+1);
        else if(xl>mid)return query(rs[x],mid+1,r,xl,xr)+lazy[x]*(xr-xl+1);
        else return query(ls[x],l,mid,xl,mid)+query(rs[x],mid+1,r,mid+1,xr)+lazy[x]*(xr-xl+1);
    }
}t;
int n,m;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    n=geti();m=geti();
    for(int i=1;i<=n;i++)a[i]=geti();
    t.build(t.root[0],1,n);
    char ops[10];
    int l,r,d,tt;
    int T=0;
    while(m--){
        scanf("%s",ops);
        if(ops[0]=='C'){
            l=geti();r=geti();d=geti();
            ++T;
            t.modify(t.root[T],t.root[T-1],1,n,l,r,d);
        }
        else if(ops[0]=='Q'){
            l=geti();r=geti();
            printf("%lld\n",t.query(t.root[T],1,n,l,r));
        }
        else if(ops[0]=='H'){
            l=geti();r=geti();tt=geti();
            printf("%lld\n",t.query(t.root[tt],1,n,l,r));
        }
        else{
            tt=geti();
            T=tt;
        }
    }
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
