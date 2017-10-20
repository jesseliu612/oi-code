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
const int maxn = 6000;
const int maxm = 60000;
int n,m,s,t,pnt=0;
int ns[maxn];
int st[maxn],nxt[maxm],pt[maxm],flow[maxm],cap[maxm],cost[maxm],d[maxn],ent=1;
void adde(int u,int v,int fl,int cst){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;flow[ent]=0;cap[ent]=fl;cost[ent]=cst;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;flow[ent]=0;cap[ent]=0;cost[ent]=-cst;
}
queue<int> q;
char vis[maxn];
int res,fa[maxn],fae[maxn];
bool spfa(){
    memset(d,127/3,sizeof(d));
    q.push(s);d[s]=0;
    while(!q.empty()){
        int r=q.front();q.pop();
        vis[r]=false;
        for(int i=st[r];i;i=nxt[i]){
            if(flow[i]>=cap[i])continue;
            if(d[pt[i]]>d[r]+cost[i]){
                d[pt[i]]=d[r]+cost[i];
                fa[pt[i]]=r;fae[pt[i]]=i;
                if(!vis[pt[i]]){
                    vis[pt[i]]=true;
                    q.push(pt[i]);
                }
            }
        }
    }
    if(d[t]>=707406378)return false;
    int u=t,fl=inf;
    while(u!=s){
        fl=min(fl,cap[fae[u]]-flow[fae[u]]);
        u=fa[u];
    }
    u=t;
    while(u!=s){
        flow[fae[u]]+=fl;flow[fae[u]^1]-=fl;
        u=fa[u];
    }
    res+=fl*d[t];
    return true;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    n=geti();m=geti();
    for(int i=1;i<=n+1;i++){
        ns[i]=++pnt;
    }
    s=++pnt;t=++pnt;
    adde(s,ns[1],inf,0);
    for(int i=1;i<=n;i++){
        adde(ns[i],ns[i+1],inf-geti(),0);
    }
    res=0;
    int u,v,c;
    for(int i=1;i<=m;i++){
        u=geti();v=geti();c=geti();
        adde(u,v+1,inf,c);
    }
    adde(ns[n+1],t,inf,0);
    while(spfa());
    cout << res;
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
