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
const int maxn = 100000 + 100;
int n;
double s,f[maxn],a[maxn],b[maxn],r[maxn],M[maxn],G[maxn];
struct lines{
    double k,b,x;
    int id;
}q[maxn],t[maxn],t1[maxn],t2[maxn];
void solve(int l,int r){
    if(l==r)return;
    /*printf("solve(%d,%d)\n",l,r);
    for(int i=l;i<=r;i++){
        cout << t[i].id << " ";
        }cout << endl;*/
    int mid=(l+r)>>1;
    int x=l-1,m=0,g=0;
    for(int i=l;i<=r;++i){
        if(t[i].id<=mid){
            t1[++m]=t[i];
        }
        else{
            t2[++g]=t[i];
        }
    }
    for(int i=1;i<=m;++i){
        t[++x]=t1[i];
    }
    for(int i=1;i<=g;++i){
        t[++x]=t2[i];
    }
    solve(l,mid);
    int hd=0,tl=0;
    for(int i=l;i<=mid;++i){
        while(tl-hd>1 && (t[i].b-q[tl-1].b)*(q[tl-1].k-q[tl].k)<=(q[tl].b-q[tl-1].b)*(q[tl-1].k-t[i].k)){
            --tl;
        }
        q[++tl]=t[i];
    }
    for(int i=mid+1;i<=r;++i){
        double x=a[t[i].id]/b[t[i].id];
        int cur=t[i].id;
        while(tl-hd>1 && q[hd+1].k*x+q[hd+1].b<=q[hd+2].k*x+q[hd+2].b){
            ++hd;
        }
        f[cur]=max(f[cur],b[cur]*(q[hd+1].k*x+q[hd+1].b));
        f[cur+1]=max(f[cur+1],f[cur]);
        t[i].b=f[cur]/M[cur];
        t[i].k=f[cur]*G[cur];
    }
    solve(mid+1,r);
    x=l,m=l,g=mid+1;
    while(m<=mid && g<=r){
        if(t[m].k<=t[g].k){
            t1[x]=t[m];++x;++m;
        }
        else{
            t1[x]=t[g];++x;++g;
        }
    }
    while(m<=mid){
        t1[x]=t[m];++x;++m;
    }
    while(g<=r){
        t1[x]=t[g];++x;++g;
    }
    for(int i=l;i<=r;i++)t[i]=t1[i];
}
bool cmp(const lines &x,const lines &y){
    return x.x<y.x;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    n=geti();s=geti();
    for(int i=1;i<=n;++i){
        scanf("%lf%lf%lf",a+i,b+i,r+i);
        M[i]=r[i]*a[i]+b[i];
        G[i]=(M[i]-b[i])/(M[i]*a[i]);
        f[i]=s;
        t[i].id=i;
        t[i].x=a[i]/b[i];
        //printf("a[%d] = %.3lf, b[%d] = %.3lf, M[%d] = %.3lf, G[%d] = %.3lf\n",i,a[i],i,b[i],i,M[i],i,G[i]);
    }
    t[1].b=f[1]/M[1];
    t[1].k=f[1]*G[1];
    sort(t+1,t+1+n,cmp);
    solve(1,n);
    /*f[1]=s;
      for(int i=2;i<=n;++i){
      f[i]=f[i-1];
      for(int j=1;j<i;++j){
      f[i]=max(f[i],f[j]*b[i]/M[j]+(m[j]*f[j]-f[j]*b[j])*a[i]/(m[j]*a[j]));
      }
      }
    */
    printf("%.3lf",f[n]);
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}

