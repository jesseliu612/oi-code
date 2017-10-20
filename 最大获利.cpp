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
typedef int ll;
ll geti(){
    char ch=getchar();while((ch<'0' || ch>'9')&&ch!='-')ch=getchar();
    ll ret=0,k=1;
    if(ch=='-')k=-1,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret*k;
}
const int maxn = 1000000;
int n,m,s,t,cst;
int st[maxn],pt[maxn],nxt[maxn],q[maxn],d[maxn],cur[maxn],ent=1;
int flow[maxn],cap[maxn];
int dp[maxn],a[maxn];
char vis[maxn];
void connect(int u,int v,int mf){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;flow[ent]=0;cap[ent]=mf;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;flow[ent]=0;cap[ent]=0;
}
bool bfs(){
    memset(vis,0,sizeof(vis));
    int hd=0,tl=0;
    q[++tl]=s;d[s]=0;vis[s]=true;
    while(hd<tl){
        int r=q[++hd];
        for(int i=st[r];i;i=nxt[i]){
            if(flow[i]>=cap[i])continue;
            if(!vis[pt[i]]){
                vis[pt[i]]=true;
                d[pt[i]]=d[r]+1;
                q[++tl]=pt[i];
            }
        }
    }
    if(vis[t])return true;
    return false;
}
int dfs(int x,ll a){
    if(x==t || a==0)return a;
    ll f,fl=0;
    for(int &i=cur[x];i;i=nxt[i]){
        if(flow[i]>=cap[i] || d[pt[i]]!=d[x]+1)continue;
        if((f=dfs(pt[i],min(a,cap[i]-flow[i])))>0){
            fl+=f;
            flow[i]+=f;flow[i^1]-=f;
            a-=f;
            if(a==0)break;
        }
    }
    return fl;
}
ll dinic(){
    ll flow=0;
    while(bfs()){
        for(int i=1;i<=n+m+2;i++)cur[i]=st[i];
        flow+=dfs(s,inf);
    }
    return flow;
}
int main(){
    n=geti();m=geti();
    int x1,x2,c;
    s=m+n+1;t=n+m+2;
    for(int i=1;i<=n;i++){
        c=geti();
        connect(i,t,c);
    }
    int tot=0;
    for(int i=1;i<=m;i++){
        x1=geti();x2=geti();c=geti();
        connect(s,n+i,c);
        connect(n+i,x1,inf);
        connect(n+i,x2,inf);
        tot+=c;
    }
    printf("%d",tot-dinic());
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
