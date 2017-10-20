#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int inf= 2147483640;
const int maxn = 1000000;
int n,m,pnt=1,s,t;
int ns[210][210];
int st[maxn],nxt[maxn],pt[maxn],flow[maxn],cap[maxn],d[maxn],ent=1;
int dx[9]={1,-1,2,-2,1,-1,2,-2};
int dy[9]={2,-2,1,-1,-2,2,-1,1};
int geti(){
    char ch=getchar();while((ch<'0' || ch>'9')&&ch!='-')ch=getchar();
    int ret=0,k=1;
    if(ch=='-')k=-1,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret*k;
}
void adde(int u,int v,int fl){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;flow[ent]=0;cap[ent]=fl;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;flow[ent]=0;cap[ent]=0;
}
queue<int> q;
bool bfs(){
    memset(d,-1,sizeof(d));
    q.push(s);d[s]=0;
    while(!q.empty()){
        int r=q.front();q.pop();
        for(int i=st[r];i;i=nxt[i]){
            if(flow[i]>=cap[i])continue;
            if(d[pt[i]]==-1){
                d[pt[i]]=d[r]+1;
                q.push(pt[i]);
            }
        }
    }
    if(d[t]!=-1)return true;
    return false;
}
int dfs(int x,int a){
    if(x==t || a==0)return a;
    int f,fl=0,bef=a;
    for(int i=st[x];i;i=nxt[i]){
        if(flow[i]>=cap[i] || d[x]!=d[pt[i]]-1)continue;
        if((f=dfs(pt[i],min(a,cap[i]-flow[i])))>0){
            fl+=f;flow[i]+=f;flow[i^1]-=f;
            a-=f;
            if(a==0)break;
        }
    }
    if(a==bef)d[x]=-1;
    return fl;
}
int dinic(){
    int ret=0;
    while(bfs()){
        ret+=dfs(s,inf);
    }
    return ret;
}
char col[210][210];
char del[210][210];
bool check(int x,int y){
    if(x<1 || x>n || y<1 || y>n)return false;
    if(del[x][y])return false;
    return true;
}
int main(){
    n=geti();m=geti();
    col[1][1]=0;
    int u,v;
    for(int i=1;i<=m;i++){
        u=geti();v=geti();del[u][v]=true;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(del[i][j])continue;
            ns[i][j]=++pnt;
        }
    }
    s=++pnt;t=++pnt;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(j==1)col[i][1]=col[i-1][1]^1;
            else col[i][j]=col[i][j-1]^1;
            if(!del[i][j]){
                if(col[i][j]){
                    adde(s,ns[i][j],1);
                }
                else{
                    adde(ns[i][j],t,1);
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(del[i][j])continue;
            if(!col[i][j])continue;
            for(int k=0;k<8;k++){
                u=i+dx[k];v=j+dy[k];
                if(!check(u,v))continue;
                adde(ns[i][j],ns[u][v],1);
            }
        }
    }
    int ret=dinic();
    cout << n*n-m-ret;
    return 0;
}
