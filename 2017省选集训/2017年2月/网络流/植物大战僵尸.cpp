#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
const int inf = 2147483640;
using namespace std;
typedef long long ll;
ll geti(){
    char ch=getchar();while((ch<'0' || ch>'9')&&ch!='-')ch=getchar();
    ll ret=0,k=1;
    if(ch=='-')k=-1,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret*k;
}
const int maxn = 1000000;
int n,m,s,t,pnt;
char del[maxn];
//netflow
int st[maxn],pt[maxn],nxt[maxn],d[maxn],cur[maxn],ent=1;
ll flow[maxn],cap[maxn];
int p[maxn];
int ns[100][100];
char vis[maxn],rev[maxn];
queue<int> q;
void connect(int u,int v,ll fl){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;flow[ent]=0;cap[ent]=fl;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;flow[ent]=0;cap[ent]=0;rev[ent]=true;
}
bool bfs(){
    d[s]=0;
    memset(vis,0,sizeof(vis));
    q.push(s);vis[s]=true;
    while(!q.empty()){
        int r=q.front();q.pop();
        if(del[r])continue;
        for(int i=st[r];i;i=nxt[i]){
            if(flow[i]>=cap[i])continue;
            if(vis[pt[i]])continue;
            vis[pt[i]]=true;
            d[pt[i]]=d[r]+1;
            q.push(pt[i]);
        }
    }
    if(vis[t])return true;
    return false;
}
ll dfs(int x,ll a){
    if(del[x])return 0;
    if(x==t || a==0)return a;
    //printf("dfs(%d,%lld)\n",x,a);
    ll f,fl=0;
    for(int &i=cur[x];i;i=nxt[i]){
        if(flow[i]>=cap[i] || d[pt[i]]!=d[x]+1)continue;
        if((f=dfs(pt[i],min(a,cap[i]-flow[i])))>0){
            flow[i]+=f;flow[i^1]-=f;
            a-=f;fl+=f;
            if(a==0)break;
        }
    }
    return fl;
}
ll dinic(){
    ll ret=0;
    while(bfs()){
        for(int i=1;i<=pnt;i++)cur[i]=st[i];
        ret+=dfs(s,inf);
    }
    return ret;
}
//tarjan
int stk[maxn],low[maxn],dfn[maxn],dnt=0,top=0;
char tvis[maxn],instack[maxn];
void tarjan(int x){
    //printf("tarjan(%d)\n",x);
    dfn[x]=++dnt;low[x]=dfn[x];
    stk[++top]=x;
    tvis[x]=true;
    instack[x]=true;
    for(int i=st[x];i;i=nxt[i]){
        if(pt[i]==s || pt[i]==t)continue;
        if(rev[i])continue;
        if(instack[pt[i]]){
            //printf("  1 : <%d,%d>\n",x,pt[i]);
            low[x]=min(low[x],dfn[pt[i]]);
        }
        else if(!tvis[pt[i]]){
            //printf("  2 : <%d,%d>\n",x,pt[i]);
            tarjan(pt[i]);
            low[x]=min(low[x],low[pt[i]]);
        }
    }
    if(dfn[x]==low[x]){
        if(stk[top]!=x){
            while(stk[top]!=x){
                del[stk[top]]=true;
                instack[stk[top]]=false;
                --top;
            }
            del[stk[top]]=true;
            instack[stk[top]]=false;
            --top;
        }
        else{
            instack[stk[top]]=false;
            --top;
        }
    }
    //printf("endtarjan(%d)\n",x);
}
void df2(int x){
    if(x==s || x==t)return;
    del[x]=true;
    vis[x]=true;
    for(int i=st[x];i;i=nxt[i]){
        if(!rev[i])continue;
        if(vis[pt[i]])continue;
        df2(pt[i]);
    }
}
int main(){
    n=geti();m=geti();
    pnt=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            ns[i][j]=++pnt;
        }
    }
    s=++pnt;t=++pnt;
    for(int i=0;i<n;i++){
        for(int j=1;j<m;j++){
            connect(ns[i][j-1],ns[i][j],inf);
        }
    }
    int tot=0;
    int sum,u,v,c;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            c=geti();p[ns[i][j]]=c;
            if(c>=0){
                connect(s,ns[i][j],c);
                tot+=c;
            }
            else{
                connect(ns[i][j],t,-c);
            }
            sum=geti();
            for(int k=1;k<=sum;k++){
                u=geti();v=geti();
                connect(ns[u][v],ns[i][j],inf);
            }
        }
    }
    memset(tvis,0,sizeof(tvis));
    for(int i=1;i<=pnt;i++){
        if(i==s || i==t)continue;
        if(!tvis[i])tarjan(i);
    }
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=pnt;i++){
        if(i==s || i==t)continue;
        if(del[i]){
            if(!vis[i])df2(i);
        }
    }
    for(int i=1;i<=pnt;i++){
        if(i==s || i==t)continue;
        if(del[i] && p[i]>0){
            tot-=p[i];
        }
    }
    int ret=dinic();
    cout << tot-ret;
    
    return 0;
}
