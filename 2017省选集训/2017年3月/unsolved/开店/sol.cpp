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
const int maxn = 150000 + 100;
int n,Q,A;
int st[maxn],pt[maxn*2],nxt[maxn*2],w[maxn*2],ent=0;
struct mons{
    int id;
    ll w;
}a[maxn];
void adde(int u,int v,int wt){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;w[ent]=wt;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;w[ent]=wt;
}
int fa[maxn],sum[maxn],bson[maxn],dfn[maxn],anc[maxn],dnt=0;
void dfs(int x){
    sum[x]=1;
    for(int i=st[x];i;i=nxt[i]){
        if(pt[i]==fa[x])continue;
        dfs(pt[i]);
        sum[x]=sum[pt[i]];
        if(sum[pt[i]]>sum[bson[x]])bson[x]=pt[i];
    }
}
void df2(int x,int a){
    dfn[x]=++dnt;anc[x]=a;
    if(bson[x])df2(bson[x],a);
    for(int i=st[x];i;i=nxt[i]){
        if(pt[i]==fa[x] || pt[i]==bson[x])continue;
        df2(pt[i],pt[i]);
    }
}
struct ptree{
    ll mx[maxn*100],lazy[maxn*100];
    int ls[maxn*100],rs[maxn*100],root[maxn*100],pnt;
    ptree(){
        memset(mx,0,sizeof(mx));memset(lazy,0,sizeof(lazy));
        memset(ls,0,sizeof(ls));memset(rs,0,sizeof(rs));memset(root,0,sizeof(root));
        pnt=0;
    }
    void modify(int &x1,int x2,int l,int r,int xl,int xr,int v){
        x1=++pnt;
        if(l==xl && r==xr){
            lazy[x1]=v*(xr-xl+1);
            return;
        }
        mx[x1]=mx[x2]+(xr-xl+1)*v;
        int mid=(l+r)>>1;
        if(xr<=mid) modify(ls[x1],ls[x2],l,mid,xl,xr,v);
        else if(xl>mid) modify(rs[x1],rs[x2],mid+1,r,xl,xr,v);
        else modify(ls[x1],ls[x2],l,mid,xl,mid,v) , modify(rs[x1],rs[x2],mid+1,r,mid+1,xr,v);
        mx[x1]=mx[ls[x1]]+mx[rs[x1]];
    }
    ll query(int x,int l,int r,int xl,int xr){
        if(l==xl && r==xr)return mx[x];
        int mid=(l+r)>>1;
        if(xr<=mid)return query(ls[x],l,mid,xl,xr)+lazy[x];
        else if(xl>mid)return query(rs[x],mid+1,r,xl,xr)+lazy[x];
        else return query(ls[x],l,mid,xl,mid)+query(rs[x],mid+1,r,mid+1,xr)+lazy[x];
    }
}t;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    n=geti();Q=geti();A=geti();
    for(int i=1;i<=n;i++)a[i].id=i,a[i].w=geti();
    int u,v,wt;
    for(int i=1;i<n;i++){
        u=geti();v=geti();wt=geti();
        adde(u,v,wt);
    }
    dfs(1);df2(1,1);
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
