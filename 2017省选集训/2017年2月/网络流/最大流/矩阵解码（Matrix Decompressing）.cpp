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
const int maxm = 500000;
int n,m,pnt,s,t;
int nr[50],nl[50],ns[50][50][2],peg[50][50],rp[50],lp[50];
int st[maxm],pt[maxm],nxt[maxm],flow[maxm],cap[maxm],ent;
void adde(int u,int v,int fl){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;flow[ent]=0;cap[ent]=fl;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;flow[ent]=0;cap[ent]=0;
}
void connect(int u,int v,int fl,int x,int y){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;flow[ent]=0;cap[ent]=fl;
    peg[x][y]=ent;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;flow[ent]=0;cap[ent]=0;
}
int q[maxm],d[maxm];
bool bfs(){
    int hd=0,tl=0;
    memset(d,-1,sizeof(d));
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
            fl+=f;flow[i]+=f;flow[i^1]-=f;a-=f;
            if(a==0)break;
        }
    }
    if(a==bef)d[x]=-1;
    return fl;
}
int dinic(){
    int res=0;
    while(bfs()){
        res+=dfs(s,inf);
    }
    return res;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int T=geti();int cs=0;
    while(T--){
        memset(st,0,sizeof(st));
        pnt=0;ent=1;
        n=geti();m=geti();
        for(int i=1;i<=n;i++)nr[i]=++pnt;
        for(int i=1;i<=m;i++)nl[i]=++pnt;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                ns[i][j][0]=++pnt;ns[i][j][1]=++pnt;
            }
        }
        s=++pnt;t=++pnt;
        for(int i=1;i<=n;i++){
            rp[i]=geti();adde(s,nr[i],rp[i]-rp[i-1]-m);
        }
        for(int i=1;i<=m;i++){
            lp[i]=geti();adde(nl[i],t,lp[i]-lp[i-1]-n);
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                adde(nr[i],ns[i][j][0],inf);
                connect(ns[i][j][0],ns[i][j][1],19,i,j);
                adde(ns[i][j][1],nl[j],inf);
            }
        }
        dinic();
        ++cs;
        printf("Matrix %d\n",cs);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                printf("%d ",flow[peg[i][j]]+1);
            }
            puts("");
        }
        puts("");
    }
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
