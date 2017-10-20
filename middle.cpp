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
const int maxn = 400000 + 100;
int mx[maxn],lmax[maxn],rmax[maxn],a[maxn],root[maxn],ls[maxn],rs[maxn],pnt;
int n;
struct node{
    int id,w;
}rd[maxn];
bool cmp(const node &x,const node &y){
    return x.w<y.w;
}
void build(int &x,int l,int r){
    x=++pnt;
    if(l==r){
        mx[x]=1;lmax[x]=1;rmax[x]=1;return;
    }
    int mid=(l+r)>>1;
    build(ls[x],l,mid);build(rs[x],mid+1,r);
    mx[x]=mx[ls[x]]+mx[rs[x]];
    lmax[x]=max(lmax[ls[x]],mx[ls[x]]+lmax[rs[x]]);
    rmax[x]=max(rmax[rs[x]],mx[rs[x]]+rmax[ls[x]]);
}
void modify(int &x,int x2,int l,int r,int p){
    x=++pnt;
    ls[x]=ls[x2];rs[x]=rs[x2];
    if(l==r){
        mx[x]=-1;lmax[x]=-1;rmax[x]=-1;return;
    }
    int mid=(l+r)>>1;
    if(p<=mid)modify(ls[x],ls[x2],l,mid,p);
    else modify(rs[x],rs[x2],mid+1,r,p);
    mx[x]=mx[ls[x]]+mx[rs[x]];
    lmax[x]=max(lmax[ls[x]],mx[ls[x]]+lmax[rs[x]]);
    rmax[x]=max(rmax[rs[x]],mx[rs[x]]+rmax[ls[x]]);
}
int querymx(int x,int l,int r,int xl,int xr){
    if(xl>xr)return 0;
    if(l==xl && r==xr){
        return mx[x];
    }
    int mid=(l+r)>>1;
    if(xr<=mid)return querymx(ls[x],l,mid,xl,xr);
    else if(xl>mid)return querymx(rs[x],mid+1,r,xl,xr);
    return querymx(ls[x],l,mid,xl,mid)+querymx(rs[x],mid+1,r,mid+1,xr);
}
int querylmax(int x,int l,int r,int xl,int xr){
    if(xl>xr)return 0;
    if(l==xl && r==xr){
        return lmax[x];
    }
    int mid=(l+r)>>1;
    if(xr<=mid)return querylmax(ls[x],l,mid,xl,xr);
    else if(xl>mid)return querylmax(rs[x],mid+1,r,xl,xr);
    else{
        int lans=querylmax(ls[x],l,mid,xl,mid);
        int lsum=querymx(ls[x],l,mid,xl,mid);
        int rans=querylmax(rs[x],mid+1,r,mid+1,xr);
        return max(lans,lsum+rans);
    }
}
int queryrmax(int x,int l,int r,int xl,int xr){
    if(xl>xr)return 0;
    if(l==xl && r==xr){
        return rmax[x];
    }
    int mid=(l+r)>>1;
    if(xr<=mid)return queryrmax(ls[x],l,mid,xl,xr);
    else if(xl>mid)return queryrmax(rs[x],mid+1,r,xl,xr);
    else{
        int rans=queryrmax(rs[x],mid+1,r,mid+1,xr);
        int rsum=querymx(rs[x],mid+1,r,mid+1,xr);
        int lans=queryrmax(ls[x],l,mid,xl,mid);
        return max(rans,rsum+lans);
    }
}
int ver[maxn];
int hs[maxn];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    n=geti();
    for(int i=1;i<=n;i++){
        rd[i].id=i;rd[i].w=geti();
    }
    sort(rd+1,rd+1+n,cmp);
    int s=0;
    for(int i=1;i<=n;i++){
        if(i!=1 && rd[i].w==rd[i-1].w)a[rd[i].id]=s;
        else a[rd[i].id]=++s,hs[s]=rd[i].w;
    }
    build(root[0],1,n);
    for(int i=1;i<=n;i++){
        modify(root[i],root[i-1],1,n,rd[i].id);
        if(i==n || rd[i].w!=rd[i+1].w)ver[a[rd[i].id]]=i;
    }
    int Q=geti();
    ll ans=0,t[4];
    while(Q--){
        for(int i=0;i<4;i++){
            t[i]=(geti()+ans)%n+1;
        }
        sort(t,t+4);
        /*for(int i=0;i<4;i++){
            cout << t[i] << " ";
        }
        cout << endl;*/
        int l=1,r=s,mid,rt=-1;
        while(l<=r){
            mid=(l+r)>>1;
            //printf("l = %d, r = %d, mid = %d, realmid = %d\n",l,r,mid,hs[mid]);
            int d1=querymx(root[ver[mid]-1],1,n,t[1],t[2]);
            int d2=queryrmax(root[ver[mid]-1],1,n,t[0],t[1]-1);
            int d3=querylmax(root[ver[mid]-1],1,n,t[2]+1,t[3]);
            //cout << d1 << " " << d2 << " " << d3 << endl;
            if(d1>=0 || d1+d2>=0 || d1+d3>=0 || d1+d2+d3>=0){
                l=mid+1;
                rt=mid;
            }
            else{
                r=mid-1;
            }
        }
        printf("%d\n",hs[rt]);
        ans=hs[rt];
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}

