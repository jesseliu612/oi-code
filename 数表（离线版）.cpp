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
#define RG register
using namespace std;
const int inf = 2147483640;
typedef int ll;
ll geti(){
    char ch=getchar();while((ch<'0' || ch>'9')&&ch!='-')ch=getchar();
    ll ret=0,k=1;
    if(ch=='-')k=-1,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret*k;
}
const int maxn = 200000 + 100;
int prime[maxn],mu[maxn],pnt=0;
int sigma[maxn],pre[maxn];
int who[maxn];
char vis[maxn];
struct Fs{
    ll f;
    int id;
}f[maxn];
inline char cmp(RG const Fs &x,RG const Fs &y){
    return x.f<y.f;
}
inline void sieve(){
    mu[1]=1;sigma[1]=1;
    for(RG int i=2;i<maxn;i++){
        if(!vis[i]){
            mu[i]=-1;prime[++pnt]=i;
        }
        for(RG int j=1;j<=pnt && i*prime[j]<maxn;j++){
            vis[i*prime[j]]=true;
            who[i*prime[j]]=i;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                break;
            }
            mu[i*prime[j]]=-mu[i];
        }
        sigma[i]=sigma[i-1]+mu[i];
    }
    for(RG int i=1;i<maxn;i++)f[i].id=i;
    for(RG int i=1;i<maxn;i++){
        for(RG int j=i;j<maxn;j+=i){
            f[j].f+=i;
        }
    }
    /*for(int i=1;i<maxn;i++){
      printf("f[%d].c = %d\n",i,f[i].c);
      }
    */
}
struct query{
    int n,m,a,id;
}q[maxn];
bool cmp2(const query &x,const query &y){
    return x.a<y.a;
}
int mx[maxn];
inline int lowbit(int x){
    return x&(-x);
}
void update(int p,int v){
    for(int i=p;i<maxn;i+=lowbit(i)){
        mx[i]+=v;
    }
}
int query(int l,int r){
    int res=0;
    for(int i=r;i;i-=lowbit(i)){
        res+=mx[i];
    }
    for(int i=l-1;i;i-=lowbit(i)){
        res-=mx[i];
    }
    return res;
}
int ans[maxn];
int main(){
    sieve();
    sort(f+1,f+maxn,cmp);
    int Q=geti();
    for(int i=1;i<=Q;i++){
        q[i].n=geti();q[i].m=geti();q[i].a=geti();q[i].id=i;
    }
    sort(q+1,q+1+Q,cmp2);
    int cr=1;
    for(int tt=1;tt<=Q;tt++){
        int n=q[tt].n,m=q[tt].m,a=q[tt].a;
        while(cr<maxn && f[cr].f<=a){
            for(int i=f[cr].id;i<maxn;i+=f[cr].id){
                update(i,f[cr].f*mu[i/f[cr].id]);
            }
            ++cr;
        }
        if(n>m)swap(n,m);
        int pos=0;
        int res=0;
        for(int i=1;i<=n;i=pos+1){
            pos=min(n/(n/i),m/(m/i));
            res+=query(i,pos)*(n/i)*(m/i);
        }
        ans[q[tt].id]=res%(1<<31);
        if(ans[q[tt].id]<0)ans[q[tt].id]+=(1<<31);
    }
    for(int i=1;i<=Q;i++){
        printf("%d\n",ans[i]);
    }
     
    fclose(stdin);
    fclose(stdout);
    return 0;
}
