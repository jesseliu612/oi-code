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
const int maxn = 800000+52;
int n,m;
char s[maxn];
int sa[maxn*2],t1[maxn*2],t2[maxn*2],c[maxn*2];
void buildsa(){
    int *x=t1,*y=t2;
    for(int i=1;i<=m;i++)c[i]=0;
    for(int i=1;i<=n;i++)c[x[i]=s[i]-'a'+1]++;
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
        if(p>=n)break;
        swap(x,y);
        m=p;
    }
}
int h[maxn],rk[maxn];
void geth(){
    for(int i=1;i<=n;i++)rk[sa[i]]=i;
    h[1]=0;
    for(int i=1;i<=n;i++){
        if(rk[i]==1)continue;
        h[rk[i]]=h[rk[i-1]];
        if(h[rk[i]])h[rk[i]]--;
        while(s[i+h[rk[i]]]==s[sa[rk[i]-1]+h[rk[i]]] && i+h[rk[i]]<=n && sa[rk[i]-1]+h[rk[i]]<=n){
            h[rk[i]]++;
        }
    }
}
int st[maxn][18],ql[maxn];
void buildst(){
    for(int i=1;i<=n;i++)st[i][0]=h[i];
    for(int j=1;j<=17;j++){
        for(int i=1;i<=n;i++){
            st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
        }
    }
}
int rmq(int l,int r){
    if(l>r)swap(l,r);
    ++l;
    int len=ql[r-l+1];
    //printf("st[%d][%d] = %d\n",l,len,st[l][len]);
    //printf("rmq(%d,%d) = min(%d,%d) = %d\n",l,r,st[l][len],st[r-(1<<len)+1][len],min(st[l][len],st[r-(1<<len)+1][len]));
    return min(st[l][len],st[r-(1<<len)+1][len]);
}
int main(){
    freopen("repeat.in","r",stdin);
    freopen("repeat.out","w",stdout);

    scanf("%s",s+1);
    n=strlen(s+1);m=256;
    //cout << "n = " << n << endl;
    buildsa();
    geth();
    /*for(int i=1;i<=n;i++){
        for(int j=sa[i];j<=n;j++){
            cout<<s[j] <<" ";
        }
        cout << " " << h[i] << endl;
    }
    */
    buildst();
    for(int i=2;i<=n;i++){
        ql[i]=(i&(i-1))?ql[i-1]:ql[i-1]+1;
    }
    int mx=0;
    for(int l=1;l<=n;l++){
        int lim=1;
        for(int i=1;i<n;i+=l){
            //printf("l = %d, i = %d\n",l,i);
            int lcp=rmq(rk[i],rk[i+l]);
            if(lcp<l)continue;
            int mv=i-(l-lcp%l);
            mx=max(mx,lcp/l+1);
            //printf("  lcp(%d-%d,%d-%d) = %d, cur = %d\n",i,rk[i],i+l,rk[i+l],lcp,lcp/l);
            if(mv<=lim)continue;
            lcp=rmq(rk[mv],rk[mv+l]);
            mx=max(mx,lcp/l+1);
            lim=i;
        }
    }
    cout << mx;
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
