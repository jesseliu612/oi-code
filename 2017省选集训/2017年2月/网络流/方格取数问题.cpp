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
const int maxn = 2000000;
int n,m,s,t,pnt=1;
int st[maxn],pt[maxn],nxt[maxn],flow[maxn],cap[maxn],d[maxn],ent=1;
void adde(int u,int v,int fl){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;flow[ent]=0;cap[ent]=fl;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;flow[ent]=0;cap[ent]=0;
}
struct node{
    int u,v,c;
}ns[100][100];
queue<int> q;
bool bfs(){
    memset(d,-1,sizeof(d));
    d[s]=0;q.push(s);
    while(!q.empty()){
        int r=q.front();q.pop();
        for(int i=st[r];i;i=nxt[i]){
            if(flow[i]>=cap[i])continue;
            if(d[pt[i]]==-1){
                d[pt[i]]=d[r]+1;
                //if(pt[i]==t)return true;
                q.push(pt[i]);
            }
        }
    }
    if(d[t]!=-1)return true;
    return false;
}
int dfs(int x,int a){
    if(x==t || a==0)return a;
    int f,fl=0;
    int sum=a;
    for(int i=st[x];i;i=nxt[i]){
        if(flow[i]>=cap[i] || d[pt[i]]!=d[x]+1)continue;
        if((f=dfs(pt[i],min(a,cap[i]-flow[i])))>0){
            fl+=f;
            flow[i]+=f;flow[i^1]-=f;
            a-=f;
            if(a==0)break;
        }
    }
    if(a==sum)d[x]=-1;
    return fl;
}
int dinic(){
    int ret=0;
    while(bfs()){
        ret+=dfs(s,inf);
        //cout << "ret = " << ret << endl;
    }
    return ret;
}
char dvis[maxn];
void dfs(int x){
    dvis[x]=true;
    for(int i=st[x];i;i=nxt[i]){
        if(flow[i]>=cap[i])continue;
        if(!dvis[pt[i]]){
            dfs(pt[i]);
        }
    }
}
int main(){
    n=geti();m=geti();
    int tot=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            ns[i][j].u=++pnt;ns[i][j].v=++pnt;
            ns[i][j].c=geti();tot+=ns[i][j].c;
        }
    }
    s=++pnt;t=++pnt;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i>1)adde(ns[i][j].u,ns[i-1][j].v,inf);
            if(i<n)adde(ns[i][j].u,ns[i+1][j].v,inf);
            if(j>1)adde(ns[i][j].u,ns[i][j-1].v,inf);
            if(j<m)adde(ns[i][j].u,ns[i][j+1].v,inf);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            adde(s,ns[i][j].u,ns[i][j].c);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            adde(ns[i][j].v,t,ns[i][j].c);
        }
    }
    int ret=dinic();
    cout << tot-ret/2;
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
