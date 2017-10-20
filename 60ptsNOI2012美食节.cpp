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
const int maxn = 100000;
const int maxm = 5000000;
int n,m,s,t,pnt;
int st[maxn],pt[maxm],nxt[maxm],flow[maxm],cap[maxm],cost[maxm],dis[maxn],fa[maxn],fae[maxn],ent=1;
void adde(int u,int v,int fl,int c){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;flow[ent]=0;cap[ent]=fl;cost[ent]=c;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;flow[ent]=0;cap[ent]=0;cost[ent]=-c;
}
char vis[maxn];
queue<int> q;
int cst=0;
bool spfa(){
    memset(dis,127/3,sizeof(dis));
    dis[s]=0;q.push(s);
    while(!q.empty()){
        int r=q.front();q.pop();
        vis[r]=false;
        for(int i=st[r];i;i=nxt[i]){
            if(flow[i]>=cap[i])continue;
            if(dis[pt[i]]>dis[r]+cost[i]){
                fa[pt[i]]=r;fae[pt[i]]=i;
                dis[pt[i]]=dis[r]+cost[i];
                if(!vis[pt[i]]){
                    vis[pt[i]]=true;
                    q.push(pt[i]);
                }
            }
        }
    }
    if(dis[t]>=707406378)return false;
    int fl=1;
    int u=t;
    while(u!=s){
        flow[fae[u]]+=fl;flow[fae[u]^1]-=fl;
        u=fa[u];
    }
    cst+=dis[t]*fl;
    return true;
}
int ns[110][810],spd[110][50];
int nd[50],pd[5];
int main(){
    freopen("delicacy.in","r",stdin);
    freopen("delicacy.out","w",stdout);

    n=geti();m=geti();
    int sump=0;
    for(int i=1;i<=n;i++){
        pd[i]=geti();
        nd[i]=++pnt;
        sump+=pd[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            spd[j][i]=geti();
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=sump;j++){
            ns[i][j]=++pnt;
        }
    }
    s=++pnt;t=++pnt;
    for(int i=1;i<=n;i++){
        for(int k=1;k<=m;k++){
            for(int g=1;g<=sump;g++){
                adde(nd[i],ns[k][g],1,spd[k][i]*g);
            }
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=sump;j++){
            adde(ns[i][j],t,1,0);
        }
    }
    for(int i=1;i<=n;i++){
        adde(s,nd[i],pd[i],0);
    }
    cst=0;
    while(spfa());
    cout << cst;

    fclose(stdin);
    fclose(stdout);
    return 0;
}

