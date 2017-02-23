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
struct node{
    int u,v;
}ns[maxn];
int n,s,t,pnt=0;
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
        for(int i=1;i<=pnt;i++)cur[i]=st[i];
        flow+=dfs(s,inf);
    }
    return flow;
}
int main(){
    pnt=0;
    n=geti();
    for(int i=1;i<=n;i++){
        a[i]=geti();ns[i].u=++pnt;ns[i].v=++pnt;
    }
    s=++pnt;t=++pnt;
    dp[1]=1;
    for(int i=2;i<=n;i++){
        dp[i]=1;
        for(int j=1;j<i;j++){
            if(a[j]>a[i])continue;
            dp[i]=max(dp[i],dp[j]+1);
        }
    }
    int ans1=0;
    for(int i=1;i<=n;i++)ans1=max(ans1,dp[i]);
    cout << ans1 << "\n";
 
    //Q2
    for(int i=1;i<=n;i++){
        connect(ns[i].u,ns[i].v,1);
    }
    for(int i=1;i<=n;i++){
        if(dp[i]==1){
            connect(s,ns[i].u,1);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(a[i]<=a[j] && dp[i]+1==dp[j]){
                connect(ns[i].v,ns[j].u,1);
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(dp[i]==ans1){
            connect(ns[i].v,t,1);
        }
    }
    cout << dinic() << "\n";
    
    //Q3
    memset(st,0,sizeof(st));memset(nxt,0,sizeof(nxt));memset(flow,0,sizeof(flow));ent=1;
    connect(ns[1].u,ns[1].v,inf);
    for(int i=2;i<n;i++){
        connect(ns[i].u,ns[i].v,1);
    }
    connect(ns[n].u,ns[n].v,inf);
    for(int i=1;i<=n;i++){
        if(dp[i]==1){
            if(i!=1)connect(s,ns[i].u,1);
            else connect(s,ns[i].u,inf);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(a[i]<=a[j] && dp[i]+1==dp[j]){
                connect(ns[i].v,ns[j].u,1);
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(dp[i]==ans1){
            if(i!=n)connect(ns[i].v,t,1);
            else connect(ns[i].v,t,inf);
        }
    }
    cout << dinic();
    fclose(stdin);
    fclose(stdout);
    return 0;
}
