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
const int maxn = 100000 + 100;
ll f[maxn];
int main(){
    register int c[4],d[4],tot,s,a[16],cur;
    register ll ans;
    for(int i=0;i<=15;++i)a[i]=(__builtin_popcount(i)&1)?-1:1;
    for(int i=0;i<4;++i)c[i]=geti();
    f[0]=1;
    for(int j=0;j<4;++j){
        for(int i=1;i<maxn;++i){
            if(i-c[j]>=0){
                f[i]+=f[i-c[j]];
            }
        }
    }
    tot=geti();
    while(tot--){
        for(int i=0;i<4;++i)d[i]=geti();
        s=geti();
        ans=0;
        for(int i=0;i<=15;++i){
            cur=s;
            for(int j=0;j<4;++j){
                if((i>>j)&1){
                    cur-=c[j]*(d[j]+1);
                }
            }
            if(cur>=0){
                ans+=a[i]*f[cur];
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
