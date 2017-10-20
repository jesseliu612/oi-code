#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cmath>
#include <complex>
using namespace std;
typedef complex<double> C;
const double pi = acos(-1.0);
const int maxn = 524288+1000;
int n,m,L;
int R[maxn];
C a[maxn],b[maxn];
void fft(C *x,int f){
    for(int i=0;i<=n;i++)if(i<R[i])swap(x[i],x[R[i]]);
    for(int i=1;i<n;i<<=1){
	C wn(cos(pi/i),sin(f*pi/i));
	for(int j=0,p=i<<1;j<n;j+=p){
	    C w(1,0);
	    for(int k=0;k<i;k++,w*=wn){
		C u=x[j+k],v=w*x[j+k+i];
		x[j+k]=u+v;
		x[j+k+i]=u-v;
	    }
	}
    }
}
int res[maxn],outer[maxn];
char s1[maxn],s2[maxn];
int main(){
    scanf("%s%s",s1,s2);
    n=strlen(s1)-1;m=strlen(s2)-1;
    for(int i=0;i<=n;i++)a[i]=s1[n-i]-'0';
    for(int i=0;i<=m;i++)b[i]=s2[m-i]-'0';
 
    m=n+m;for(n=1;n<=m;n<<=1)L++;
    for(int i=0;i<n;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
    fft(a,1);fft(b,1);
    for(int i=0;i<=n;i++)a[i]*=b[i];
    fft(a,-1);
    for(int i=0;i<=m;i++)res[i]=int(a[i].real()/n+0.5);
    int ret=0,cnt=0;
    for(int i=0;i<=m;i++){
	outer[++cnt]=(res[i]+ret)%10;
	ret=(res[i]+ret)/10;
    }
    while(ret){
	outer[++cnt]=ret%10;ret/=10;
    }
    for(int i=cnt;i;i--)printf("%d",outer[i]);
 
    return 0;
}
