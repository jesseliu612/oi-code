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
bool cmp(const mons &x,const mons &y){
    return x.w<y.w;
}
void adde(int u,int v,int wt){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;w[ent]=wt;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;w[ent]=wt;
}
int fa[maxn],sum[maxn],bson[maxn],dfn[maxn],anc[maxn],dep[maxn],ver[maxn],rdn[maxn],dnt=0;
ll dis[maxn],pre[maxn],s[maxn];
void dfs(int x){
    sum[x]=1;
    for(int i=st[x];i;i=nxt[i]){
        if(pt[i]==fa[x])continue;
        dep[pt[i]]=dep[x]+1;
        dis[pt[i]]=dis[x]+w[i];
        fa[pt[i]]=x;
        dfs(pt[i]);
        sum[x]+=sum[pt[i]];
        if(sum[pt[i]]>sum[bson[x]])bson[x]=pt[i];
    }
}
void df2(int x,int a){
    dfn[x]=++dnt;anc[x]=a;rdn[dnt]=x;
    if(bson[x])df2(bson[x],a);
    for(int i=st[x];i;i=nxt[i]){
        if(pt[i]==fa[x] || pt[i]==bson[x])continue;
        df2(pt[i],pt[i]);
    }
}
struct Ptree{
    ll mx[maxn*120],lazy[maxn*120];
    int root[maxn*120],ls[maxn*120],rs[maxn*120],pnt;
    Ptree(){
        pnt=0;
    }
    void modify(int &x,int x2,int l,int r,int xl,int xr,ll v){
        x=++pnt;
        ls[x]=ls[x2];rs[x]=rs[x2];mx[x]=mx[x2];lazy[x]=lazy[x2];
        if(l==xl && r==xr){
            lazy[x]+=v;
            return;
        }
        mx[x]+=v*(s[xr]-s[xl-1]);
        int mid=(l+r)>>1;
        if(xr<=mid)modify(ls[x],ls[x2],l,mid,xl,xr,v);
        else if(xl>mid)modify(rs[x],rs[x2],mid+1,r,xl,xr,v);
        else modify(ls[x],ls[x2],l,mid,xl,mid,v),modify(rs[x],rs[x2],mid+1,r,mid+1,xr,v);
    }
    ll query(int x,int l,int r,int xl,int xr){
        if(l==xl && r==xr){
            return mx[x]+lazy[x]*(s[xr]-s[xl-1]);
        }
        int mid=(l+r)>>1;
        if(xr<=mid)return query(ls[x],l,mid,xl,xr)+lazy[x]*(s[xr]-s[xl-1]);
        else if(xl>mid)return query(rs[x],mid+1,r,xl,xr)+lazy[x]*(s[xr]-s[xl-1]);
        else return query(ls[x],l,mid,xl,mid)+query(rs[x],mid+1,r,mid+1,xr)+lazy[x]*(s[xr]-s[xl-1]);
    }
}t;
int Tnt=0;
void toroot(int x){
    //printf("toroot(%d)\n",x);
    while(anc[x]!=1){
        ++Tnt;
        t.modify(t.root[Tnt],t.root[Tnt-1],1,n+10,dfn[anc[x]],dfn[x],1);
        x=fa[anc[x]];
    }
    ++Tnt;
    t.modify(t.root[Tnt],t.root[Tnt-1],1,n+10,dfn[anc[x]],dfn[x],1);
}
ll query(int x,int v){
    int tmp=x;
    ll ret=0;
    while(anc[x]!=1){
        ret+=t.query(t.root[v],1,n+10,dfn[anc[x]],dfn[x]);
        x=fa[anc[x]];
    }
    ret+=t.query(t.root[v],1,n+10,dfn[anc[x]],dfn[x]);
    //printf("query(%d,%d) = %lld\n",tmp,v,ret);
    return ret;
}
int find(int x){
    int l=1,r=n,mid,rt=-1;
    while(l<=r){
        mid=(l+r)>>1;
        if(a[mid].w<=x){
            rt=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return rt;
}
int findx(int x){
    int l=1,r=n,mid,rt=-1;
    while(l<=r){
        mid=(l+r)>>1;
        if(a[mid].w>=x){
            rt=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return rt;
}
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
    for(int i=1;i<=n;i++){
        s[i]=s[i-1]+dis[rdn[i]]-dis[fa[rdn[i]]];
    }
    /*for(int i=1;i<=n;i++){
        printf("rdn[%d] = %d\n",i,rdn[i]);
    }
    cout << endl;
    t.modify(t.root[1],t.root[0],1,n+10,3,5,1);
    t.modify(t.root[2],t.root[1],1,n+10,2,4,1);
    t.modify(t.root[3],t.root[2],1,n+10,2,5,1);
    cout << t.query(t.root[3],1,n+10,1,5);*/
    sort(a+1,a+1+n,cmp);
    /*for(int i=1;i<=n;i++){
        printf("%d ",a[i].w);
    }
    puts("");*/
    for(int i=1;i<=n;i++){
        toroot(a[i].id);
        ver[i]=Tnt;
        pre[i]=pre[i-1]+dis[a[i].id];
    }
    ll a,b,l,r;
    ll ans=0;
    while(Q--){
        u=geti();a=geti();b=geti();
        l=min((a+ans)%A,(b+ans)%A);
        r=max((a+ans)%A,(b+ans)%A);
        //printf("l = %lld, r = %lld\n",l,r);
        l=findx(l);r=find(r);
        //printf("l = %lld, r = %lld\n",l,r);
        ans=0;
        ans+=pre[r]-pre[l-1];
        //printf("pre[%lld] = %lld, pre[%lld] = %lld\n",r,pre[r],l-1,pre[l-1]);
        ans-=query(u,ver[r])*2;
        ans+=query(u,ver[l-1])*2;
        ans+=(r-l+1)*dis[u];
        printf("%lld\n",ans);
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
