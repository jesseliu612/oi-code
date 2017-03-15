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
const int mo = 10000;
int n,m,st,ed,k;
struct mtx{
    int c[50][50];
};
mtx operator * (mtx &a,mtx &b){
    mtx c={0};
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                (c.c[i][k]+=a.c[i][j]*b.c[j][k])%=mo;
            }
        }
    }
    return c;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    n=geti();m=geti();st=geti();ed=geti();k=geti();
    int u,v;
    mtx w={0},t[13];
    for(int i=1;i<=m;i++){
        u=geti();v=geti();
        w.c[u][v]=1;w.c[v][u]=1;
    }
    for(int i=1;i<=12;i++)t[i]=w;
    int nfish=geti(),p[4];
    for(int i=1;i<=nfish;i++){
        u=geti();
        for(int j=0;j<u;j++)p[j]=geti();
        for(int j=1;j<=12;j++){
            for(int k=0;k<n;k++){
                t[j].c[k][p[j%u]]=0;
            }
        }
    }
    mtx bef={0},z=t[1],ret={0};
    bef.c[0][st]=1;
    for(int i=2;i<=12;i++){
        z=z*t[i];
    }
    for(int i=0;i<n;i++)ret.c[i][i]=1;
    u=k/12;
    while(u){
        if(u&1){
            ret=ret*z;
        }
        z=z*z;
        u>>=1;
    }
    for(int i=1;i<=k%12;i++){
        ret=ret*t[i];
    }
    cout << (bef*ret).c[0][ed];
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
