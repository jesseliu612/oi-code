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
const int maxn = 600000+100;
int n,m;
int s[maxn];
int sa[maxn],t1[maxn],t2[maxn],c[maxn];
void build_sa(){
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
        swap(x,y);
        if(p==n)break;
        m=p;
    }
}
int h[maxn],rk[maxn];
void geth(){
    for(int i=1;i<=n;i++)rk[sa[i]]=i;
    h[1]=0;
    for(int i=1;i<=n;i++){
        h[rk[i]]=h[rk[i-1]];
        if(h[rk[i]])h[rk[i]]--;
        while(s[i+h[rk[i]]]==s[sa[rk[i]-1]+h[rk[i]]])h[rk[i]]++;
    }
}
struct node{
    int id;
    int val;
}rd[maxn];
bool cmp(const node &x,const node &y){
    return x.val<y.val;
}
int del[maxn];
int bef[maxn],nxt[maxn],ht[maxn];
ll anss[maxn];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    n=geti();
    for(int i=n;i>=1;i--)rd[i].val=geti(),rd[i].id=i;
    sort(rd+1,rd+1+n,cmp);
    int p=0;
    for(int i=1;i<=n;i++){
        if(i!=1 && rd[i].val==rd[i-1].val)s[rd[i].id]=p;
        else s[rd[i].id]=++p;
    }
    m=p+1;
    build_sa();
    geth();
    for(int i=1;i<=n;i++)anss[n]+=i-h[rk[n-i+1]];
    for(int i=1;i<=n;i++){
        bef[i]=i-1;nxt[i]=i+1;ht[i]=h[i];
    }
    nxt[n]=0;
    for(int i=n;i>1;i--){
        int r=rk[n-i+1];
        anss[i-1]=anss[i]-(i-max(ht[r],ht[nxt[r]]));
        nxt[bef[r]]=nxt[r];bef[nxt[r]]=bef[r];
        ht[nxt[r]]=min(ht[nxt[r]],ht[r]);
    }
    for(int i=1;i<=n;i++)printf("%lld\n",anss[i]);
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}

