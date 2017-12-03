#include<iostream>
#include<cstdio>
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;
const ll MAXN=1005;

int gcd(int a,int b){return b==0?a:gcd(b,a%b);}

ll C[MAXN*MAXN];
inline void	initC()
{
	int i,j;
	C[3]=1,C[4]=4;
	for(i=5;i<MAXN*MAXN;i++)
		C[i]=i*(i-1)*(i-2)/6;
}

ll f[MAXN][MAXN],sum[MAXN][MAXN];
inline void preTab()
{
	initC();
	ll i,j;
	for(i=1;i<MAXN;i++)
		for(j=1;j<MAXN;j++)
		{
			f[i][j]=f[i][j-1]+f[i-1][j]-f[i-1][j-1]+gcd(i,j)-1;
			sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+f[i][j];
		}
}

int main()
{
	preTab();
	int Case=0,n,m;
	while(scanf("%d%d",&n,&m)&&n&&m)
	{
		ll ans=C[(n+1)*(m+1)]-(n+1)*C[m+1]-(m+1)*C[n+1]-sum[n][m]*2;
		cout<<"Case "<<++Case<<": "<<ans<<endl;
	}
	return 0;
}
