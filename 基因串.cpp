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
const int inf = 1000;
typedef long long ll;
ll geti(){
    char ch=getchar();while((ch<'0' || ch>'9')&&ch!='-')ch=getchar();
    ll ret=0,k=1;
    if(ch=='-')k=-1,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return ret*k;
}
int n,k;
struct rule{
    int a,b;
};
vector<rule> rl[30];
char s[110];
int f[110][110][30],g[110][110];
int dfs(int l,int r,int c){
    if(f[l][r][c]!=-1)return f[l][r][c];
    if(l==r){
        if(c==s[l]){
            f[l][r][c]=1;
            return true;
        }
        f[l][r][c]=0;
        return false;
    }
    int &a=f[l][r][c];a=0;
    for(int j=0;j<rl[c].size();j++){
        for(int d=l;d<r;d++){
            int ct1=dfs(l,d,rl[c][j].a);
            int ct2=dfs(d+1,r,rl[c][j].b);
            if(ct1>0 && ct2>0){
                if(ct1==1 && ct2==1){
                    a=1;
                }
                else if(a==0){
                    a=2;
                }
            }
        }
    }
    if(a==0 && c+'A'=='S'){
        for(int d=l;d<r;d++){
            if(dfs(l,d,'S'-'A') && dfs(d+1,r,'S'-'A')){
                a=2;
            }
        }
    }
    return a;
}
int dp(int l,int r){
    if(l==r && s[l]=='S'-'A')return 1;
    if(g[l][r]!=-1)return g[l][r];
    if(dfs(l,r,'S'-'A')==1){
        g[l][r]=1;
        return 1;
    }
    int &a=g[l][r];a=inf;
    for(int d=l;d<r;d++){
        a=min(a,dp(l,d)+dp(d+1,r));
    }
    return a;
}
int main(){
    freopen("gen.in","r",stdin);
    freopen("gen.out","w",stdout);

    n=geti();
    char ops[30];
    for(int i=1;i<=n;i++){
        scanf("%s",ops);
        rl[ops[0]-'A'].push_back((rule){ops[1]-'A',ops[2]-'A'});
    }
    k=geti();
    while(k--){
        scanf("%s",s+1);
        memset(f,-1,sizeof(f));
        memset(g,-1,sizeof(g));
        int len=strlen(s+1);
        for(int i=1;i<=len;i++){
            s[i]-='A';
        }
        if(dfs(1,len,'S'-'A')==0){
            printf("NIE\n");
            continue;
        }
        else{
            printf("%d\n",dp(1,len));
        }
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
