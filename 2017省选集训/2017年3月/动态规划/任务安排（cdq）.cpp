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
typedef long double ld;
ll geti(){
    char ch=getchar();while((ch<'0' || ch>'9')&&ch!='-')ch=getchar();
    ll ret=0,k=1;
    if(ch=='-')k=-1,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret*k;
}
const int maxn = 300000 + 1000;
struct lines{
    ll k,b,x;
    int id;
}q[maxn],t1[maxn],t2[maxn],t[maxn];
int n,gap;
ll c[maxn],s[maxn],f[maxn];
void solve(int l,int r,int xl,int xr){
    if(xl==xr)return;
    int mid=(xl+xr)>>1;
    int x=l-1,m=0,g=0;
    for(int i=l;i<=r;i++){
        if(q[i].id<=mid){
            t1[++m]=q[i];
        }
        else{
            t2[++g]=q[i];
        }
    }
    for(int i=1;i<=m;i++)q[++x]=t1[i];
    int tmp=x;
    for(int i=1;i<=g;i++)q[++x]=t2[i];
    solve(l,tmp,xl,mid);
    int hd=0,tl=1;
    for(int i=l;i<=tmp;++i){
        while(tl-hd>1 && (ld)(q[i].b-t[tl-1].b)*(t[tl-1].k-t[tl].k)<=(ld)(t[tl-1].k-q[i].k)*(t[tl].b-t[tl-1].b))--tl;
        t[++tl]=q[i];
    }
    for(int i=tmp+1;i<=r;++i){
        while(tl-hd>1 && t[hd+1].k*q[i].x+t[hd+1].b>=t[hd+2].k*q[i].x+t[hd+2].b)++hd;
        f[q[i].id]=min(f[q[i].id],t[hd+1].k*q[i].x+t[hd+1].b+s[q[i].id]*c[q[i].id]+gap*c[n]);
        q[i].b=f[q[i].id]-gap*c[q[i].id];
    }
    solve(tmp+1,r,mid+1,xr);
    x=l,m=l,g=tmp+1;
    while(m<=tmp && g<=r){
        if(q[m].k>=q[g].k){
            t1[x]=q[m];++x;++m;
        }
        else{
            t1[x]=q[g];++x;++m;
        }
    }
    while(m<=tmp){
        t1[x]=q[m];++x;++m;
    }
    while(g<=r){
        t1[x]=q[g];++x;++g;
    }
    for(int i=l;i<=r;i++)q[i]=t1[i];
}
bool cmp(const lines &x,const lines &y){
    return x.x<y.x;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    n=geti();gap=geti();
    for(int i=1;i<=n;i++){
        s[i]=s[i-1]+geti();
        c[i]=c[i-1]+geti();
        //cout << s[i] << " " << c[i] << endl;
        q[i].id=i;q[i].x=s[i];q[i].k=-c[i];
    }
    memset(f,0x7f,sizeof(f));
    sort(q+1,q+1+n,cmp);
    solve(0,n,0,n);
    cout << f[n];
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}

