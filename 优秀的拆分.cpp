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
const int maxn = 300000+100;
int n;
int ql[maxn];
struct suffixarray{
    int m;
    char s[maxn*2];
    int sa[maxn*2],t1[maxn*2],t2[maxn*2],c[maxn*2],h[maxn],rk[maxn];
    int st[maxn][16];
    void getsa(){
        int *x=t1,*y=t2;
        for(int i=1;i<=m;i++)c[i]=0;
        for(int i=1;i<=n;i++)c[x[i]=s[i]]++;
        for(int i=2;i<=m;i++)c[i]+=c[i-1];
        for(int i=n;i>=1;i--)sa[c[x[i]]--]=i;
        for(int k=1;k<=n;k<<=1){
            int p=0;
            for(int i=n;i>=n-k+1;i--)y[++p]=i;
            for(int i=1;i<=n;i++)if(sa[i]>k)y[++p]=sa[i]-k;
            for(int i=1;i<=m;i++)c[i]=0;
            for(int i=1;i<=n;i++)c[x[y[i]]]++;
            for(int i=2;i<=m;i++)c[i]+=c[i-1];
            for(int i=n;i>=1;i--)sa[c[x[y[i]]]--]=y[i];
            p=0;
            swap(x,y);
            for(int i=1;i<=n;i++){
                if(i!=1 && y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k])x[sa[i]]=p;
                else x[sa[i]]=++p;
            }
            if(p>=n)break;
            m=p;
        }
    }
    void geth(){
        for(int i=1;i<=n;i++)rk[sa[i]]=i;
        h[1]=0;
        for(int i=1;i<=n;i++){
            h[rk[i]]=h[rk[i-1]];
            if(h[rk[i]])h[rk[i]]--;
            while(s[i+h[rk[i]]]==s[sa[rk[i]-1]+h[rk[i]]])h[rk[i]]++;
        }
    }
    void buildrmq(){
        for(int i=1;i<=n;i++){
            st[i][0]=h[i];
        }
        for(int j=1;j<=15;j++){
            for(int i=1;i<=n;i++){
                st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
            }
            
        }
    }
    int rmq(int l,int r){
        if(l>r)swap(l,r);
        l++;
        return min(st[l][ql[r-l+1]],st[r-(1<<ql[r-l+1])+1][ql[r-l+1]]);
    }
}s1,s2;
ll v1[maxn],v2[maxn];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    for(int i=2;i<maxn;i++){
        ql[i]=(i&(i-1))?ql[i-1]:ql[i-1]+1;
    }
    int T=geti();
    while(T--){
        memset(v1,0,sizeof(v1));memset(v2,0,sizeof(v2));
        scanf("%s",s1.s+1);
        n=strlen(s1.s+1);
        s1.m=256;s2.m=256;
        for(int i=n+1;i>=0;i--)s2.s[i]=s1.s[n-i+1];
        s1.getsa();s2.getsa();
        s1.geth();s1.buildrmq();
        s2.geth();s2.buildrmq();
        for(int i=1;i<=n;i++){
            int l1=0,r1=0,l2=0,r2=0;
            for(int j=1;j<n;j+=i){
                int t1=s1.rmq(s1.rk[j],s1.rk[j+i]);
                int t2=s2.rmq(s2.rk[n-j+1],s2.rk[n-j-i+1]);
                int len=(j+t1-1)-(j+i-t2+1)+1;
                if(len<0)continue;
                l1=max(j-i+1,j-t2+1),r1=min(j,j-t2+1+len);
                if(l1>r1)continue;
                l2=l1+2*i-1,r2=r1+2*i-1;
                v1[l1]++;v1[r1+1]--;
                v2[l2]++;v2[r2+1]--;
            }
        }
        for(int i=2;i<=n;i++)v1[i]+=v1[i-1];
        for(int i=2;i<=n;i++)v2[i]+=v2[i-1];
        ll res=0;
        for(int i=2;i<=n;i++){
            res+=v1[i]*v2[i-1];
        }
        printf("%lld\n",res);
    }
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
