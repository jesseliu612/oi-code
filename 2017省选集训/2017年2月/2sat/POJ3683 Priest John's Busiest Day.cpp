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
const int maxn = 2100;
const int maxm = maxn*maxn;
int n;
int s[maxn][2],d[maxn],ns[maxn][2];
int st[maxn],pt[maxm],nxt[maxm],rev[maxn],ent;
struct eg{
    int u,v;
}e[maxm];
void adde(int u,int v){
    //printf("adde(%d,%d)\n",u,v);
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;e[ent].u=u;e[ent].v=v;
}
void connect(int u,int v){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;
}
int dfn[maxn],low[maxn],stk[maxn],tp,dnt;
char vis[maxn],ins[maxn];
int bel[maxn],nnt=0,du[maxn];
void tarjan(int x){
    //printf("tarjan(%d)\n",x);
    dfn[x]=++dnt;low[x]=dfn[x];
    vis[x]=true;
    ins[x]=true;
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
    //printf("low[%d] = %d, dfn[%d] = %d\n",x,low[x],x,dfn[x]);
    if(low[x]==dfn[x]){
        ++nnt;
        while(stk[tp]!=x){
            bel[stk[tp]]=nnt;
            //printf("bel[%d] = %d\n",stk[tp],bel[stk[tp]]);
            ins[stk[tp]]=false;
            tp--;
        }
        bel[stk[tp]]=nnt;
        ins[stk[tp]]=false;
        tp--;
    }
    //printf("endtarjan(%d)\n",x);
}
char ncz[maxn];
void dfs(int x){
    ncz[x]=true;
    for(int i=st[x];i;i=nxt[i]){
        dfs(pt[i]);
    }
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    while(scanf("%d",&n)==1){
        memset(st,0,sizeof(st));
        int pnt=1;tp=0,dnt=0,nnt=0,ent=1;
        for(int i=1;i<=n;i++){
            ns[i][0]=++pnt;ns[i][1]=++pnt;
        }
        for(int i=1;i<=n;i++){
            s[i][0]=geti();s[i][0]=s[i][0]*60+geti();
            s[i][1]=geti();s[i][1]=s[i][1]*60+geti();
            d[i]=geti();s[i][1]-=d[i];
        }
        for(int i=1;i<=n;i++){
            for(int x=0;x<2;x++){
                for(int j=i+1;j<=n;j++){
                    for(int y=0;y<2;y++){
                        if((s[j][y]>=s[i][x] && s[j][y]<s[i][x]+d[i]) || (s[i][x]>=s[j][y] && s[i][x]<s[j][y]+d[j])){
                            adde(ns[i][x],ns[j][y^1]);
                            adde(ns[j][y],ns[i][x^1]);
                        }
                    }
                }
            }
        }
        memset(vis,0,sizeof(vis));
        int flag=0;
        for(int i=2;i<=pnt;i++){
            if(!vis[i]){
                tarjan(i);
            }
        }
        for(int i=1;i<=n;i++){
            if(bel[ns[i][0]]==bel[ns[i][1]]){
                flag=1;
            }
            else{
                rev[bel[ns[i][0]]]=bel[ns[i][1]];
                rev[bel[ns[i][1]]]=bel[ns[i][0]];
            }
        }
        if(flag==1){
            printf("NO\n");
        }
        else{
            printf("YES\n");
            int me=ent;
            ent=1;
            memset(st,0,sizeof(st));
            memset(du,0,sizeof(du));
            for(int i=1;i<=me;i++){
                if(bel[e[i].v]!=bel[e[i].u]){
                    connect(bel[e[i].v],bel[e[i].u]);
                    du[bel[e[i].u]]++;
                }
            }
            tp=0;
            for(int i=1;i<=nnt;i++){
                if(du[i]==0){
                    stk[++tp]=i;
                }
            }
            memset(ncz,0,sizeof(ncz));
            while(tp){
                int r=stk[tp--];
                if(ncz[r])continue;
                for(int i=st[r];i;i=nxt[i]){
                    du[pt[i]]--;
                    if(du[pt[i]]==0){
                        stk[++tp]=pt[i];
                    }
                }
                dfs(rev[r]);
            }
            for(int i=1;i<=n;i++){
                if(!ncz[bel[ns[i][0]]]){
                    printf("%.2d:%.2d ",s[i][0]/60,s[i][0]%60);
                    printf("%.2d:%.2d",(s[i][0]+d[i])/60,(s[i][0]+d[i])%60);
                }
                else{
                    printf("%.2d:%.2d ",s[i][1]/60,s[i][1]%60);
                    printf("%.2d:%.2d",(s[i][1]+d[i])/60,(s[i][1]+d[i])%60);
                }
                putchar('\n');
            }
        }
    }
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
