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
struct node{
    ll w,id;
}a[2000];
ll p[100];
int n;
bool cmp(const node &x,const node &y){
    return x.w>y.w;
}
bool add(ll x){
    for(int i=62;i>=0;i--){
        if(x&(1ll<<i)){
            if(p[i]==0){
                p[i]=x;return true;
            }
            x^=p[i];
        }
    }
    return false;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    n=geti();
    for(int i=1;i<=n;i++){
        a[i].id=geti();a[i].w=a[i].id;
    }
    sort(a+1,a+1+n,cmp);
    ll ans=0;
    for(int i=1;i<=n;i++){
        if(!add(a[i].id)){
            ans+=a[i].w;
        }
    }
    cout << ans;
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
