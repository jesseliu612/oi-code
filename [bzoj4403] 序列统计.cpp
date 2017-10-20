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
const int mo = 1e6+3;
ll fct[mo+10],inv[mo+10];
ll C(ll n,ll m){
    if(m>n)return 0;
    return fct[n]%mo*inv[fct[n-m]]%mo*inv[fct[m]]%mo;
}
ll lucas(ll n,ll m){
    if(m==0)return 1;
    return C(n%mo,m%mo)%mo*lucas(n/mo,m/mo)%mo;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int T=geti();
    fct[0]=1;
    for(int i=1;i<=mo;i++)fct[i]=(fct[i-1]*i)%mo;
    inv[1]=1;
    for(int i=2;i<=mo;i++)inv[i]=-(mo/i)*inv[mo%i]%mo;
    ll n,m,l,r;
    while(T--){
        m=geti();l=geti();r=geti();
        n=r-l+1;
        printf("%lld\n",((lucas(n+m,m)-1)%mo+mo)%mo);
    }
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
