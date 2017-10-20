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
const int maxn = 1000000+52;
int x,k,t;
int f[maxn],q[maxn];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int T=geti();
    while(T--){
        memset(f,0x7f,sizeof(f));
        memset(q,0,sizeof(q));
        x=geti();k=geti();t=geti();
        int hd=0,tl=0;
        f[1]=0;q[++tl]=1;
        for(int i=2;i<=x;i++){
            while(hd<tl && q[hd+1]<i-t){
                hd++;
            }
            if(hd<tl)f[i]=f[q[hd+1]]+1;
            if(i%k==0)f[i]=min(f[i],f[i/k]+1);
            while(hd<tl && f[q[tl]]>f[i])tl--;
            q[++tl]=i;
        }
        printf("%d\n",f[x]);
    }
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
