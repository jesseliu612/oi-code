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
const int maxn = 50000 + 1000;
int st[maxn],pt[maxn*2],nxt[maxn*2],ent=0;
ll w[maxn*2];
int n,m;
void adde(int u,int v,int wt){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;w[ent]=wt;
}
int army[maxn],is_army[maxn];
ll dis[maxn];
int fa[17][maxn];
struct AM{
    int id;
    ll rem;
}rrt[maxn];
int drt[maxn];
char cov[maxn];
void dfs(int x,int f){
    for(int i=st[x];i;i=nxt[i]){
        if(pt[i]==f)continue;
        fa[0][pt[i]]=x;
        dis[pt[i]]=dis[x]+w[i];
        dfs(pt[i],x);
    }
}
void goup(int p,ll x){
    //printf("goup(%d,%lld)\n",p,x);
    ll cnt=0;
    cov[p]=true;
    //printf("cov[%d] = true\n",p);
    for(int j=16;j>=0;j--){
        //printf("curdis = %lld\n",dis[p]-dis[fa[j][p]]);
        if(dis[p]-dis[fa[j][p]]+cnt<=x){
            cnt+=dis[p]-dis[fa[j][p]];
            p=fa[j][p];
            cov[p]=true;
            //printf("cov[%d] = true\n",p);
            //printf("cnt = %lld\n",cnt);
        }
    }
}
void df2(int x,int f){
    //printf("cov[%d] = %d\n",x,cov[x]);
    if(!cov[x]){
        int flag=0,cnt=0;
        for(int i=st[x];i;i=nxt[i]){
            if(pt[i]==f)continue;
            ++cnt;
            df2(pt[i],x);
            if(!cov[pt[i]])flag=1;
        }
        if(!flag && cnt>0){
            cov[x]=true;
        }
    }
    else{
        for(int i=st[x];i;i=nxt[i]){
            if(pt[i]==f)continue;
            cov[pt[i]]=true;
            df2(pt[i],x);
        }
    }
    //printf("cov[%d] = %d\n",x,cov[x]);
}
bool cmpr(AM x,AM y){
    return x.rem<y.rem;
}
bool cmpd(int x,int y){
    return dis[x]<dis[y];
}
int topson(int p){
    for(int i=16;i>=0;i--){
        if(fa[i][p]>1)p=fa[i][p];
    }
    return p;
}
bool check(ll x){
    //printf("check(%lld)\n",x);
    memset(cov,0,sizeof(cov));
    int cnt=0,cnt2=0;
    for(int i=1;i<=m;i++){
        if(dis[army[i]]<=x){
            int tp=topson(army[i]);
            rrt[++cnt].id=tp;
            rrt[cnt].rem=x-dis[army[i]];
            //printf("dis[%d]=%lld<=%lld\n",army[i],dis[army[i]],x);
        }
        else{
            goup(army[i],x);
        }
    }
    df2(1,0);
    for(int i=st[1];i;i=nxt[i]){
        if(!cov[pt[i]])drt[++cnt2]=pt[i];
    }
    sort(rrt+1,rrt+cnt+1,cmpr);
    sort(drt+1,drt+cnt2+1,cmpd);
    /*printf("reach root:\n");
    for(int i=1;i<=cnt;i++){
        printf("%d,%lld\n",rrt[i].id,rrt[i].rem);
    }
    printf("uncovered points:\n");
    for(int i=1;i<=cnt2;i++){
        printf("%d\n",drt[i]);
    }
    */
    if(cnt2>cnt)return false;
    if(cnt2==0)return true;
    int p=1,v=1;
    while(p<=cnt && v<=cnt2){
        /*printf("p = %d, v = %d\n",p,v);
          printf("cov[%d] = %d\n",rrt[p].id,cov[rrt[p].id]);*/
        if(cov[drt[v]]){
            //cout << "a" << endl;
            ++v;continue;
        }
        if(!cov[rrt[p].id]){
            //cout << "b" << endl;
            cov[rrt[p].id]=true;
            ++p;continue;
        }
        if(rrt[p].rem>=dis[drt[v]]){
            //cout << "c" << endl;
            cov[drt[v]]=true;
            ++p;++v;
        }
        else{
            //cout << "d" << endl;
            ++p;
        }
    }
    while(v<=cnt2 && cov[drt[v]])++v;
    if(v<=cnt2)return false;
    return true;
}
int main(){
    n=geti();
    int u,v,wt;
    for(int i=1;i<n;i++){
        u=geti();v=geti();wt=geti();
        adde(u,v,wt);adde(v,u,wt);
    }
    m=geti();
    for(int i=1;i<=m;i++){
        army[i]=geti();
        is_army[army[i]]=true;
    }
    dfs(1,0);
    for(int j=1;j<=16;j++){
        for(int i=1;i<=n;i++){
            fa[j][i]=fa[j-1][fa[j-1][i]];
        }
    }
    //for(int i=2;i<=n;i++)printf("dis[%d] = %lld\n",i,dis[i]);
    ll l=0,r=50000000000000,mid,rt;
    while(l<=r){
        mid=(l+r)>>1;
        if(check(mid)){
            r=mid-1;
            rt=mid;
        }
        else{
            l=mid+1;
        }
    }
    cout << rt;
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
