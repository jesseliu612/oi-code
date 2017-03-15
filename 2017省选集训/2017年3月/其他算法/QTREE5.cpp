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
int n,Q,op;
int st[maxn],pt[maxn*2],nxt[maxn*2],ent=0;
void adde(int u,int v){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;
}
int size[maxn],maxs[maxn],root,mins;
int fa[maxn],anc[maxn],dfn[maxn],bson[maxn],dep[maxn],bef[maxn],dnt=0;
char del[maxn];
void dfs(int x){
    size[x]=1;
    for(int i=st[x];i;i=nxt[i]){
        if(pt[i]==fa[x])continue;
        dep[pt[i]]=dep[x]+1;
        fa[pt[i]]=x;
        dfs(pt[i]);
        size[x]+=size[pt[i]];
        if(size[pt[i]]>size[bson[x]])bson[x]=pt[i];
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
int getdis(int u,int v){
    int ret=dep[u]+dep[v];
    while(anc[u]!=anc[v]){
        if(dep[anc[u]]<dep[anc[v]])swap(u,v);
        u=fa[anc[u]];
    }
    if(dep[u]>dep[v])swap(u,v);
    return ret-2*dep[u];
}
void getroot(int x,int tot,int f){
    size[x]=1,maxs[x]=0;
    for(int i=st[x];i;i=nxt[i]){
        if(del[pt[i]] || pt[i]==f)continue;
        getroot(pt[i],tot,x);
        size[x]+=size[pt[i]];
        maxs[x]=max(maxs[x],size[pt[i]]);
    }
    maxs[x]=max(maxs[x],tot-size[x]);
    if(maxs[x]<mins){
        mins=maxs[x];root=x;
    }
}
void build(int x){
    del[x]=true;
    for(int i=st[x];i;i=nxt[i]){
        if(del[pt[i]])continue;
        root=0;mins=inf;
        getroot(pt[i],size[pt[i]],x);
        bef[root]=x;
        build(root);
    }
}
struct node{
    int id,dis;
};
bool operator < (const node &x,const node &y){
    return x.dis>y.dis;
}   
priority_queue<node> q[maxn];
int col[maxn];
void modify(int x){
    if(col[x]){
        col[x]=0;return;
    }
    col[x]=1;
    int u=x;
    while(bef[u]){
        q[u].push((node){x,getdis(x,u)});
        u=bef[u];
    }
    q[u].push((node){x,getdis(x,u)});
}
int query(int x){
    int ret=inf;
    int u=x;
    while(bef[u]){
        while(!q[u].empty() && !col[q[u].top().id])q[u].pop();
        if(!q[u].empty()){
            ret=min(ret,q[u].top().dis+getdis(x,u));
        }
        u=bef[u];
    }
    while(!q[u].empty() && !col[q[u].top().id]){
        q[u].pop();
    }
    if(!q[u].empty()){
        ret=min(ret,q[u].top().dis+getdis(x,u));
    }
    if(ret==inf)return -1;
    return ret;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    
    n=geti();
    int u,v;
    for(int i=1;i<n;i++){
        u=geti();v=geti();
        adde(u,v);
    }

    dfs(1);df2(1,1);
    
    root=0;mins=inf;
    getroot(1,n,0);
    build(root);
    
    Q=geti();
    while(Q--){
        op=geti();v=geti();
        if(!op){
            modify(v);
        }
        else{
            printf("%d\n",query(v));
        }
    }
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
