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
const int maxn = 1000000+1000;
const ll mo = 1000000007;
int T;
char s[maxn];
int nxt[maxn],fknxt[maxn],num[maxn],fknum[maxn];
int main(){
    T=geti();
    while(T--){
        memset(nxt,0,sizeof(nxt));
        memset(fknxt,0,sizeof(fknxt));
        memset(num,0,sizeof(num));
        memset(fknum,0,sizeof(fknum));
        scanf("%s",s+1);
        int n=strlen(s+1);
        nxt[1]=0;
        for(int i=2;i<=n;i++){
            int j=nxt[i-1];
            while(j && s[j+1]!=s[i])j=nxt[j];
            if(s[j+1]==s[i]){
                nxt[i]=j+1;
            }
            else nxt[i]=0;
        }
        /*cout << "nxt" << endl;
        for(int i=1;i<=n;i++)cout << nxt[i] << " ";
        cout << endl;*/
        fknxt[1]=0;
        for(int i=2;i<=n;i++){
            int j=fknxt[i-1];
            while((j && s[j+1]!=s[i])||j+1>i/2)j=nxt[j];
            if(s[j+1]==s[i]){
                fknxt[i]=j+1;
            }
            else fknxt[i]=0;
        }
        /*cout << "fknxt" << endl;
        for(int i=1;i<=n;i++){
            cout << fknxt[i] << " ";
        }
        cout << endl;*/
        fknum[1]=0;
        for(int i=2;i<=n;i++){
            if(nxt[i]!=0)fknum[i]=fknum[nxt[i]]+1;
            else fknum[i]=0;
        }
        /*cout << "fknum" << endl;
        for(int i=1;i<=n;i++){
            cout << fknum[i] << " ";
        }
        cout << endl;*/
        num[1]=0;
        for(int i=2;i<=n;i++){
            if(fknxt[i]!=0){
                num[i]=fknum[fknxt[i]]+1;
            }
            else{
                num[i]=0;
            }
        }
        /*cout << "s" << endl;
        for(int i=1;i<=n;i++)cout << s[i] << " ";
        cout << endl;
        for(int i=1;i<=n;i++)cout << num[i] << " ";
        cout << endl;*/
        ll res=1;
        for(int i=1;i<=n;i++){
            res=(res*(num[i]+1))%mo;
        }
        printf("%lld\n",res);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}

