#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
ll geti(){
    ll ret=0;char ch=getchar();char k=0;
    while((ch<'0' || ch>'9') && ch!='-')ch=getchar();
    if(ch=='-')k=1,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return k?-ret:ret;
}
const int maxn = 100000 + 100;
ll n,k,w[maxn];
struct node{
    ll w,dep;
};
bool operator < (node x,node y){
    if(x.w!=y.w)return x.w>y.w;
    else return x.dep>y.dep;
}
priority_queue<node> q;
int main(){
    n=geti();k=geti();
    for(int i=1;i<=n;i++)w[i]=geti(),q.push((node){w[i],0});
    while((n-1)%(k-1)){
        q.push((node){0,0});++n;
    }
    ll ans=0;
    while(q.size()>1){
        ll tot=0,mxdp=0;
        for(int i=1;i<=k;i++){
            node r=q.top();q.pop();
            tot+=r.w;mxdp=max(mxdp,r.dep);
        }
        ans+=tot;
        q.push((node){tot,mxdp+1});
    }
    node res=q.top();
    printf("%lld\n%lld",ans,res.dep);
    return 0;
}
