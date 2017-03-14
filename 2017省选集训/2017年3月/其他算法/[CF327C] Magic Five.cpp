#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
const int inf = 2147483640;
typedef long long ll;
const int mo = 1000000007;
int k,n;
char s[110000];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%s%d",s,&k);
    n=strlen(s);
    register ll u=k,cur=1,ret=0,x=1,tot=0;
    for(register int i=0;i<n;++i){
        if(s[i]=='0' || s[i]=='5')tot=(tot+x)%mo;
        x=(x*2)%mo;
    }
    while(u){
        if(u&1)ret=(ret*x+cur)%mo;
        cur=(cur*x+cur)%mo;
        x=(x*x)%mo;
        u>>=1;
    }
    printf("%lld",(ret*tot)%mo);
    return 0;
}
