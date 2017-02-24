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
const int maxn = 120000;
const int maxm = 600000;
struct node{
    int a,b;
}ns[maxn];
int n,m;
int st[maxn],pt[maxm],nxt[maxm],ent=1;
void adde(int u,int v){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;
}
char cz[maxn],ins[maxn];
int stk[maxn],tp=0;
int ans[maxn];
bool dfs(int x){
    if(cz[x^1])return false;
    stk[++tp]=x;
    cz[x]=true;
    for(int i=st[x];i;i=nxt[i]){
        if(cz[pt[i]])continue;
        if(!dfs(pt[i]))return false;
    }
    return true;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    n=geti();m=geti();
    int pnt=1;
    for(int i=1;i<=n;i++){
        ns[i].a=++pnt;ns[i].b=++pnt;
    }
    int u,v;
    for(int i=1;i<=m;i++){
        u=geti();v=geti();
        adde(u+1,(v+1)^1);adde(v+1,(u+1)^1);
    }
    for(int i=1;i<=n;i++){
        tp=0;
        if(dfs(ns[i].a)){
            ans[i]=ns[i].a-1;
        }
        else{
            for(int j=1;j<=tp;j++)cz[stk[j]]=false;
            tp=0;
            if(!dfs(ns[i].b)){
                printf("NIE");
                exit(0);
            }
            ans[i]=ns[i].b-1;
        }
    }
    for(int i=1;i<=n;i++){
        printf("%d\n",ans[i]);
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
