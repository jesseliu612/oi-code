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
const int maxn = 10000;
const int maxm = 1000000;
int st[maxn],pt[maxm],nxt[maxm],cap[maxm],flow[maxm],q[maxn],d[maxn],ent=1;
int n,m,s,t,pnt;
int ns[maxn];
struct Dx{
    int id;
    ll v;
}wt[maxn];
struct edge{
    int u,v;
}e[maxm];
void adde(int u,int v,int fl){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;flow[ent]=0;cap[ent]=fl;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;flow[ent]=0;cap[ent]=0;
}
bool bfs(){
    int hd=0,tl=0;
    memset(d,-1,sizeof(d));
    d[s]=0;
    q[++tl]=s;
    while(hd<tl){
        int r=q[++hd];
        if(r==t)return true;
        for(int i=st[r];i;i=nxt[i]){
            if(flow[i]>=cap[i])continue;
            if(d[pt[i]]!=-1)continue;
            d[pt[i]]=d[r]+1;
            q[++tl]=pt[i];
        }
    }
    return false;
}
int dfs(int x,int a){
    if(x==t || a==0)return a;
    int f,fl=0,bef=a;
    for(int i=st[x];i;i=nxt[i]){
        if(flow[i]>=cap[i] || d[pt[i]]!=d[x]+1)continue;
        if((f=dfs(pt[i],min(a,cap[i]-flow[i])))>0){
            fl+=f;flow[i]+=f;flow[i^1]-=f;a-=f;
            if(a==0)break;
        }
    }
    if(a==bef)d[x]=-1;
    return fl;
}
ll dinic(){
    ll res=0;
    while(bfs()){
        res+=dfs(s,inf);
    }
    return res;
}
int main(){
    freopen("optimalmarks.in","r",stdin);
    freopen("optimalmarks.out","w",stdout);

    pnt=0;
    n=geti();m=geti();
    for(int i=1;i<=n;i++){
        ns[i]=++pnt;
    }
    s=++pnt;t=++pnt;
    for(int i=1;i<=m;i++){
        e[i].u=geti();e[i].v=geti();
    }
    int k=geti();
    for(int i=1;i<=k;i++){
        wt[i].id=geti();wt[i].v=geti();
    }
    ll ans=0;
    for(int ss=0;ss<=32;ss++){
        memset(st,0,sizeof(st));
        ent=1;
        for(int i=1;i<=m;i++){
            adde(ns[e[i].u],ns[e[i].v],1);
            adde(ns[e[i].v],ns[e[i].u],1);
        }
        for(int i=1;i<=k;i++){
            if(((wt[i].v)>>ss)&1){
                adde(s,ns[wt[i].id],inf);
            }
            else{
                adde(ns[wt[i].id],t,inf);
            }
        }
        ans+=dinic()*(1<<ss);
    }
    cout << ans;
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
