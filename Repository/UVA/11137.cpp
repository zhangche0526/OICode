#include<iostream>
#include<cstdio>
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;
const int MAXN=1e4;

ll f[2][MAXN+5];

int main()
{
	std::ios::sync_with_stdio(false);
	int n,i,j;
	f[0][0]=1;
	for(i=1;i<=21;i++)
		for(j=0;j<=MAXN;j++)
			if(j-i*i*i>=0) f[i&1][j]=f[i&1][j-i*i*i]+f[i&1^1][j];
			else f[i&1][j]=f[i&1^1][j];
	while(cin>>n) cout<<f[1][n]<<endl;
	return 0;
}
