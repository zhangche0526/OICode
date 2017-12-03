#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;  
const int MAXN=80000;
int f[MAXN+1],c[MAXN+1];  
int main()  
{
	ios::sync_with_stdio(false);
	freopen("8.in","r",stdin);
	freopen("8.out","w",stdout);
        int i,x,n;char ch;
	cin>>n;
        for(i=1;i<=n;i++)  
        {  
                cin>>ch;
                if(ch=='s') c[i]=c[f[i-1]],f[i]=f[f[i-1]];
                else
                {  
                        cin>>x;
                        if(ch=='t') f[i]=f[x-1],c[i]=c[x-1];
                        else f[i]=i-1,c[i]=x;
                }  
                if(c[i]) cout<<c[i]<<endl;
                else cout<<-1<<endl;
        }  
        return 0;  
} 
