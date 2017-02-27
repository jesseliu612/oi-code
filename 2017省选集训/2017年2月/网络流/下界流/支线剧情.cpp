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
const int maxm = 1000000;
int n,m;
int s,t;
int st[maxn],pt[maxm],nxt[maxm],flow[maxm],cap[maxm],cost[maxm],ent;
void connect(int u,int v,int fl,int cst){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;flow[ent]=0;cap[ent]=fl;cost[ent]=cst;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;flow[ent]=0;cap[ent]=0;cost[ent]=-cst;
}
int res=0,d[maxn],fa[maxn],fae[maxn];
char vis[maxn];
queue<int> q;
bool spfa(){
    memset(vis,0,sizeof(vis));
    memset(d,127/3,sizeof(d));
    int crc=d[0];
    q.push(s);d[s]=0;
    int flag=0;
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
    if(d[t]==crc)return false;
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
    res+=d[t]*fl;
    return true;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int n=geti();ent=1;
    s=n+1,t=n+2;
    for(int i=1;i<=n;i++){
        int k=geti();
        if(i!=1)connect(i,1,inf,0);
        connect(i,t,k,0);
        for(int j=1;j<=k;j++){
            int u=geti();int cc=geti();
            connect(i,u,inf,cc);
            connect(s,u,1,cc);
        }
    }
    res=0;
    while(spfa());
    cout << res;
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}

