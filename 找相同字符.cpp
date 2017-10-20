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
const int maxn = 800000+100;
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
        swap(x,y);
        m=p;
        if(p>=n)break;
    }
}
void geth(){
    for(int i=1;i<=n;i++)rk[sa[i]]=i;
    h[1]=0;
    for(int i=1;i<=n;i++){
        if(rk[i]==1)continue;
        h[rk[i]]=h[rk[i-1]];
        if(h[rk[i]])h[rk[i]]--;
        while(s[i+h[rk[i]]]==s[sa[rk[i]-1]+h[rk[i]]])h[rk[i]]++;
    }
}
int st[maxn][21],stw[maxn][21];
void buildst(){
    for(int i=1;i<=n;i++){
        st[i][0]=h[i];stw[i][0]=i;
    }
    for(int j=1;j<=20;j++){
        for(int i=1;i<=n;i++){
            if(st[i][j-1]>st[i+(1<<(j-1))][j-1]){
                st[i][j]=st[i+(1<<(j-1))][j-1];
                stw[i][j]=stw[i+(1<<(j-1))][j-1];
            }
            else{
                st[i][j]=st[i][j-1];
                stw[i][j]=stw[i][j-1];
            }
        }
    }
}
int ql[maxn];
ll prea[maxn],preb[maxn];
ll ans=0;
void calc(int l,int r){
    if(l>=r)return;
    int mid;
    if(st[l+1][ql[r-l]] < st[r-(1<<ql[r-l])+1][ql[r-l]]){
        mid=stw[l+1][ql[r-l]];
    }
    else{
        mid=stw[r-(1<<ql[r-l])+1][ql[r-l]];
    }
    ans+=((prea[mid-1]-prea[l-1])*(preb[r]-preb[mid-1])+(preb[mid-1]-preb[l-1])*(prea[r]-prea[mid-1]))*h[mid];
    calc(l,mid-1);calc(mid,r);
}
int main(){
    m=256;
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
    s[n+1]=0;
    for(int i=2;i<=n;i++){
        ql[i]=(i&(i-1))?ql[i-1]:ql[i-1]+1;
    }
    buildsa();
    geth();
    buildst();
    for(int i=1;i<=n;i++){
        prea[i]=prea[i-1];
        preb[i]=preb[i-1];
        if(sa[i]<=len1)prea[i]++;
        else if(sa[i]>len1+1)preb[i]++;
    }
    calc(1,n);
    cout << ans;
     
    fclose(stdin);
    fclose(stdout);
    return 0;
}
