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
const int maxn = 500;
const int maxm = 1000000;
int st[maxn],pt[maxm],nxt[maxm],flow[maxm],cap[maxm],cost[maxm],dis[maxn],fa[maxn],fae[maxn],q[maxm],ent=1;
int m,n,s,t;
int cst=0;
char vis[maxn];
struct node{
    int u,v,c;
}a[maxn][maxn];
void connect(int u,int v,int c,int mf){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;flow[ent]=0;cap[ent]=mf;cost[ent]=-c;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;flow[ent]=0;cap[ent]=0;cost[ent]=c;
}
bool spfa(){
    memset(dis,127/3,sizeof(dis));
    memset(vis,0,sizeof(vis));
    int hd=0,tl=0;
    q[++tl]=s;dis[s]=0;
    while(hd<tl){
        int r=q[++hd];
        vis[r]=false;
        for(int i=st[r];i;i=nxt[i]){
            if(cap[i]>flow[i]){
                if(dis[pt[i]]>dis[r]+cost[i]){
                    fa[pt[i]]=r;fae[pt[i]]=i;
                    dis[pt[i]]=dis[r]+cost[i];
                    if(!vis[pt[i]]){
                        vis[pt[i]]=true;
                        q[++tl]=pt[i];
                    }
                }
            }
        }
    }
    if(dis[t]<707406378){
        int u=t;
        int minf=2147483640;
        while(u!=s){
            minf=min(minf,cap[fae[u]]-flow[fae[u]]);
            u=fa[u];
        }
        u=t;
        while(u!=s){
            flow[fae[u]]+=minf;flow[fae[u]^1]-=minf;
            u=fa[u];
        }
        cst+=minf*dis[t];
        return true;
    }
    return false;
}
int main(){
    m=geti();n=geti();
    int c;
    int pnt;
    pnt=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i+m-1;j++){
            a[i][j].u=++pnt;a[i][j].v=++pnt;a[i][j].c=geti();
        }
    }
    s=++pnt,t=++pnt;
    //Q1
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i+m-1;j++){
            connect(a[i][j].v,a[i][j].u,a[i][j].c,1);
        }
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=i+m-1;j++){
            connect(a[i][j].u,a[i+1][j].v,0,1);
            connect(a[i][j].u,a[i+1][j+1].v,0,1);
        }
    }
    for(int i=1;i<=m;i++){
        connect(s,a[1][i].v,0,1);
    }
    for(int i=1;i<=n+m-1;i++){
        connect(a[n][i].u,t,0,1);
    }
    cst=0;
    while(spfa());
    cout << -cst << endl;
    //Q2
    memset(st,0,sizeof(st));memset(flow,0,sizeof(flow));ent=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i+m-1;j++){
            connect(a[i][j].v,a[i][j].u,a[i][j].c,2147483640);
        }
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=i+m-1;j++){
            connect(a[i][j].u,a[i+1][j].v,0,1);
            connect(a[i][j].u,a[i+1][j+1].v,0,1);
        }
    }
    for(int i=1;i<=m;i++){
        connect(s,a[1][i].v,0,1);
    }
    for(int i=1;i<=n+m-1;i++){
        connect(a[n][i].u,t,0,2147483640);
    }
    cst=0;
    while(spfa());
    cout << -cst << endl;
    //Q3
    memset(st,0,sizeof(st));memset(flow,0,sizeof(flow));ent=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i+m-1;j++){
            connect(a[i][j].v,a[i][j].u,a[i][j].c,2147483640);
        }
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=i+m-1;j++){
            connect(a[i][j].u,a[i+1][j].v,0,2147483640);
            connect(a[i][j].u,a[i+1][j+1].v,0,2147483640);
        }
    }
    for(int i=1;i<=m;i++){
        connect(s,a[1][i].v,0,1);
    }
    for(int i=1;i<=n+m-1;i++){
        connect(a[n][i].u,t,0,2147483640);
    }
    cst=0;
    while(spfa());
    cout << -cst << endl;
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
