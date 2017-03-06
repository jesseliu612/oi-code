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
typedef long double ll;
ll geti(){
    char ch=getchar();while((ch<'0' || ch>'9')&&ch!='-')ch=getchar();
    ll ret=0,k=1;
    if(ch=='-')k=-1,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret*k;
}
const int maxn = 500000 + 100;
int n,l,p;
char str[maxn][30],skip[maxn];
ll c[maxn],s[maxn],f[maxn];
int fst[maxn],zy[maxn];
int bef[maxn],aft[maxn];
ll Pow(ll x){
    x=abs(x-l);
    //printf("Pow(%lld)\n",x);
    /*long double tmp=1;
      for(int i=1;i<=p;i++){
      tmp*=x;
      //if(tmp>(long double)1e18)return -1;
      }
    */
    ll ret=1;
    for(int i=1;i<=p;i++){
        ret*=x;
    }
    return ret;
}
bool check(int p,int x){
    if(p<=x)return false;
    ll ret=Pow(s[p]-s[x]+p-(x+1));
    //if(ret==-1)return false;
    double tmp;
    tmp=ret+f[x];
    //if(tmp>1e18)return false;
    ll ret2=Pow(s[p]-s[bef[x]]+p-(bef[x]+1));
    //if(ret==-1)return true;
    ret+=f[x];ret2+=f[bef[x]];
    //printf("check(%d,%d) = %lld , %lld\n",p,x,ret,ret2);
    return ret<ret2;
}
bool work_dp(){
    fst[0]=1;
    int j=0;
    bef[0]=0;aft[0]=1;
    for(int i=1;i<=n;i++)bef[i]=i-1,aft[i]=i+1;
    for(int i=1;i<=n;i++){
        while(aft[j]<i && fst[aft[j]]<=i){
            j=aft[j];
        }
        ll ret=Pow(s[i]-s[j]+i-(j+1));
        f[i]=f[j]+ret;
        zy[i]=j;
        if(f[i]>1e18){
            skip[i]=true;
            aft[bef[i]]=aft[i];bef[aft[i]]=bef[i];
            continue;
        }
        //printf("f[%d] = %lld , j = %d\n",i,f[i],j);
        while(check(fst[bef[i]],i) && i){
            aft[bef[bef[i]]]=aft[bef[i]];bef[aft[bef[i]]]=bef[bef[i]];
        }
        int l=fst[bef[i]],r=n,rt=-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid,i)){
                rt=mid;r=mid-1;
            }
            else{
                l=mid+1;
            }
        }
        //cout << "rt = " << rt << endl;
        fst[i]=rt;
        if(rt==-1){
            aft[bef[i]]=aft[i];bef[aft[i]]=bef[i];
        }
        /*else if(rt==fst[bef[i]]){
          aft[bef[i-1]]=aft[i-1];bef[aft[i-1]]=bef[i-1];
          }
        */
        //printf("fst[%d] = %d\n",i,fst[i]);
    }
    //printf("f[%d] = %lld\n",n,f[n]);
    if(f[n]>1e18)return false;
    return true;
}
int stk[maxn];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int T=geti();
    while(T--){
        memset(fst,0,sizeof(fst));
        memset(f,0,sizeof(f));
        memset(s,0,sizeof(s));
        memset(skip,0,sizeof(skip));
        n=geti();l=geti();p=geti();
        for(int i=1;i<=n;i++){
            scanf("%s",str[i]);
            c[i]=strlen(str[i]);
            s[i]=s[i-1]+c[i];
            //printf("c[%d] = %lld, s[%d] = %lld\n",i,c[i],i,s[i]);
        }
        if(!work_dp()){
            printf("Too hard to arrange\n");
        }
        else{
            printf("%lld\n",(long long)f[n]);
            int cnt=0;
            int u=n;
            stk[++cnt]=u;
            while(u!=0){
                stk[++cnt]=zy[u];
                u=zy[u];
            }
            for(int i=cnt;i;i--){
                for(int j=stk[i]+1;j<=stk[i-1];j++){
                    printf("%s ",str[j]);
                }
                if(i!=1)puts("");
            }
        }
        printf("--------------------\n");
    }
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
