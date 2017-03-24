#include <bits/stdc++.h>
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
const int maxn = 300;
double p[maxn],d[maxn];
double f[maxn][maxn],s[maxn][maxn],sp[maxn][maxn],tp[maxn];
int n,m;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int T=geti();
    while(T--){
        memset(f,0,sizeof(f));
        n=geti();m=geti();
        tp[0]=1;
        for(int i=1;i<=n;i++){
            scanf("%lf%lf",p+i,d+i);
            sp[1][i]=tp[i-1]*p[i];
            tp[i]=tp[i-1]*(1-p[i]);
        }
        for(int i=2;i<=m;i++){
            for(int j=1;j<=n;j++){
                sp[i][j]=sp[i-1][j]*sp[1][j];
                printf("sp[%d][%d] = %.10lf\n",i,j,sp[i][j]);
            }
        }
        double ret=0;
        for(int j=1;j<=n;j++){
            f[1][j]=sp[1][j];
            ret+=f[1][j]*d[j];
            s[1][j]=s[1][j-1]+f[1][j];
        }
        for(int i=2;i<=m;i++){
            for(int j=1;j<=n;j++){
                f[i][j]=p[j];
                double tmp=0;
                f[i][j]*=(1-s[i][j-1]);
                printf("f[%d][%d] = %.10lf\n",i,j,f[i][j]);
                f[i][j]*=(1-sp[i-1][j]);
                //f[i][j]-=f[i-1][j]*sp[j-1]*p[j];
                ret+=f[i][j]*d[j];
                s[i][j]=s[i][j-1]+f[i][j];
                printf("**f[%d][%d] = %.10lf\n",i,j,f[i][j]);
            }
        }
        printf("%.10lf\n",ret);
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
