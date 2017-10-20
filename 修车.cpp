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
const int inf = 707406378;
int s,t,n,m,pnt=1;
int st[maxn],pt[maxm],nxt[maxm],flow[maxm],cap[maxm],d[maxn],q[maxm],cost[maxm],ent=1;
int ts[20][70];
int ns[20][70],nc[70];
void adde(int u,int v,int fl,int cst){
    //cout << ent+1 << " " << u << " " << v << " " << fl << " " << cst << endl;
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;cap[ent]=fl;cost[ent]=cst;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;cap[ent]=0;cost[ent]=-cst;
}
char vis[maxn];
int fa[maxn],fae[maxn],res;
bool spfa(){
    memset(vis,0,sizeof(vis));
    memset(d,127,sizeof(d));
    int hd=0,tl=0;
    q[++tl]=s;d[s]=0;
    while(hd<tl){
        int r=q[++hd];
        vis[r]=false;
        for(int i=st[r];i;i=nxt[i]){
            if(flow[i]>=cap[i])continue;
            if(d[pt[i]]>d[r]+cost[i]){
                d[pt[i]]=d[r]+cost[i];
                fa[pt[i]]=r;fae[pt[i]]=i;
                if(!vis[pt[i]]){
                    q[++tl]=pt[i];
                    vis[pt[i]]=true;
                }
            }
        }
    }
    if(d[t]>2000000000)return false;
    int fl=1;
    int u=t;
    u=t;
    while(u!=s){
        flow[fae[u]]+=fl;flow[fae[u]^1]-=fl;
        u=fa[u];
    }
    res+=fl*d[t];
    //cout << "flow = " << fl << " , d = " << d[t] << endl;
    return true;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    m=geti();n=geti();
    pnt=0;
    for(int i=1;i<=n;i++){
        nc[i]=++pnt;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            ts[j][i]=geti();
            ns[j][i]=++pnt;
        }
    }
    s=++pnt;t=++pnt;
    //s -> car
    for(int i=1;i<=n;i++){
        adde(s,nc[i],1,0);
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            adde(ns[i][j],t,1,0);
        }
    }
    //cout << "%%%" << endl;
    //car -> worker
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=1;k<=n;k++){
                adde(nc[i],ns[j][k],1,ts[j][i]*k);
            }
        }
    }
    //cout << "%%%" << endl;
    //for each worker
    /*for(int i=1;i<=m;i++){
        for(int j=1;j<n;j++){
            adde(ns[i][j],ns[i][j+1],j,0);
        }
    }
    */
    //cout << "%%%" << endl;
    //worker -> t
    /*for(int i=1;i<=m;i++){
        adde(ns[i][n],t,n,0);
    }
    */
    res=0;
    while(spfa());
    /*for(int i=2;i<=ent;i++){
        if(flow[i]>0){
            cout << i << " " << flow[i] << " " << cost[i] << endl;
        }
    }
    cout << res << endl;*/
    printf("%.2lf",(double)res/n);
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
