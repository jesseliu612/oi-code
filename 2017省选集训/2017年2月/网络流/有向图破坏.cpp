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
const int maxn = 1000;
const int maxm = 50000;
int n,m,pnt=1,s,t;
int st[maxn],pt[maxm],nxt[maxm],flow[maxm],cap[maxm],d[maxn],q[maxm],ent=1;
void adde(int u,int v,int fl){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;flow[ent]=0;cap[ent]=fl;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;flow[ent]=0;cap[ent]=0;
}
struct node{
    int u,v;
}ns[maxn];
bool bfs(){
    memset(d,-1,sizeof(d));
    int hd=0,tl=0;
    q[++tl]=s;d[s]=0;
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
            fl+=f;flow[i]+=fl;flow[i^1]-=f;a-=f;
            if(a==0)break;
        }
    }
    if(bef==a)d[x]=-1;
    return fl;
}
int dinic(){
    int ret=0;
    while(bfs()){
        ret+=dfs(s,inf);
    }
    return ret;
}
int main(){
    n=geti();m=geti();
    for(int i=1;i<=n;i++){
        ns[i].u=++pnt;ns[i].v=++pnt;
    }
    s=++pnt;t=++pnt;
    int u,v;
    for(int i=1;i<=n;i++){
        u=geti();
        adde(ns[i].v,t,u);
    }
    for(int i=1;i<=n;i++){
        u=geti();
        adde(s,ns[i].u,u);
    }
    for(int i=1;i<=m;i++){
        u=geti();v=geti();
        adde(ns[u].u,ns[v].v,inf);
    }
    cout << dinic();
    fclose(stdin);
    fclose(stdout);
    return 0;
}
