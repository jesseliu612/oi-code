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
int st[maxn],pt[maxm],nxt[maxm],flow[maxm],cap[maxm],pid[maxm],lm[maxm],ent;
void connect(int u,int v,int fl,int id){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;flow[ent]=0;cap[ent]=fl;
    pid[id]=ent;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;flow[ent]=0;cap[ent]=0;
}
void adde(int u,int v,int fl){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;flow[ent]=0;cap[ent]=fl;
    pt[++ent]=u;nxt[ent]=st[v];st[v]=ent;flow[ent]=0;cap[ent]=0;
}
int d[maxn],q[maxn];
bool bfs(){
    int hd=0,tl=0;
    memset(d,-1,sizeof(d));d[s]=0;q[++tl]=s;
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
    int T=geti();
    while(T--){
        n=geti();m=geti();ent=1;
        memset(st,0,sizeof(st));
        int u,v,l,c;
        int tot=0;
        s=n+1;t=n+2;
        for(int i=1;i<=m;i++){
            u=geti();v=geti();l=geti();c=geti();
            lm[i]=l;
            connect(u,v,c-l,i);
            adde(u,t,l);
            adde(s,v,l);
            tot+=l;
        }
        if(dinic()<tot){
            printf("NO\n\n");
            continue;
        }
        printf("YES\n");
        for(int i=1;i<=m;i++){
            printf("%d\n",flow[pid[i]]+lm[i]);
        }
        putchar('\n');
    }
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
