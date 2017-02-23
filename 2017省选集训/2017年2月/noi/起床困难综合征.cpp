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
const int maxn = 100000 + 100;
int n,m;
int op[maxn],dr[maxn];
bitset<32> bef,cur,ret;
int main(){
    n=geti();m=geti();
    char ops[15];
    bitset<32> maxm(m);
    for(int i=1;i<=n;i++){
        scanf("%s",ops);
        if(ops[0]=='A'){
            op[i]=1;dr[i]=geti();
        }
        else if(ops[0]=='O'){
            op[i]=2;dr[i]=geti();
        }
        else{
            op[i]=3;dr[i]=geti();
        }
    }
    int flag=0;
    for(int i=30;i>=0;i--){
        cur=bef;
        cur[i]=0;
        int zero,one;
        for(int j=1;j<=n;j++){
            if(op[j]==1){
                cur&=dr[j];
            }
            else if(op[j]==2){
                cur|=dr[j];
            }
            else{
                cur^=dr[j];
            }
        }
        zero=cur[i];
        int cans=0;
        ret[i]=zero;
        if(flag || maxm[i]==1){
            cur=bef;
            cur[i]=1;
            for(int j=1;j<=n;j++){
                if(op[j]==1){
                    cur&=dr[j];
                }
                else if(op[j]==2){
                    cur|=dr[j];
                }
                else{
                    cur^=dr[j];
                }
            }
            one=cur[i];
            if(one>zero){
                cans=1;
                ret[i]=one;
            }
        }
        if(cans<maxm[i]){
            flag=1;
        }
    }
    int res=0,ers=1;
    for(int i=0;i<=30;i++){
        if(ret[i]==1){
            res+=ers;
        }
        ers*=2;
    }
    cout << res;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

