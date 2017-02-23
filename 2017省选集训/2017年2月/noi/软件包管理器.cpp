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
#define ls (x<<1)
#define rs (x<<1|1)
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
const int maxn = 100000 + 1000;
int n,fa[maxn];
int st[maxn],pt[maxn*2],nxt[maxn*2],ent=0;
int dfn[maxn],anc[maxn],size[maxn],dep[maxn],bson[maxn],lx[maxn],rx[maxn],dnt=0;
void adde(int u,int v){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;
}
void dfs(int x){
    int bsz=0;
    size[x]=1;
    for(int i=st[x];i;i=nxt[i]){
        dep[pt[i]]=dep[x]+1;
        dfs(pt[i]);
        if(size[pt[i]]>bsz){
            bsz=size[pt[i]];
            bson[x]=pt[i];
        }
        size[x]+=size[pt[i]];
    }
}
void df2(int x,int a){
    dfn[x]=++dnt;
    lx[x]=dnt;
    anc[x]=a;
    if(bson[x]){
        df2(bson[x],a);
    }
    for(int i=st[x];i;i=nxt[i]){
        if(pt[i]==bson[x])continue;
        df2(pt[i],pt[i]);
    }
    rx[x]=dnt;
}
struct SegTree{
    int mx[maxn*4],lazy[maxn*4];
    SegTree(){
        memset(mx,0,sizeof(mx));
        memset(lazy,-1,sizeof(lazy));
    }
    void update(int x,int l,int r){
        if(lazy[x]!=-1){
            int mid=(l+r)>>1;
            if(l!=r){
                mx[ls]=lazy[x]*(mid-l+1);
                mx[rs]=lazy[x]*(r-mid);
                lazy[ls]=lazy[x];lazy[rs]=lazy[x];
            }
            lazy[x]=-1;
        }
    }
    void modify(int x,int l,int r,int xl,int xr,int v){
        update(x,l,r);
        if(l==xl && r==xr){
            mx[x]=v*(r-l+1);lazy[x]=v;return;
        }
        int mid=(l+r)>>1;
        if(xr<=mid)modify(ls,l,mid,xl,xr,v);
        else if(xl>mid)modify(rs,mid+1,r,xl,xr,v);
        else{
            modify(ls,l,mid,xl,mid,v);
            modify(rs,mid+1,r,mid+1,xr,v);
        }
        mx[x]=mx[ls]+mx[rs];
    }
    int query(int x,int l,int r,int xl,int xr){
        update(x,l,r);
        if(l==xl && r==xr){
            return mx[x];
        }
        int mid=(l+r)>>1;
        if(xr<=mid)return query(ls,l,mid,xl,xr);
        else if(xl>mid)return query(rs,mid+1,r,xl,xr);
        else return query(ls,l,mid,xl,mid)+query(rs,mid+1,r,mid+1,xr);
    }
}t;
//0:uninstalled, 1:installed
//install means query the number of zero on the path
int install(int x){
    int ret=0;
    int u=x;
    while(anc[x]!=1){
        ret+=t.query(1,1,n+10,dfn[anc[x]],dfn[x]);
        t.modify(1,1,n+10,dfn[anc[x]],dfn[x],1);
        x=fa[anc[x]];
    }
    ret+=t.query(1,1,n+10,dfn[anc[x]],dfn[x]);
    t.modify(1,1,n+10,dfn[anc[x]],dfn[x],1);
    return dep[u]-ret;
}
int uninstall(int x){
    int ret=t.query(1,1,n+10,lx[x],rx[x]);
    t.modify(1,1,n+10,lx[x],rx[x],0);
    return ret;
}
int main(){
    n=geti();
    for(int i=2;i<=n;i++){
        fa[i]=geti();fa[i]++;
        adde(fa[i],i);
    }
    dep[1]=1;
    dfs(1);
    df2(1,1);
    int Q=geti();
    char ops[16];
    int opt,ret;
    for(int i=1;i<=Q;i++){
        scanf("%s",ops);
        opt=geti();++opt;
        if(ops[0]=='i'){
            ret=install(opt);
            printf("%d\n",ret);
        }
        else{
            ret=uninstall(opt);
            printf("%d\n",ret);
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
