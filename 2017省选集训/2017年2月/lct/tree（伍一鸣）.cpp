#include <cstdio>
#include <iostream>
#include <cstdlib>
using namespace std;
typedef unsigned int u32;
const u32 mo = 51061;
const int maxn = 200000 + 1000;
int n,Q;
int c[2][maxn],fa[maxn],v[maxn],rev[maxn],stk[maxn],size[maxn];
u32 tot[maxn],add[maxn],mul[maxn];
u32 geti(){
    u32 ret=0;char ch=getchar();
    while(ch<'0' || ch>'9')ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret;
}
bool isroot(int x){
    return c[0][fa[x]]!=x && c[1][fa[x]]!=x;
}
void pushup(int x){
    size[0]=0;tot[0]=0;
    size[x]=size[c[0][x]]+size[c[1][x]]+1;
    tot[x]=(tot[c[0][x]]+tot[c[1][x]]+v[x])%mo;
}
void pushdown(int x){
    int ls=c[0][x],rs=c[1][x];
    if(rev[x]){
	swap(c[0][x],c[1][x]);
	rev[ls]^=1;rev[rs]^=1;rev[x]^=1;
    }
    if(ls){
        v[ls]=(v[ls]*mul[x]+add[x])%mo;
        tot[ls]=(tot[ls]*mul[x]+add[x]*size[ls])%mo;
        mul[ls]=(mul[ls]*mul[x])%mo;
        add[ls]=(add[ls]*mul[x]+add[x])%mo;
    }
    if(rs){
        v[rs]=(v[rs]*mul[x]+add[x])%mo;
        tot[rs]=(tot[rs]*mul[x]+add[x]*size[rs])%mo;
        mul[rs]=(mul[rs]*mul[x])%mo;
        add[rs]=(add[rs]*mul[x]+add[x])%mo;
    }
    add[x]=0;mul[x]=1;
}
void rot(int x){
    int y=fa[x],z=fa[y],l=1,r;
    if(c[0][y]==x)l=0;r=l^1;
    if(!isroot(y)){
	if(c[0][z]==y)c[0][z]=x;
	else c[1][z]=x;
    }
    fa[x]=z;fa[y]=x;fa[c[r][x]]=y;
    c[l][y]=c[r][x];c[r][x]=y;
    pushup(y);pushup(x);
}
void splay(int x){
    int cnt=0;stk[++cnt]=x;
    for(int i=x;!isroot(i);i=fa[i])stk[++cnt]=fa[i];
    for(int i=cnt;i;i--)pushdown(stk[i]);
    int u=x;
    while(!isroot(u)){
	int y=fa[u],z=fa[y];
	if(!isroot(y)){
	    if((c[0][y]==u)^(c[0][z]==y))rot(u);
	    else rot(y);
	}
	rot(u);
    }
}
void access(int x){
    int t=0;
    while(x){
        splay(x);
        c[1][x]=t;pushup(x);
        fa[t]=x;t=x;x=fa[x];
    }
}
void makeroot(int x){
    access(x);splay(x);rev[x]^=1;
}
void link(int x,int y){
    makeroot(x);fa[x]=y;
}
void cut(int x,int y){
    makeroot(x);access(y);splay(y);c[0][y]=fa[x]=0;pushup(y);
}
int main(){
    n=geti();Q=geti();
    int u,vv,a,b,vx;
    for(int i=1;i<=n;i++)v[i]=1,mul[i]=1,tot[i]=1;
    for(int i=1;i<n;i++){
        u=geti();vv=geti();
        link(u,vv);
    }
    char op[20];
    for(int i=1;i<=Q;i++){
        scanf("%s",op);
        if(op[0]=='+'){
            u=geti();vv=geti();vx=geti();
            makeroot(u);access(vv);splay(vv);
            v[vv]+=vx;v[vv]%=mo;
            tot[vv]+=vx;tot[vv]%=mo;
            add[vv]+=vx;add[vv]%=mo;
        }
        else if(op[0]=='-'){
            u=geti();vv=geti();a=geti();b=geti();
            cut(u,vv);link(a,b);
        }
        else if(op[0]=='*'){
            u=geti();vv=geti();vx=geti();
            makeroot(u);access(vv);splay(vv);
            v[vv]*=vx;v[vv]%=mo;
            tot[vv]*=vx;tot[vv]%=mo;
            add[vv]*=vx;add[vv]%=mo;
            mul[vv]*=vx;mul[vv]%=mo;
        }
        else{
            u=geti();vv=geti();
            makeroot(u);access(vv);splay(vv);
            printf("%d\n",tot[vv]);
        }
    }
    return 0;
}
