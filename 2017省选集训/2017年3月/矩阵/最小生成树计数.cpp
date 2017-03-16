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
const int mo = 31011;
const int maxm = 1000 + 100;
const int maxn = 100 + 10;
struct edge{
    int u,v,w;
}e[maxm],t[maxn][maxm];
int bel[maxn],mx[maxn],val[maxn],cnt[maxn],tmp[maxn];
int du[maxn][maxn],xmg[maxn][maxn];
ll K[maxn][maxn];
bool cmp(edge x,edge y){
    return x.w<y.w;
}
int fa(int x){
    return mx[x]==x?x:mx[x]=fa(mx[x]);
}
void un(int x,int y){
    x=fa(x);y=fa(y);mx[x]=y;
}
ll det(int pnt){
    if(pnt==1)return 1;
    ll ans=1;
    for(int i=1;i<pnt;i++){
        for(int j=i+1;j<pnt;j++){
            while(K[j][i]!=0){
                ll t=(K[i][i]/K[j][i]);
                for(int h=1;h<pnt;h++){
                    K[i][h]=((K[i][h]-K[j][h]*t)%mo+mo)%mo;
                }
                swap(K[i],K[j]);
                ans*=-1;
            }
        }
        (ans*=K[i][i])%=mo;
    }
    return ans;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int n,m;
    n=geti();m=geti();
    for(int i=1;i<=n;i++)mx[i]=i,bel[i]=i,cnt[i]=0;
    for(int i=1;i<=m;i++){
        e[i].u=geti();e[i].v=geti();e[i].w=geti();
    }
    sort(e+1,e+1+m,cmp);
    ll ans=1;
    int tot=0,bef=0;
    for(int i=1;i<=m;i++){
        t[bel[e[i].u]][++cnt[bel[e[i].u]]].u=bel[e[i].u];
        t[bel[e[i].u]][cnt[bel[e[i].u]]].v=bel[e[i].v];
        t[bel[e[i].v]][++cnt[bel[e[i].v]]].u=bel[e[i].v];
        t[bel[e[i].v]][cnt[bel[e[i].v]]].v=bel[e[i].u];
        if(fa(e[i].u)!=fa(e[i].v)){
            un(e[i].u,e[i].v);
            ++tot;
        }
        if(i==m || e[i].w!=e[i+1].w){
            if(tot==bef)continue;
            bef=tot;
            set<int> s[110];
            for(int j=1;j<=n;j++)s[fa(j)].insert(bel[j]);
            for(int j=1;j<=n;j++){
                if(s[j].size()>0){
                    set<int> ::iterator itr;
                    int tt=0;
                    for(itr=s[j].begin();itr!=s[j].end();itr++){
                        val[*itr]=++tt;
                        tmp[tt]=*itr;
                    }
                    //cout << "tt = " << tt << endl;
                    for(int k=1;k<=tt;k++){
                        for(int h=1;h<=tt;h++){
                            du[k][h]=0;xmg[k][h]=0;
                        }
                    }
                    for(int k=1;k<=tt;k++){
                        for(int h=1;h<=cnt[tmp[k]];h++){
                             du[ val[bel[t[tmp[k]][h].u]] ][ val[bel[t[tmp[k]][h].u]] ]++;
                            xmg[ val[bel[t[tmp[k]][h].u]] ][ val[bel[t[tmp[k]][h].v]] ]++;
                        }
                    }
                    for(int k=1;k<=tt;k++){
                        for(int h=1;h<=tt;h++){
                            K[k][h]=(du[k][h]-xmg[k][h]+mo)%mo;
                        }
                    }
                    (ans*=det(tt))%=mo;
                }
            }
            for(int j=1;j<=n;j++)bel[j]=fa(j),cnt[j]=0;
            if(tot==n-1)break;
        }
    }
    if(tot>=n-1)cout << (ans+mo)%mo;
    else cout << 0;
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
