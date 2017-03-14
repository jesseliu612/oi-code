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
const int inf = 214748364;
typedef long long ll;
ll geti(){
    char ch=getchar();while((ch<'0' || ch>'9')&&ch!='-')ch=getchar();
    ll ret=0,k=1;
    if(ch=='-')k=-1,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret*k;
}
const int maxn = 1000000 + 1000;
int st[maxn],pt[maxn*2],nxt[maxn*2],w[maxn*2],ent=0;
void adde(int u,int v,int wt){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;w[ent]=wt;
}
int n;
int fa[maxn],anc[maxn],dep[maxn],dfn[maxn],bson[maxn],size[maxn],ed[maxn],dnt=0;
void dfs(int x){
    size[x]=1;
    for(int i=st[x];i;i=nxt[i]){
        if(pt[i]==fa[x])continue;
        fa[pt[i]]=x;
        dep[pt[i]]=dep[x]+w[i];
        dfs(pt[i]);
        size[x]+=size[pt[i]];
        if(size[pt[i]]>size[bson[x]])bson[x]=pt[i];
    }
}
void df2(int x,int a){
    anc[x]=a;
    dfn[x]=++dnt;
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
bool cmp(const int &x,const int &y){
    return dfn[x]<dfn[y];
}
int sz[maxn],ld[maxn],mind[maxn],k;
ll tot;
int ldis,minc;
void dp(int x,int f){
    sz[x]=key[x]?1:0;
    int sec=0;
    for(int i=st[x];i;i=nxt[i]){
        if(pt[i]==f)continue;
        dp(pt[i],x);
        tot+=(ll)w[i]*sz[pt[i]]*(k-sz[pt[i]]);
        sz[x]+=sz[pt[i]];
        if(ld[pt[i]]+w[i]>ld[x]){
            sec=ld[x];
            ld[x]=ld[pt[i]]+w[i];
        }
        else if(ld[pt[i]]+w[i]>sec){
            sec=ld[pt[i]]+w[i];
        }
    }
    ldis=max(ldis,ld[x]+sec);
    int cur=inf;
    if(key[x]){
        mind[x]=0;
        for(int i=st[x];i;i=nxt[i]){
            if(pt[i]==f)continue;
            cur=min(cur,mind[pt[i]]+w[i]);
        }
    }
    else{
        int min1=inf,min2=inf;
        mind[x]=inf;
        for(int i=st[x];i;i=nxt[i]){
            if(pt[i]==f)continue;
            if(mind[pt[i]]+w[i]<min1){
                min2=min1;
                min1=mind[pt[i]]+w[i];
            }
            else if(mind[pt[i]]+w[i]<min2){
                min2=mind[pt[i]]+w[i];
            }
        }
        mind[x]=min1;
        cur=min1+min2;
    }
    minc=min(minc,cur);
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    n=geti();
    int u,v;
    for(int i=1;i<n;i++){
        u=geti();v=geti();
        adde(u,v,1);adde(v,u,1);
    }
    dfs(1);
    df2(1,1);
    int Q=geti();
    while(Q--){
        ent=0;
        k=geti();
        for(int i=1;i<=k;i++){
            ns[i]=geti();
            key[ns[i]]=true;
        }
        sort(ns+1,ns+1+k,cmp);
        int cnt=k;
        for(int i=1;i<=k;i++){
            ns[++cnt]=lca(ns[i],ns[i+1]);
        }
        sort(ns+1,ns+1+cnt,cmp);
        cnt=unique(ns+1,ns+1+cnt)-ns-1;
        int top=0;
        for(int i=1;i<=cnt;i++){
            st[ns[i]]=0;
            while(top && (dfn[stk[top]]>dfn[ns[i]] || ed[stk[top]]<dfn[ns[i]]))--top;
            if(!top){
                stk[++top]=ns[i];
            }
            else{
                adde(stk[top],ns[i],dep[ns[i]]-dep[stk[top]]);
                adde(ns[i],stk[top],dep[ns[i]]-dep[stk[top]]);
                stk[++top]=ns[i];
            }
        }
        tot=0;minc=inf;ldis=0;
        dp(ns[1],0);
        for(int i=1;i<=cnt;i++)key[ns[i]]=false,sz[ns[i]]=0,ld[ns[i]]=0,mind[ns[i]]=0;
        printf("%lld %d %d\n",tot,minc,ldis);
    }
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
