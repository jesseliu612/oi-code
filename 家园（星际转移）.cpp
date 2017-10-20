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
const int maxm = 5000000;
const int maxn = 10000;
const int maxt = 50;
int n,m,k,pnt=1,s,t;
int st[maxn],pt[maxm],nxt[maxm],cap[maxm],flow[maxm],d[maxn],q[maxn],ent=1;
int boat[30][30],bs[30],psg[maxn];
int ns[30][60];
void adde(int u,int v,int fl){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;flow[ent]=0;cap[ent]=fl;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;flow[ent]=0;cap[ent]=0;
}
bool bfs(){
    int hd=0,tl=0;
    q[++tl]=s;
    memset(d,-1,sizeof(d));
    d[s]=0;
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
    if(d[t]!=-1)return true;
    return false;
}
int dfs(int x,int a){
    if(x==t || a==0)return a;
    int f,fl=0,bef=a;
    for(int i=st[x];i;i=nxt[i]){
        if(flow[i]>=cap[i] || d[x]+1!=d[pt[i]])continue;
        if((f=dfs(pt[i],min(a,cap[i]-flow[i])))>0){
            fl+=f;flow[i]+=f;flow[i^1]-=f;a-=f;
            if(a==0)break;
        }
    }
    if(a==bef)d[x]=-1;
    return fl;
}
int dinic(){
    int ret=0,res=2;
    while(bfs()){
        res=d[t];
        ret+=dfs(s,inf);
    }
    return res;
}
int main(){
    n=geti();m=geti();k=geti();
    for(int i=1;i<=m;i++){
        psg[i]=geti();
        bs[i]=geti();
        for(int j=0;j<bs[i];j++){
            boat[i][j]=geti()+2;
        }
    }
    //number the nodes
    for(int j=0;j<=maxt;j++){
        for(int i=1;i<=n+2;i++){
            ns[i][j]=++pnt;
            if(j)adde(ns[i][j-1],ns[i][j],inf);
        }
    }
    s=++pnt;t=++pnt;
    //edge
    //s -> earth
    adde(s,ns[2][0],k);
    //boats
    for(int i=1;i<=m;i++){
        for(int j=1;j<=maxt;j++){
            adde(ns[boat[i][(j-1)%bs[i]]][j-1],ns[boat[i][j%bs[i]]][j],psg[i]);
        }
    }
    //moon -> t
    for(int j=0;j<=maxt;j++){
        adde(ns[1][j],t,inf);
    }
    
    cout << dinic()-2;
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
