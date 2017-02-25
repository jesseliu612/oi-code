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
const int maxm = 10000;
int n,m;
int st[maxn],pt[maxm],nxt[maxm],ent=0;
int stk[maxn][2],tp[2]={0,0};
int ns[maxn][2],pnt=1;
int anss[maxn];
void adde(int u,int v){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;
}
char cz[maxn];
int Tp;
bool dfs(int x,int c){
    if(cz[x^1])return false;
    stk[++tp[c]][c]=x;
    cz[x]=true;
    for(int i=st[x];i;i=nxt[i]){
        if(cz[pt[i]]==true)continue;
        if(!dfs(pt[i],c))return false;
    }
    return true;
}
int dfn[maxn],low[maxn],vis[maxn],ins[maxn],tsk[maxn],ttop=0,dnt=0;
void tarjan(int x){
    dfn[x]=++dnt;low[x]=dnt;
    vis[x]=true;ins[x]=true;tsk[++ttop]=x;
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
        cout << "###" << endl;
        while(tsk[ttop]!=x){
            cout << tsk[ttop] << endl;
            ttop--;
        }
        cout << tsk[ttop] << endl;
        ttop--;
    }
}
int main(){
    freopen("cowngress.in","r",stdin);
    freopen("cowngress.out","w",stdout);

    n=geti();m=geti();
    int u,v,ux,vx;
    char opu[10],opv[10];
    for(int i=1;i<=n;i++){
        ns[i][0]=++pnt;ns[i][1]=++pnt;
    }
    for(int i=1;i<=m;i++){
        scanf("%d%s%d%s",&u,opu,&v,opv);
        if(opu[0]=='Y')ux=0;else ux=1;
        if(opv[0]=='Y')vx=0;else vx=1;
        adde(ns[u][ux^1],ns[v][vx]);
        adde(ns[v][vx^1],ns[u][ux]);
    }
    /*for(int i=2;i<=pnt;i++){
        if(!vis[i])tarjan(i);
    }
    */
    int flag=0;
    for(int k=n;k>=1;k--){
        if(cz[ns[k][0]]){
            anss[k]=0;
            continue;
        }
        else if(cz[ns[k][1]]){
            anss[k]=1;
            continue;
        }
        Tp=k;
        tp[0]=0;tp[1]=0;
        if(dfs(ns[k][0],0)){
            for(int i=1;i<=tp[0];i++)cz[stk[i][0]]=false;
            if(dfs(ns[k][1],1)){
                for(int i=1;i<=tp[1];i++)cz[stk[i][1]]=false;
                anss[k]=2;
            }
            else{
                for(int i=1;i<=tp[1];i++)cz[stk[i][1]]=false;
                for(int i=1;i<=tp[0];i++)cz[stk[i][0]]=true;
                anss[k]=0;
            }
        }
        else{
            for(int i=1;i<=tp[0];i++)cz[stk[i][0]]=false;
            if(dfs(ns[k][1],1)){
                anss[k]=1;
            }
            else{
                flag=1;
                break;
            }
        }
    }
    if(flag){
        printf("IMPOSSIBLE");
    }
    else{
        for(int i=1;i<=n;i++){
            if(anss[i]==0)putchar('Y');
            else if(anss[i]==1)putchar('N');
            else putchar('?');
        }
    }
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
