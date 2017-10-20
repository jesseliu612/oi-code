#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <ctime>
#define ls (x<<1)
#define rs (x<<1|1)
using namespace std;
typedef long long ll;
ll geti(){
    char ch=getchar(),k=1;ll ret=0;
    while((ch<'0' || ch>'9') && ch!='0')ch=getchar();
    if(ch=='-')k=0,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return k?ret:-ret;
}
const int maxn = 100000 + 1000;
struct XDS{
    ll mx[maxn*8],lazy[maxn*8];
    void pushdown(int x){
        mx[ls]+=lazy[x];mx[rs]+=lazy[x];
        lazy[ls]+=lazy[x];lazy[rs]+=lazy[x];
        lazy[x]=0;
    }
    void update(int x,int l,int r,int xl,int xr,ll v){
        //printf("update(%d,%d,%d,%d,%d,%lld)\n",x,l,r,xl,xr,v);cout << flush;
        //pushdown(x);
        if(xl==l && r==xr){
            mx[x]+=v;lazy[x]+=v;return;
        }
        int mid=(l+r)>>1;
        if(xr<=mid)update(ls,l,mid,xl,xr,v);
        else if(xl>mid)update(rs,mid+1,r,xl,xr,v);
        else update(ls,l,mid,xl,mid,v),update(rs,mid+1,r,mid+1,xr,v);
        mx[x]=max(mx[ls],mx[rs])+lazy[x];
    }
    ll query(int x,int l,int r,int xl,int xr){
        //pushdown(x);
        if(l==xl && r==xr){
            return mx[x];
        }
        int mid=(l+r)>>1;
        if(xr<=mid)return query(ls,l,mid,xl,xr)+lazy[x];
        else if(xl>mid)return query(rs,mid+1,r,xl,xr)+lazy[x];
        else return max(query(ls,l,mid,xl,mid),query(rs,mid+1,r,mid+1,xr))+lazy[x];
    }
}t;
int n,w,h;
struct star{
    ll x,y,ty,l;
}a[maxn];
ll hs[maxn];
bool cmpx(const star &x,const star &y){
    return x.x<y.x;
}
bool cmpy(const star &x,const star &y){
    return x.ty<y.ty;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    while(scanf("%d%d%d",&n,&w,&h)==3){
        //cout << n << " " << w << " " << h << endl;
        memset(a,0,sizeof(a));
        memset(hs,0,sizeof(hs));
        memset(t.mx,0,sizeof(t.mx));
        memset(t.lazy,0,sizeof(t.lazy));
        for(int i=1;i<=n;i++){
            a[i*2-1].x=geti();a[i*2-1].ty=geti();a[i*2-1].l=geti();
            a[i*2].x=a[i*2-1].x+w;a[i*2].ty=a[i*2-1].ty;a[i*2].l=-a[i*2-1].l;
        }
        n=n*2;
        sort(a+1,a+1+n,cmpy);
        int s=0;
        for(int i=1;i<=n;i++){
            if(i!=1 && a[i].ty==a[i-1].ty)a[i].y=s;
            else{
                if(a[i].ty-hs[s]>1){
                    ++s;hs[s]=hs[s-1]+1;
                }
                ++s;hs[s]=a[i].ty;
                a[i].y=s;
            }
        }
        hs[++s]=a[n].ty+1;
        sort(a+1,a+1+n,cmpx);
        ll ans=0;
        /*for(int i=1;i<=n;i++){
            printf("i = %d, x = %lld, y = %lld, ty = %lld, l = %lld\n",i,a[i].x,a[i].y,a[i].ty,a[i].l);
        }
        */
        for(int i=1;i<=n;i++){
            //printf("i = %d, x = %lld, y = %lld, ty = %lld, l = %lld\n",i,a[i].x,a[i].y,a[i].ty,a[i].l);
            int l=a[i].y,r=s,mid,rt=-1;
            ll cur=a[i].ty+h-1;
            while(l<=r){
                mid=(l+r)>>1;
                if(hs[mid]<=cur){
                    rt=mid;l=mid+1;
                }
                else r=mid-1;
            }
            t.update(1,1,s,a[i].y,rt,a[i].l);
            //cout << "rt = " << rt << endl;
            if(a[i].x!=a[i+1].x || i==n){
                ans=max(ans,t.query(1,1,s,1,s));
                //cout << "i = " << i << " , ans = " << t.query(1,1,s,1,s) << endl;
            }
        }
        //ll stdans=geti();
        //if(ans==stdans)cout << "Accepted" << endl;
        //else cout << "Wrong Answer!" << endl;
        printf("%lld\n",ans);
    }
    
    return 0;
}

