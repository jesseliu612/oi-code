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
const int maxn = 10000;
const int maxm = 1000000;
int n,m;
int st[maxn],pt[maxm],nxt[maxm],rev[maxn],ent;
void adde(int u,int v){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;
}
int door[maxn][2];
int ns[maxn][2];
int dfn[maxn],low[maxn],stk[maxn],bel[maxn],tp,dnt,nnt;
char vis[maxn],ins[maxn];
void tarjan(int x){
    dfn[x]=++dnt;low[x]=dfn[x];
    vis[x]=true;ins[x]=true;
    stk[++tp]=x;
    for(int i=st[x];i;i=nxt[i]){
        if(!vis[pt[i]]){
            tarjan(pt[i]);
            low[x]=min(low[x],low[pt[i]]);
        }
        else if(ins[pt[i]]){
            low[x]=min(low[x],dfn[pt[i]]);
        }
    }
    if(dfn[x]==low[x]){
        ++nnt;
        while(stk[tp]!=x){
            bel[stk[tp]]=nnt;
            ins[stk[tp]]=false;
            --tp;
        }
        bel[stk[tp]]=nnt;
        ins[stk[tp]]=false;
        --tp;
    }
}
bool check(int ans){
    memset(st,0,sizeof(st));memset(vis,0,sizeof(vis));memset(ins,0,sizeof(ins));
    ent=1;dnt=0;tp=0;nnt=0;
    for(int i=1;i<=ans;i++){
        for(int x=0;x<2;x++){
            for(int j=i+1;j<=ans;j++){
                for(int y=0;y<2;y++){
                    if(door[i][x]==rev[door[j][y]]){
                        adde(ns[i][x],ns[j][y^1]);
                        adde(ns[j][y],ns[i][x^1]);
                    }
                }
            }
        }
    }
    for(int i=1;i<=ans;i++){
        if(!vis[ns[i][0]])tarjan(ns[i][0]);
        if(!vis[ns[i][1]])tarjan(ns[i][1]);
    }
    for(int i=1;i<=ans;i++){
        if(bel[ns[i][0]]==bel[ns[i][1]])return false;
    }
    return true;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    while(scanf("%d%d",&n,&m)==2){
        if(n==0 || m==0)break;
        memset(st,0,sizeof(st));
        int u,v;
        int pnt=0;
        for(int i=1;i<=n;i++){
            u=geti();v=geti();
            rev[u]=v;rev[v]=u;
        }
        for(int i=1;i<=m;i++){
            u=geti();v=geti();
            door[i][0]=u;door[i][1]=v;
            ns[i][0]=++pnt;ns[i][1]=++pnt;
        }
        int l=1,r=m,rt=-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid)){
                rt=mid;
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        printf("%d\n",rt);
    }
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
