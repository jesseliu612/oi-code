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
#include <bitset>
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
const int maxn = 5000 + 100;
int n,m,q,s;
int x0,a,b,c,d;
int x[maxn*maxn],t[maxn*maxn];
bitset<maxn> cz[maxn];
void clr(int x,int y){
    cz[x][y]=true;
    int i,j;
    if(y<m && x>1){
        for(i=x-1;i>=1;i--){
            if(cz[i][y+1])break;
        }
        for(j=y+1;j<=m;j++){
            if(cz[x-1][j])break;
        }
        for(;i<x;i++){
            for(int k=j;k>y;k--){
                cz[i][k]=true;
            }
        }
    }
    if(x<n && y>1){
        for(i=x+1;i<=n;i++){
            if(cz[i][y-1])break;
        }
        for(j=y-1;j>=1;j--){
            if(cz[x+1][j])break;
        }
        for(;i>x;i--){
            for(int k=j;k<y;k++){
                cz[i][k]=true;
            }
        }
    }
}
int main(){
    x0=geti();a=geti();b=geti();c=geti();d=geti();
    n=geti();m=geti();q=geti();s=n*m;
    x[0]=x0;
    for(int i=1;i<=s;i++){
        x[i]=((((ll)((ll)a*x[i-1])%d)*x[i-1])%d+(ll)((ll)b*x[i-1])%d+(ll)c)%d;
    }
    for(int i=1;i<=s;i++)t[i]=i;
    for(int i=1;i<=s;i++){
        swap(t[i],t[x[i]%i+1]);
    }
    int u,v;
    for(int i=1;i<=q;i++){
        u=geti();v=geti();
        swap(t[u],t[v]);
    }
    for(int i=1;i<=s;i++){
        x[t[i]]=i;
    }
    for(int i=1;i<=s;i++){
        int a=(x[i]-1)/m+1;int b=(x[i]-1)%m+1;
        if(cz[a][b])continue;
        printf("%d ",i);
        clr(a,b);
    }	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
