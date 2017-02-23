#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cmath>
#include <complex>
using namespace std;
typedef complex<double> C;
const double pi = acos(-1.0);
const int maxn = 262145;
int n,m,L;
int R[maxn];
C a[maxn],b[maxn];
int geti(){
    int ret=0,k=0;char ch;
    while((ch<'0' || ch>'9') && ch!='-')ch=getchar();
    if(ch=='-')k=1,ch=getchar();
    while(ch>='0' && ch<='9')ret=ret*10+ch-'0',ch=getchar();
    return k?-ret:ret;
}
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
int main(){
    n=geti();m=geti();
    for(int i=0;i<=n;i++)a[i]=geti();
    for(int i=0;i<=m;i++)b[i]=geti();
    m=n+m;for(n=1;n<=m;n<<=1)L++;
    for(int i=0;i<n;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
    fft(a,1);fft(b,1);
    for(int i=0;i<=n;i++)a[i]*=b[i];
    fft(a,-1);
    for(int i=0;i<=m;i++)printf("%d ",int(a[i].real()/n+0.5));
    return 0;
}
