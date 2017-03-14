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
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
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
const int maxn = 250000 + 1000;
int n;
int st[maxn],pt[maxn*2],nxt[maxn*2],w[maxn*2],ent=0;
int dep[maxn],dfn[maxn],fa[maxn],size[maxn],anc[maxn],bson[maxn],ed[maxn],dnt=0;
ll dis[maxn],cds[maxn];
void adde(int u,int v,int wt){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;w[ent]=wt;
}
void dfs(int x){
    size[x]=1;
    for(int i=st[x];i;i=nxt[i]){
        if(pt[i]==fa[x])continue;
        dep[pt[i]]=dep[x]+1;
        dis[pt[i]]=dis[x]+w[i];
        fa[pt[i]]=x;
        cds[pt[i]]=Min(cds[x],w[i]);
        dfs(pt[i]);
        size[x]+=size[pt[i]];
        if(size[pt[i]]>size[bson[x]])bson[x]=pt[i];
    }
}
void df2(int x,int a){
    dfn[x]=++dnt;anc[x]=a;
    if(bson[x]){
        df2(bson[x],a);
    }
    for(int i=st[x];i;i=nxt[i]){
        if(pt[i]==fa[x] || pt[i]==bson[x])continue;
        df2(pt[i],pt[i]);
    }
    ed[x]=dnt;
}
int lca(int u,int v){
    while(anc[u]!=anc[v]){
        if(dep[anc[u]]<dep[anc[v]])swap(u,v);
        u=fa[anc[u]];
    }
    return dep[u]>dep[v]?v:u;
}
int ns[maxn],stk[maxn];
char key[maxn];
ll mx[maxn];
char cmp(const int &x,const int &y){
    return dfn[x]<dfn[y];
}
void dp(int x,int f){
    ll tot=0;
    for(int i=st[x];i;i=nxt[i]){
        if(pt[i]==f)continue;
        dp(pt[i],x);
        tot+=mx[pt[i]];
    }
    if(key[x])mx[x]=cds[x];
    else mx[x]=min(cds[x],tot);
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    
    n=geti();
    memset(cds,0x7f,sizeof(cds));
    int u,v,wt;
    for(int i=1;i<n;i++){
        u=geti();v=geti();wt=geti();
        adde(u,v,wt);
        adde(v,u,wt);
    }
    dfs(1);
    df2(1,1);
    int Q=geti();
    while(Q--){
        ent=0;
        int k=geti();
        ++k;
        ns[1]=1;
        for(int i=2;i<=k;i++){
            ns[i]=geti();key[ns[i]]=true;
        }
        sort(ns+1,ns+1+k,cmp);
        int cnt=k;
        for(int i=1;i<=k;i++){
            ns[++cnt]=lca(ns[i],ns[i+1]);
        }
        sort(ns+1,ns+1+cnt,cmp);
        cnt = unique(ns+1,ns+1+cnt) - ns - 1;
        int top=0;
        for(int i=1;i<=cnt;i++){
            st[ns[i]]=0;
        }
        for(int i=1;i<=cnt;i++){
            while(top && !(dfn[stk[top]]<dfn[ns[i]] && dfn[ns[i]]<=ed[stk[top]]))--top;
            if(!top){
                stk[++top]=ns[i];
            }
            else{
                adde(ns[i],stk[top],dis[ns[i]]-dis[stk[top]]);
                adde(stk[top],ns[i],dis[ns[i]]-dis[stk[top]]);
                stk[++top]=ns[i];
            }
        }
        dp(1,0);
        for(int i=1;i<=cnt;i++)key[ns[i]]=false;
        printf("%lld\n",mx[1]);
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
