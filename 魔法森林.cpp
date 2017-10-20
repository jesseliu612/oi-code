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
const int maxn = 150000 + 100;
int c[maxn][2],fa[maxn],rev[maxn],w[maxn],mx[maxn],val[maxn],stk[maxn];
int n,m;
bool isroot(int x){
    return c[fa[x]][0]!=x&&c[fa[x]][1]!=x;
}
void pushdown(int x){
    if(rev[x]){
        swap(c[x][0],c[x][1]);
        rev[c[x][0]]^=1;rev[c[x][1]]^=1;rev[x]^=1;
    }
}
void pushup(int x){
    mx[0]=0;mx[x]=x;
    int l=c[x][0],r=c[x][1];
    if(val[mx[l]]>val[mx[x]])mx[x]=mx[l];
    if(val[mx[r]]>val[mx[x]])mx[x]=mx[r];
}
void rot(int x){
    int y=fa[x],z=fa[y],l=1,r;
    if(c[y][0]==x)l=0;
    r=l^1;
    if(!isroot(y)){
        if(c[z][0]==y)c[z][0]=x;
        else c[z][1]=x;
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
    for(int i=cnt;i;i--){
        pushdown(stk[i]);
    }
    int u=x;
    while(!isroot(u)){
        int y=fa[u],z=fa[y];
        if(!isroot(y)){
            if((c[y][0]==u)^(c[z][0]==y))rot(u);
            else rot(y);
        }
        rot(u);
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
    makeroot(x);access(y);splay(y);c[y][0]=fa[x]=0;
    pushup(y);
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
struct edge{
    int x,y,a,b;
}e[maxn];
bool cmp(edge x,edge y){
    return x.a<y.a;
}
int main(){
    n=geti();m=geti();
    for(int i=1;i<=n+m;i++)mx[i]=i;
    for(int i=1;i<=m;i++){
        e[i].x=geti();e[i].y=geti();e[i].a=geti();e[i].b=geti();
    }
    sort(e+1,e+1+m,cmp);
    int ans=2147483640;
    for(int i=1;i<=m;i++){
        val[n+i]=e[i].b;
        //if e[i].x is not connected with e[i].y, which means adding this edge won't make the answer worse.
        if(find(e[i].x)!=find(e[i].y)){
            link(n+i,e[i].x);
            link(n+i,e[i].y);
        }
        else{
            int ct=query(e[i].x,e[i].y);
            if(val[ct]<e[i].b)continue;
            cut(ct,e[ct-n].x);
            cut(ct,e[ct-n].y);
            link(n+i,e[i].x);
            link(n+i,e[i].y);
        }
        if(find(1)!=find(n))continue;
        ans=min(ans,e[i].a+val[query(1,n)]);
    }
    if(ans!=2147483640)cout << ans;
    else cout << "-1";
    fclose(stdin);
    fclose(stdout);
    return 0;
}

