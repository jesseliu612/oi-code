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
const int maxn = 50000 + 100;
struct land{
    int x,y;
}a[maxn];
struct node{
    ll id,k,b;
}q[maxn];
int n,t;
bool cmp(const land &x,const land &y){
    return x.x==y.x?x.y>y.y:x.x<y.x;
}
char del[maxn];
ll c[maxn],w[maxn],f[maxn];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    t=geti();
    for(int i=1;i<=t;i++){
        a[i].x=geti();a[i].y=geti();
    }
    sort(a+1,a+t+1,cmp);
    int last=a[t].y;
    for(int i=t-1;i;i--){
        if(a[i].y<=last)del[i]=true;
        else last=a[i].y;
    }
    n=0;
    for(int i=1;i<=t;i++){
        if(!del[i]){
            c[++n]=a[i].y;
            w[n]=a[i].x;
        }
    }
    int hd=0,tl=1;
    q[tl].k=c[1];
    for(int i=1;i<=n;i++){
        while(tl-hd>1 && q[hd+1].k*w[i]+q[hd+1].b>=q[hd+2].k*w[i]+q[hd+2].b)++hd;
        int j=q[hd+1].id;
        f[i]=q[hd+1].k*w[i]+q[hd+1].b;
        node r;
        r.k=c[i+1];r.b=f[i];
        while(tl-hd>1 && (r.b-q[tl-1].b)*(q[tl-1].k-q[tl].k)<=(q[tl].b-q[tl-1].b)*(q[tl-1].k-r.k))--tl;
        q[++tl]=r;
    }
    cout << f[n];
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
