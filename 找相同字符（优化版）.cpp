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
const int maxn = 200000*4+100;
int n,m;
char s[maxn],s1[maxn],s2[maxn];
int sa[maxn],t1[maxn],t2[maxn],c[maxn],rk[maxn],h[maxn];
void buildsa(){
    int *x=t1,*y=t2;
    for(int i=1;i<=m;i++)c[i]=0;
    for(int i=1;i<=n;i++)c[x[i]=s[i]]++;
    for(int i=2;i<=m;i++)c[i]+=c[i-1];
    for(int i=n;i>=1;i--)sa[c[x[i]]--]=i;
    for(int k=1;k<n;k<<=1){
        int p=0;
        for(int i=n;i>=n-k+1;i--)y[++p]=i;
        for(int i=1;i<=n;i++)if(sa[i]>k)y[++p]=sa[i]-k;
        for(int i=1;i<=m;i++)c[i]=0;
        for(int i=1;i<=n;i++)c[x[y[i]]]++;
        for(int i=2;i<=m;i++)c[i]+=c[i-1];
        for(int i=n;i>=1;i--)sa[c[x[y[i]]]--]=y[i];
        p=0;
        for(int i=1;i<=n;i++){
            if(i!=1 && x[sa[i]]==x[sa[i-1]] && x[sa[i]+k]==x[sa[i-1]+k])y[sa[i]]=p;
            else y[sa[i]]=++p;
        }
        m=p;swap(x,y);
        if(p>=n)break;
    }
}
void geth(){
    for(int i=1;i<=n;i++)rk[sa[i]]=i;
    h[1]=0;
    for(int i=1;i<=n;i++){
        if(rk[i]==1)continue;
        h[rk[i]]=h[rk[i-1]];if(h[rk[i]])h[rk[i]]--;
        while(s[i+h[rk[i]]]==s[sa[rk[i]-1]+h[rk[i]]] && sa[rk[i]-1]+h[rk[i]]<=n && i+h[rk[i]]<=n)h[rk[i]]++;
    }
}
int st[maxn],pt[maxn],nxt[maxn],ent=0;
void adde(int u,int v){
    pt[++ent]=v;nxt[ent]=st[u];st[u]=ent;
}
int bef[maxn],aft[maxn],prea[maxn],preb[maxn];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    scanf("%s%s",s1+1,s2+1);
    int len1=strlen(s1+1),len2=strlen(s2+1);
    n=0;
    for(int i=1;i<=len1;i++){
        s[++n]=s1[i];
    }
    s[++n]='z'+1;
    for(int i=1;i<=len2;i++){
        s[++n]=s2[i];
    }
    for(int i=1;i<=n;i++)s[i]-='a'-1;
    m=27;
    buildsa();
    geth();
    for(int i=1;i<=n;i++){
        adde(h[i],i);
    }
    ll ans=0;
    for(int i=1;i<=n;i++)bef[i]=i-1,aft[i]=i+1;
    bef[n+1]=n;
    for(int i=1;i<=n;i++){
        prea[i]=prea[i-1];preb[i]=preb[i-1];
        if(sa[i]<=len1)prea[i]+=1;
        else if(sa[i]>len1+1)preb[i]+=1;
    }
    for(int i=n;i>=1;i--){
        ll curans=0;
        for(int j=st[i];j;j=nxt[j]){
            int r=pt[j];
            //cout << "r = " << r << endl;
            //printf("%d , %d\n",aft[r]-1,bef[r]-1);
            curans+=(prea[aft[r]-1]-prea[r-1])*(preb[r-1]-preb[bef[r]-1])+(preb[aft[r]-1]-preb[r-1])*(prea[r-1]-prea[bef[r]-1]);
            bef[aft[r]]=bef[r];aft[bef[r]]=aft[r];
        }
        /*for(int j=1;j<=n+1;j++){
            printf("j = %d, bef[%d] = %d, aft[%d] = %d, h = %d\n",j,j,bef[j],j,aft[j],h[j]);
        }
        cout << endl;*/
        ans+=curans*i;
    }
    cout << ans;
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
