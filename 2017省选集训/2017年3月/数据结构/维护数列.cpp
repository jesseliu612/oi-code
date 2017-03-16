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
const int inf = 500001000;
typedef long long ll;
ll geti(){
    char ch=getchar();while((ch<'0' || ch>'9')&&ch!='-')ch=getchar();
    ll ret=0,k=1;
    if(ch=='-')k=-1,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret*k;
}
const int maxn = 500000+100;
int rd[maxn];
int pt[maxn],c[maxn][2];
int size[maxn],fa[maxn],modi[maxn],toc[maxn],sum[maxn],rev[maxn],lmax[maxn],rmax[maxn],tmax[maxn],stk[maxn];
int rbc[maxn],rtp=0;
int root,pnt=0;
inline int newnode(){
    if(rtp){
        int ret=rbc[rtp];--rtp;
        if(c[ret][0])rbc[++rtp]=c[ret][0];
        if(c[ret][1])rbc[++rtp]=c[ret][1];
        return ret;
    }
    return ++pnt;
}
inline void pushup(int x){
    size[0]=0;sum[0]=0;
    int ls=c[x][0],rs=c[x][1];
    size[x]=size[ls]+size[rs]+1;
    sum[x]=sum[ls]+sum[rs]+pt[x];
    if(ls){
        tmax[x]=max(pt[x],max(tmax[ls],rmax[ls]+pt[x]));
        lmax[x]=max(lmax[ls],sum[ls]+pt[x]);
        if(rs){
            tmax[x]=max(tmax[x],max(pt[x]+lmax[rs],max(tmax[rs],rmax[ls]+pt[x]+lmax[rs])));
            lmax[x]=max(lmax[x],sum[ls]+pt[x]+lmax[rs]);
            rmax[x]=max(rmax[rs],max(sum[rs]+pt[x],sum[rs]+pt[x]+rmax[ls]));
        }
        else{
            rmax[x]=max(pt[x],rmax[ls]+pt[x]);
        }
    }
    else if(rs){
        tmax[x]=max(tmax[rs],max(pt[x],lmax[rs]+pt[x]));
        lmax[x]=max(pt[x],lmax[rs]+pt[x]);
        rmax[x]=max(rmax[rs],sum[rs]+pt[x]);
    }
    else{
        tmax[x]=lmax[x]=rmax[x]=pt[x];
    }
}
inline void pushdown(int x){
    int &ls=c[x][0],&rs=c[x][1];
    if(modi[x]){
        modi[x]=0;
        if(ls){
            toc[ls]=pt[ls]=toc[x];
            sum[ls]=toc[x]*size[ls];
        }
        if(rs){
            toc[rs]=pt[rs]=toc[x];
            sum[rs]=toc[x]*size[rs];
        }
        if(toc[x]>=0){
            if(ls)lmax[ls]=rmax[ls]=tmax[ls]=sum[ls];
            if(rs)lmax[rs]=rmax[rs]=tmax[rs]=sum[rs];
        }
        else{
            if(ls)lmax[ls]=rmax[ls]=tmax[ls]=toc[x];
            if(rs)lmax[rs]=rmax[rs]=tmax[rs]=toc[x];
        }
        modi[ls]=1;modi[rs]=1;
    }
    if(rev[x]){
        rev[x]=0;rev[ls]^=1;rev[rs]^=1;
        swap(ls,rs);
        swap(lmax[ls],rmax[ls]);
        swap(lmax[rs],rmax[rs]);
    }
}
inline int kth(int x,int k){
    pushdown(x);
    int ls=c[x][0],rs=c[x][1];
    size[0]=0;
    if(size[ls]>=k)return kth(ls,k);
    if(size[ls]+1==k)return x;
    return kth(rs,k-size[ls]-1);
}
inline void rot(int x){
    int y=fa[x],z=fa[y],l=1,r;
    if(c[y][0]==x)l=0;
    r=l^1;
    if(z){
        if(c[z][0]==y)c[z][0]=x;
        else c[z][1]=x;
    }
    fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
    c[y][l]=c[x][r];c[x][r]=y;
    pushup(y);pushup(x);
}
inline void splay(int x,int pos){
    int cnt=0;stk[++cnt]=x;
    for(int i=x;fa[i]!=0;i=fa[i]){
        stk[++cnt]=fa[i];
    }
    for(int i=cnt;i;i--){
        pushdown(stk[i]);
    }
    int u=x;
    while(fa[u]!=pos){
        int y=fa[u],z=fa[y];
        if(z!=pos){
            if((c[z][0]==y)^(c[y][0]==u))rot(u);
            else rot(y);
        }
        rot(u);
    }
    if(pos==0)root=x;
}
inline int build(int l,int r,int f){
    int mid=(l+r)>>1;
    int cur=newnode();
    fa[cur]=f;size[cur]=1;
    modi[cur]=toc[cur]=rev[cur]=c[cur][0]=c[cur][1]=0;
    pt[cur]=sum[cur]=lmax[cur]=rmax[cur]=tmax[cur]=rd[mid];
    if(l<mid){
        c[cur][0]=build(l,mid-1,cur);
    }
    if(r>mid){
        c[cur][1]=build(mid+1,r,cur);
    }
    pushup(cur);
    return cur;
}
int len=0;
inline void ins(){
    int pos=geti();int tot=geti();
    ++pos;
    for(int i=1;i<=tot;i++)rd[i]=geti();
    int a=kth(root,pos);int b=kth(root,pos+1);
    splay(a,0);splay(b,a);
    c[b][0]=build(1,tot,b);
    pushup(b);pushup(a);
    len+=tot;
}
inline void del(){
    int pos=geti();int tot=geti();
    if(tot==0)return;
    ++pos;
    int a=kth(root,pos-1);int b=kth(root,pos+tot);
    splay(a,0);splay(b,a);
    rbc[++rtp]=c[b][0];
    c[b][0]=0;
    pushdown(a);pushdown(b);
    pushup(b);pushup(a);
    len-=tot;
}
inline void modify(){
    int pos=geti();int tot=geti();int v=geti();
    ++pos;
    int a=kth(root,pos-1);int b=kth(root,pos+tot);
    splay(a,0);splay(b,a);
    modi[c[b][0]]=true;
    sum[c[b][0]]=size[c[b][0]]*v;
    if(v>=0){
        tmax[c[b][0]]=lmax[c[b][0]]=rmax[c[b][0]]=sum[c[b][0]];
    }
    else{
        tmax[c[b][0]]=lmax[c[b][0]]=rmax[c[b][0]]=v;
    }
    pt[c[b][0]]=v;toc[c[b][0]]=v;
    pushdown(a);pushdown(b);
    pushup(b);pushup(a);
}
inline void reverse(){
    int pos=geti();int tot=geti();
    ++pos;
    int a=kth(root,pos-1);int b=kth(root,pos+tot);
    splay(a,0);splay(b,a);
    rev[c[b][0]]^=1;
    swap(lmax[c[b][0]],rmax[c[b][0]]);
    pushdown(c[b][0]);
    pushup(b);pushup(a);
}
inline void getsum(){
    int pos=geti();int tot=geti();
    ++pos;
    int a=kth(root,pos-1);int b=kth(root,pos+tot);
    splay(a,0);splay(b,a);
    printf("%d\n",sum[c[b][0]]);
}
void dfs(int x){
    if(!x)return;
    pushdown(x);
    dfs(c[x][0]);
    dfs(c[x][1]);
    pushup(x);
}
inline void getmax(){
    printf("%d\n",tmax[root]);
}
inline void work(){
    char ops[20];
    int n=geti();
    int m=geti();
    for(int i=1;i<=n;i++)rd[i]=geti();
    len=n+2;
    rd[0]=rd[n+1]=-inf;
    root=build(0,n+1,0);
    for(int T=1;T<=m;T++){
        scanf("%s",ops);
        if(ops[0]=='I')ins();
        else if(ops[0]=='D')del();
        else if(ops[2]=='K')modify();
        else if(ops[0]=='R')reverse();
        else if(ops[0]=='G')getsum();
        else getmax();
    }
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    
    work();
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
