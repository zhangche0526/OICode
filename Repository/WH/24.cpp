#include<cstdio>  
#include<iostream> 
using namespace std;
const int MAXN=1000,MAXK=30;
int N,K,f[MAXN+1][MAXK+1],T[MAXN+1],ans;  
int max(int a,int b){return a>b?a:b;}  
int main()  
{  
	ios::sync_with_stdio(false);
    freopen("24.in","r",stdin);  
    freopen("24.out","w",stdout);  
    cin>>N>>K;
    for(int i=1;i<=N;i++)  
    {  
    	cin>>T[i];
    }  
    for(int i=1;i<=N;i++)  
    {  
        for(int j=0;j<=K;j++)  
        {  
            if(j==0)  
            {
                f[i][j]=f[i-1][j];
                if((j%2+1)==T[i])
                    f[i][j]++;
                continue;
            }
            f[i][j]=max(f[i-1][j],f[i-1][j-1]);
            if((j%2+1)==T[i])
                f[i][j]++;
        }
    }
    for(int j=0;j<=K;j++)
        ans=ans>f[N][j]?ans:f[N][j];
    cout<<ans<<endl;
    return 0;  
}  
