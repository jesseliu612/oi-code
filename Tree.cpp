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
const int maxn = 10000 + 100;
int n,m;
int st[maxn],pt[maxn*2],nxt[maxn*2],w[maxn*2],dis[maxn],dep[maxn],ent=0,ans;
void adde(int u,int v,int wt){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;w[ent]=wt;
}
int size[maxn];
char del[maxn];
int mxs,mxw,rem;
void dfs(int x,int f){
    size[x]=1;
    int maxc=0;
    for(int i=st[x];i;i=nxt[i]){
        if(pt[i]==f || del[pt[i]])continue;
        dfs(pt[i],x);
        maxc=max(maxc,size[pt[i]]);
        size[x]+=size[pt[i]];
    }
    maxc=max(maxc,rem-size[x]);
    if(mxs>maxc){
        mxs=maxc;mxw=x;
    }
}
int p[maxn],cnt;
void df2(int x,int f){
    p[++cnt]=dep[x];
    for(int i=st[x];i;i=nxt[i]){
        if(pt[i]==f || del[pt[i]])continue;
        dep[pt[i]]=dep[x]+w[i];
        df2(pt[i],x);
    }
}
int count(int x,int now){
    cnt=0;dep[x]=now;
    df2(x,0);
    sort(p+1,p+1+cnt);
    int l=1,r=cnt,ret=0;
    /*for(int i=1;i<=cnt;i++)cout << p[i] << " ";
      cout << endl;*/
    while(l<r){
        if(p[r]+p[l]<=m)ret+=r-l++;
        else r--;
    }
    return ret;
}
void work(int x){
    //printf("work(%d)\n",x);cout << flush;
    del[x]=true;
    ans+=count(x,0);
    //cout << "ans = " << ans << endl;
    for(int i=st[x];i;i=nxt[i]){
        if(del[pt[i]])continue;
        ans-=count(pt[i],w[i]);
        //cout << "ans = " << ans << endl;
        mxs=2147483640;
        rem=size[pt[i]];
        dfs(pt[i],x);
        work(mxw);
    }
}
int main(){
    while(scanf("%d%d",&n,&m)==2){
        if(n==0 && m==0)break;
        ans=0;ent=0;
        memset(st,0,sizeof(st));
        memset(nxt,0,sizeof(nxt));
        memset(del,0,sizeof(del));
        int u,v,wt;
        for(int i=1;i<n;i++){
            u=geti();v=geti();wt=geti();
            adde(u,v,wt);adde(v,u,wt);
        }
        mxs=2147483640;
        rem=n;
        dfs(1,0);
        work(mxw);
        printf("%d\n",ans);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
