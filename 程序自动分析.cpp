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
const int maxn = 100000+100;
int c[maxn][3];
struct Opt{
    int val,id,pls;
}a[maxn*2];
bool cmp(Opt x,Opt y){
    return x.val<y.val;
}
int n,m;
struct Un{
    int mx[maxn*2];
    void init(int n){
        for(int i=1;i<=n*2;i++)mx[i]=i;
    }
    int fa(int x){
        return mx[x]==x?x:mx[x]=fa(mx[x]);
    }
    void un(int x,int y){
        x=fa(x);y=fa(y);mx[x]=y;
    }
    bool query(int x,int y){
        x=fa(x);y=fa(y);return x==y;
    }
}u;
int main(){
    int T=geti();
    while(T--){
        n=geti();
        u.init(n);
        for(int i=1;i<=n;i++){
            a[i*2-1].val=geti();a[i*2].val=geti();c[i][2]=geti();
            a[i*2-1].id=i;a[i*2-1].pls=0;
            a[i*2].id=i;a[i*2].pls=1;
        }
        sort(a+1,a+n*2+1,cmp);
        int s=0;
        for(int i=1;i<=2*n;i++){
            if(i!=1 && a[i].val==a[i-1].val){
                c[a[i].id][a[i].pls]=s;
            }
            else{
                c[a[i].id][a[i].pls]=++s;
            }
        }
        for(int i=1;i<=n;i++){
            if(c[i][2]==1){
                u.un(c[i][0],c[i][1]);
            }
        }
        int flag=0;
        for(int i=1;i<=n;i++){
            if(c[i][2]==0){
                if(u.query(c[i][0],c[i][1])){
                    flag=1;break;
                }
            }
        }
        if(flag){
            printf("NO\n");
        }
        else{
            printf("YES\n");
        }
        cout << flush;
    }
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
