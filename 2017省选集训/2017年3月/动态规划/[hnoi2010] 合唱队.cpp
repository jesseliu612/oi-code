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
const int mo = 19650827;
const int maxn = 1000 + 52;
int n,a[maxn],f[maxn][maxn],g[maxn][maxn];
int G(int l,int r);
inline int F(int l,int r){
    if(r-l==1){
        return a[l]<a[r];
    }
    if(f[l][r]!=-1)return f[l][r];
    int &ret=f[l][r];ret=0;
    if(a[l]<a[l+1])ret+=F(l+1,r);
    if(a[l]<a[r])ret+=G(l+1,r);
    ret%=mo;
    return ret;
}
inline int G(int l,int r){
    if(r-l==1){
        return a[l]<a[r];
    }
    if(g[l][r]!=-1)return g[l][r];
    int &ret=g[l][r];ret=0;
    if(a[r]>a[r-1])ret+=G(l,r-1);
    if(a[r]>a[l])ret+=F(l,r-1);
    ret%=mo;
    return ret;
}
int main(){
    freopen("chorus.in","r",stdin);
    freopen("chorus.out","w",stdout);

    memset(f,-1,sizeof(f));memset(g,-1,sizeof(g));
    n=geti();
    if(n==1){
        putchar('1');return 0;
    }
    for(int i=1;i<=n;i++)a[i]=geti();
    printf("%d\n",(F(1,n)+G(1,n))%mo);
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
