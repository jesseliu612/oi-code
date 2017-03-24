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
const int maxn = 220 + 52;
int T,n,r,d[maxn],w[maxn];
double p[maxn],ans;
char vis[maxn];
void dfs(int x,double pb,int tot){
    if(x==r+1){
        ans+=pb*tot;
        return;
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            vis[i]=true;
            w[x]=i;
            dfs(x+1,pb*p[i],tot+d[i]);
            vis[i]=false;
            pb=pb*(1-p[i]);
        }
    }
    w[x]=-1;
    dfs(x+1,pb,tot);
}
int main(){
    freopen("arthur.in","r",stdin);
    freopen("arthur.out","w",stdout);

    T=geti();
    while(T--){
        n=geti();r=geti();
        for(int i=1;i<=n;i++)scanf("%lf%d",p+i,d+i);
        ans=0;
        dfs(1,1,0);
        printf("%.10lf\n",ans);
    }
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
