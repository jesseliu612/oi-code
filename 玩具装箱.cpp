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
const int maxn = 50000+100;
ll n,l;
ll s[maxn],m[maxn],f[maxn];
inline ll sqr(ll x){
    return x*x;
}
struct lines{
    ll k,b,id;
}q[maxn];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    n=geti();l=geti();
    for(int i=1;i<=n;i++){
        s[i]=s[i-1]+geti();
        m[i]=s[i]+i;
    }
    int h=0,t=1;
    for(int i=1;i<=n;i++){
        /*for(int j=0;j<n;j++){
            //f[i]=min(f[i],f[j]+m[j]*m[j]+2*m[j]-2*m[j]*m[i]+m[i]*m[i]-2*m[i]+1-2*l*(m[i]-m[j]-1)+l*l);
            //f[i]=min(f[i],f[j]+l*l+2*l+sqr(m[i])-2*m[i]-2*l*m[i]+sqr(m[j])+2*m[j]+2*l*m[j]-2*m[i]*m[j]+1);
            //f[i]=min(f[i],f[j]+sqr(m[i]-m[j]-1)-2*l*(m[i]-m[j]-1)+l*l);    
        }
        */
        ll c=l*l+2*l+sqr(m[i])-2*l*m[i];
        while((t-h)>1 && q[h+2].k*m[i]+q[h+2].b<=q[h+1].k*m[i]+q[h+1].b){
            ++h;
        }
        int j=q[h+1].id;
        f[i]=f[j]+(s[i]-s[j]+i-j-1-l)*(s[i]-s[j]+i-j-1-l);
        lines r;
        r.k=-2*m[i];
        r.b=m[i]*m[i]+2*m[i]+2*l*m[i]+f[i];
        r.id=i;
        while((t-h)>1 && (long double)(r.b-q[t-1].b)*(q[t-1].k-q[t].k)<=(long double)(q[t].b-q[t-1].b)*(q[t-1].k-r.k)){
            //printf("%lld <= %lld\n",(r.b-q[t-1].b)*(q[t-1].k-q[t].k),(q[t].b-q[t-1].b)*(q[t-1].k-r.k));
            --t;
        }
        q[++t]=r;
        /*printf("f[%d] = %lld, j = %d\n",i,f[i],j);
        for(int j=h+1;j<=t;j++)cout << q[j].id << " ";
        cout << endl;*/
    }
    cout << f[n];
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
