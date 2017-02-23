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
#define hash hhhash
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
int c[maxn][2],fa[maxn],rev[maxn],val[maxn],mx[maxn],stk[maxn];
int n,m,Q;
map<ll,int> el;
ll hash(int u,int v){
    if(u>v)swap(u,v);
    return (ll)u*200000+v;
}
struct Query{
    int op,u,v,id;
}q[maxn];
struct eg{
    int u,v,t,del;
}e[maxn];
bool isroot(int x){
    return c[fa[x]][1]!=x && c[fa[x]][0]!=x;
}
void pushup(int x){
    mx[0]=0;mx[x]=x;
    int l=c[x][0],r=c[x][1];
    if(val[mx[l]]>val[mx[x]])mx[x]=mx[l];
    if(val[mx[r]]>val[mx[x]])mx[x]=mx[r];
}
void pushdown(int x){
    if(rev[x]){
        swap(c[x][0],c[x][1]);
        rev[c[x][0]]^=1;rev[c[x][1]]^=1;rev[x]^=1;
    }
}
void rot(int x){
    int y=fa[x],z=fa[y],l=1,r;
    if(c[y][0]==x)l=0;r=l^1;
    if(!isroot(y)){
        if(c[z][0]==y)c[z][0]=x;else c[z][1]=x;
    }
    fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
    c[y][l]=c[x][r];c[x][r]=y;
    pushup(y);pushup(x);
}
void splay(int x){
    int cnt=0;stk[++cnt]=x;
    for(int i=x;!isroot(i);i=fa[i]){
        stk[++cnt]=fa[i];
    }
    for(int i=cnt;i;i--)pushdown(stk[i]);
    while(!isroot(x)){
        int y=fa[x],z=fa[y];
        if(!isroot(y)){
            if((c[y][0]==x)^(c[z][0]==y))rot(x);
            else rot(y);
        }
        rot(x);
    }
}
void access(int x){
    int t=0;
    while(x){
        splay(x);
        c[x][1]=t;fa[t]=x;
        pushup(x);
        t=x;x=fa[x];
    }
}
void makeroot(int x){
    access(x);splay(x);rev[x]^=1;
}
void link(int x,int y){
    makeroot(x);fa[x]=y;
}
void cut(int x,int y){
    makeroot(x);access(y);splay(y);c[y][0]=fa[x]=0;pushup(y);
}
int find(int x){
    access(x);splay(x);
    while(c[x][0])x=c[x][0];
    return x;
}
int query(int x,int y){
    makeroot(x);access(y);splay(y);
    return mx[y];
}
int ans[maxn];
int main(){
    n=geti();m=geti();Q=geti();
    for(int i=1;i<=m;i++){
        e[i].u=geti();e[i].v=geti();e[i].t=geti();e[i].del=0;
        el[hash(e[i].u,e[i].v)]=i;
    }
    for(int i=1;i<=Q;i++){
        q[i].op=geti();q[i].u=geti();q[i].v=geti();
        if(q[i].op==2){
            e[el[hash(q[i].u,q[i].v)]].del=true;
        }
    }
    for(int i=1;i<=m;i++){
        if(e[i].del==false){
            val[n+i]=e[i].t;
            if(find(e[i].u)!=find(e[i].v)){
                link(n+i,e[i].u);
                link(n+i,e[i].v);
            }
            else{
                int ct=query(e[i].u,e[i].v);
                if(val[ct]<val[n+i])continue;
                cut(ct,e[ct-n].u);
                cut(ct,e[ct-n].v);
                link(i+n,e[i].u);
                link(i+n,e[i].v);
            }
        }
    }
    int cnt=0;
    for(int i=Q;i;i--){
        if(q[i].op==2){
            int eid=el[hash(q[i].u,q[i].v)];
            val[eid+n]=e[eid].t;
            if(find(q[i].u)!=find(q[i].v)){
                link(eid+n,e[eid].u);
                link(eid+n,e[eid].v);
            }
            else{
                int ct=query(q[i].u,q[i].v);
                if(val[ct]<val[eid+n])continue;
                cut(ct,e[ct-n].u);
                cut(ct,e[ct-n].v);
                link(eid+n,e[eid].u);
                link(eid+n,e[eid].v);
            }
        }
        else{
            ans[++cnt]=val[query(q[i].u,q[i].v)];
        }
    }
    for(int i=cnt;i;i--)printf("%d\n",ans[i]);
 
    fclose(stdin);
    fclose(stdout);
    return 0;
}
