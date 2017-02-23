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
const int maxn = 620000;
int n,m;
char s[maxn];
int sa[maxn],c[maxn],t[maxn],t1[maxn],h[maxn],rank[maxn];
ll a[maxn],bef[maxn],aft[maxn],val[maxn],mx1[maxn],mx2[maxn],mx3[maxn],mx4[maxn],mn1[maxn],mn2[maxn];
void getsa(){
    int *x=t,*y=t1;
    for(int i=1;i<=m;i++)c[i]=0;
    for(int i=1;i<=n;i++)c[x[i]=s[i]]++;
    for(int i=2;i<=m;i++)c[i]+=c[i-1];
    for(int i=n;i;i--)sa[c[x[i]]--]=i;
    for(int k=1;k<=n;k<<=1){
        int p=0;
        for(int i=n;i>=n-k+1;i--)y[++p]=i;
        for(int i=1;i<=n;i++)if(sa[i]>k)y[++p]=sa[i]-k;
        for(int i=1;i<=m;i++)c[i]=0;
        for(int i=1;i<=n;i++)c[x[y[i]]]++;
        for(int i=2;i<=m;i++)c[i]+=c[i-1];
        for(int i=n;i;i--)sa[c[x[y[i]]]--]=y[i];
        swap(x,y);
        p=0;
        for(int i=1;i<=n;i++){
            if(i!=1&&y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]){
                x[sa[i]]=p;
            }
            else{
                x[sa[i]]=++p;
            }
        }
        m=p;
    }
}
void geth(){
    for(int i=1;i<=n;i++)rank[sa[i]]=i;
    int k=0;
    for(int i=1;i<=n;i++){
        if(k)k--;
        while(s[i+k]==s[sa[rank[i]-1]+k] && i+k<=n)k++;
        h[rank[i]]=k;
    }
}
vector<int> e[maxn];
char cz[maxn];
ll anss[maxn][2];
int main(){
    n=geti();m=129;
    scanf("%s",s+1);
    for(int i=1;i<=n;i++)s[i]=s[i]-'a'+1;
    for(int i=1;i<=n;i++)a[i]=geti();
    getsa();
    /*for(int i=1;i<=n;i++)cout << sa[i]<<" ";
      cout << endl;*/
    geth();
    for(int i=1;i<=n;i++){
        //for(int j=sa[i];j<=n;j++)cout << char(s[j]+'a'-1);
        //printf("  h[%d] = %d\n",i,h[i]);
        e[h[i]].push_back(i);
        //cout << sa[i] << endl;
    }
    mn1[0]=2147483640ll;mn2[0]=-2147483640ll;
    for(int i=1;i<=n;i++){
        bef[i]=i-1;aft[i]=i+1;val[i]=1;
        if(a[sa[i]]>=0){
            mx1[i]=a[sa[i]];mx2[i]=-2147483640ll;
            mn1[i]=a[sa[i]];mn2[i]=-2147483640ll;
        }
        else{
            mx3[i]=a[sa[i]];mx4[i]=2147483640ll;
            mn1[i]=2147483640ll;mn2[i]=a[sa[i]];
        }
    }
    ll ans=0,mx=-1152921504606846976;
    for(int k=n-1;k>=0;k--){
        for(int j=0;j<e[k].size();j++){
            int i=e[k][j];
            bef[aft[i]]=bef[i];
            aft[bef[i]]=aft[i];
            ans+=val[i]*val[bef[i]];
            val[bef[i]]+=val[i];
            cz[i]=true;
            ll tp[4];
            tp[0]=mx1[i];tp[1]=mx2[i];tp[2]=mx1[bef[i]];tp[3]=mx2[bef[i]];
            sort(tp,tp+4);
            mx1[bef[i]]=tp[3];mx2[bef[i]]=tp[2];
            if(mx1[bef[i]]!=0 && mx2[bef[i]]!=0)mx=max(mx,mx1[bef[i]]*mx2[bef[i]]);
            
            tp[0]=mx3[i];tp[1]=mx4[i];tp[2]=mx3[bef[i]];tp[3]=mx4[bef[i]];
            sort(tp,tp+4);
            mx3[bef[i]]=tp[0];mx4[bef[i]]=tp[1];
            if(mx3[bef[i]]!=0 && mx4[bef[i]]!=0)mx=max(mx,mx3[bef[i]]*mx4[bef[i]]);

            if(mn1[i]<mn1[bef[i]])mn1[bef[i]]=mn1[i];
            if(mn2[i]>mn2[bef[i]])mn2[bef[i]]=mn2[i];
            if(mn1[bef[i]]!=0 && mn2[bef[i]]!=0)mx=max(mx,mn1[bef[i]]*mn2[bef[i]]);
        }
        anss[k][0]=ans;anss[k][1]=mx;if(ans==0)anss[k][1]=0;
    }
    for(int i=0;i<n;i++)printf("%lld %lld\n",anss[i][0],anss[i][1]);
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
