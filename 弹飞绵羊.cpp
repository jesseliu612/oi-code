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
const int maxn = 200000 + 100;
int n;
int c[maxn][2],fa[maxn],rev[maxn],size[maxn],stk[maxn],nxt[maxn];
bool isroot(int x){
    return c[fa[x]][0]!=x && c[fa[x]][1]!=x;
}
void pushup(int x){
    size[0]=0;
    size[x]=size[c[x][0]]+size[c[x][1]]+1;
}
void pushdown(int x){
    if(rev[x]){
        swap(c[x][0],c[x][1]);
        rev[c[x][0]]^=1;rev[c[x][1]]^=1;rev[x]^=1;
    }
}
void rot(int x){
    int y=fa[x],z=fa[y],l=1,r;
    if(c[y][0]==x)l=0;
    r=l^1;
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
        rot(u);//数据太水，之前写的rot(x)居然AC了
    }
}
void access(int x){
    int t=0;
    while(x){
        splay(x);
        c[x][1]=t;
        t=x;x=fa[x];
    }
}
void makeroot(int x){
    access(x);splay(x);rev[x]^=1;
}
void link(int x,int y){
    makeroot(x);fa[x]=y;splay(x);
}
void cut(int x,int y){
    makeroot(x);access(y);splay(y);c[y][0]=fa[x]=0;
}
int main(){
    freopen("lct.in","r",stdin);
    freopen("lct.out","w",stdout);
    n=geti();
    for(int i=1;i<=n;i++){
        int x=geti();
        fa[i]=x+i;size[i]=1;
        if(fa[i]>n+1)fa[i]=n+1;
        nxt[i]=fa[i];
    }
    size[n+1]=1;
    int m=geti();
    for(int i=1;i<=m;i++){
        int op=geti();
        if(op==1){
            makeroot(n+1);
            int x=geti();++x;
            access(x);
            splay(x);
            printf("%d\n",size[c[x][0]]);

        }
        else{
            int x=geti();int y=geti();
            ++x;
            int t=min(n+1,x+y);
            cut(x,nxt[x]);link(x,t);
            nxt[x]=t;
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
