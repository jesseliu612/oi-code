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
const int mo = 1e9;
ll n,m,ns[10][10],du[100][100],img[100][100],k[100][100],pnt=0;
char xmg[10][10];
inline bool check(int x,int y){
    return (xmg[x][y]!='*' && x>=1 && x<=n && y>=1 && y<=m);
}
inline void adde(int a,int b,int c,int d){
    if(!check(a,b) || !check(c,d))return;
    du[ns[a][b]][ns[a][b]]++;
    du[ns[c][d]][ns[c][d]]++;
    img[ns[a][b]][ns[c][d]]=1;
    img[ns[c][d]][ns[a][b]]=1;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    n=geti();m=geti();
    for(int i=1;i<=n;i++){
        scanf("%s",xmg[i]+1);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(xmg[i][j]=='*')continue;
            ns[i][j]=++pnt;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(xmg[i][j]=='*')continue;
            adde(i,j,i+1,j);
            adde(i,j,i,j+1);
        }
    }
    for(int i=1;i<=pnt;i++){
        for(int j=1;j<=pnt;j++){
            k[i][j]=du[i][j]-img[i][j];
        }
    }
    //cout << "pnt = " << pnt << endl;
    ll ans=1;
    for(int i=1;i<pnt;i++){
        //cout << "i = " << i << endl;
        if(k[i][i]==0){
            for(int j=i+1;j<pnt;j++){
                if(k[j][i]!=0){
                    for(int h=1;h<=pnt;h++)swap(k[j][h],k[i][h]);
                    break;
                }
            }
        }
        if(k[i][i]==0){
            putchar('0');
            return 0;
        }
        for(int j=i+1;j<pnt;j++){
            while(k[j][i]!=0){
                int t=(k[i][i]/k[j][i]);
                for(int h=1;h<pnt;h++){
                    k[i][h]=((k[i][h]-k[j][h]*t))%mo;
                }
                swap(k[i],k[j]);
                ans*=-1;
            }
        }
        (ans*=k[i][i])%=mo;
    }

    printf("%lld",(ans+mo)%mo);
	
    fclose(stdin);
    fclose(stdout);
    return 0;
}
